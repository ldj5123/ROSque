Navigation
==============
## 1. 목적
* 드론이 SLAM으로 작성힌 맵 기반의 장애물을 회피하며 자율비행
## 2. 주요 기능
* SLAM으로 저장한 .ply파일을 point_cloud_io 패키지를 이용해 point cloud2 topic 발행
* point cloud2를 subscribe해 rivz상에서 octomap으로 구현
* 목표지점을 지정, plan하면 장애물을 피하며 회피기동 경로 topic publish
* 경로를 subscribe하여 좌표마다 이동하는 cmd_vel topic publish
* 경로대로 drone 이동

<img src="/image/Navigation_chart.png" width="95%" height="95%"></img>

## 3. 개발환경
* 소프트웨어
  - Linux ubuntu 16.04
  - ROS kinetic
* 하드웨어
  - Parrot bebop 2 drone
  
## 4. 설치 및 실행

#### 4-1. 설치
```
$ cd catkin_ws

$ git clone https://github.com/AutonomyLab/bebop_autonomy.git

$ git clone -b Navigation --single-branch https://github.com/ldj5123/ROSque.git

$ catkin_make
```
#### 4-2. 실행
```
$ roscore
```
```
$ roslaunch bebop_driver bebop_node.launch
```
이동 경로를 생성하는 bebop moveit 실행
```
$ roslaunch bebop_path_planning demo.launch
```
경로대로 움직이는 알고리즘 노드 실행
```
$ rosrun rosque_navi rosque_navi
```
비상시 착륙할 수 있도록 조종 노드 실행
```
$ rosrun bebop_teleop bebop_teleop_node
```


## 5. 프로젝트 수행 경과 및 개선 사항

#### 5-1. moveit이라는 매니퓰레이터를 모션플래닝하는 패키지를 이용
  - bebop에 맞도록 [urdf](https://github.com/ldj5123/ROSque/blob/Navigation/bebop_path_planning/config/bebop.urdf "urdf")를 작성 후, moveit_setup_assistant로 bebop_path_planning 패키지를 생성
  ```
  <link name="landing_gear">
    <visual>
      <geometry>
        <cylinder length="0.18" radius="0.03"/>
      </geometry>
      <origin rpy="0 -1.5708 0" xyz="0 0 0"/>
      <material name="blue">
        <color rgba="0 0 .8 1"/>
      </material>
    </visual>
    <collision>
      <geometry>
        <cylinder length="0.18" radius="0.03"/>
      </geometry>
      <origin rpy="0 -1.5708 0" xyz="0 0 0"/>
    </collision>
    <inertial>
      <mass value="10"/>
      <inertia ixx="1.0" ixy="1.0" ixz="1.0" iyy="1.0" iyz="1.0" izz="1.0"/>
    </inertial>
  </link>
  ...
```
- moveit_setup_assistant로 bebop_path_planning 패키지 생성
  
<img src="/image/drone_model.png" width="95%" height="95%"></img>

- moveit_setup_assistant로 생성한 bebop_path_planning demo.launch 실행화면
  
<img src="/image/rivz.gif" width="95%" height="95%"></img>

#### 5-2. moveit 상에서 point cloud subscribe
  - octomap-server로 point cloud를 발행했으나, 드론이 맵을 장애물로 인식하지 않고 통과
  - bebop_path_planning 패키지의 config에 [sensors_3d](https://github.com/ldj5123/ROSque/blob/Navigation/bebop_path_planning/config/sensors_3d.yaml) point cloud topic을 수정
```
sensors:
    - sensor_plugin: occupancy_map_monitor/PointCloudOctomapUpdater
      point_cloud_topic: /my_topic
      max_range: 40.0
      point_subsample: 10
      padding_offset: 0.1
      padding_scale: 1.04. 결과물
      filtered_cloud_topic: filtered_cloud
```
  - point_cloud_io 패키지를 이용해 point_cloud_topic에서 설정한 토픽명으로 point cloud 발행
  
<img src="/image/moveit_map.png" width="95%" height="95%"></img>
  
  - PC 성능에 낮고 SLAM으로 생성한 ply파일의 크기가 너무 클 경우, rviz에서 point cloud Subscribe 및 path planning 실행 지연 
 
#### 5-3. path_planning을 통한 Navigation 구현
  - bebop_path_planning에서 plan했을 때 move_group/display_planned_path로 point 좌표값을 발행하는 것을 확인하고, 각 point로 이동하는 [알고리즘](https://github.com/ldj5123/ROSque/blob/Navigation/rosque_navi/src/path.h "path.h") 개발
  
<img src="/image/plan.gif" width="95%" height="95%"></img>
```
          translation: 
            x: 0.393470570714
            y: -0.351707545828
            z: 0.0
          rotation: 
            x: 0.0
            y: 0.0
            z: -7.72150347209e-06
            w: 0.99999999997
```
  - vector를 이용해 각 좌표를 변수에 담음
```
    for (i = 0; i < point_size; i++) {
        path_x.push_back(msg.trajectory[0].multi_dof_joint_trajectory.points[i].transforms[0].translation.x);
        path_y.push_back(msg.trajectory[0].multi_dof_joint_trajectory.points[i].transforms[0].translation.y);
        path_z.push_back(msg.trajectory[0].multi_dof_joint_trajectory.points[i].transforms[0].translation.z);
        qz = msg.trajectory[0].multi_dof_joint_trajectory.points[i].transforms[0].rotation.z;
        qw = msg.trajectory[0].multi_dof_joint_trajectory.points[i].transforms[0].rotation.w;
        path_w.push_back(Quaternion2Yaw(qz, qw));
    }
```
  - 경로의 현재좌표와 다음좌표의 차를 이용해 bebop을 이동
```
    // x, y, z : 현재좌표 x_n, y_n, z_n : 
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    std::chrono::milliseconds mill = std::chrono::duration_cast<std::chrono::milliseconds>(start - start);
    float z_ = z_n - z;
    float y_ = y_n - y;
    float x_ = x_n - x;
    geometry_msgs::Twist cmdT;
    while(mill.count() < millsec){
        std::chrono::system_clock::time_point End = std::chrono::system_clock::now();
        mill = std::chrono::duration_cast<std::chrono::milliseconds>(End - start);
        cmdT;

        cmdT.linear.x = x_/8;
        cmdT.linear.y = y_/8;
        cmdT.linear.z = 0;
        cmdT.angular.x = cmdT.angular.y = cmdT.angular.z = 0;
        bebop_cmd.publish(cmdT);
    }
```
  
* 생성된 3D맵과 실제 공간의 괴리에 따른 드론 제어의 어려움

## 6. 결과물
  {% include navigation.html id="qfNVPmGrgD4" %}

