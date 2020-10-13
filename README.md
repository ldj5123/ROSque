Navigation
==============
## 1. 목적
* 드론이 SLAM으로 작성힌 맵 기반의 장애물을 회피하며 자율비행
## 2. 주요 기능
* 3D맵을 구성하여 드론이 Navigation을 수행

## 3. 개발환경
* 소프트웨어
  - Linux ubuntu 16.04
  - ROS kinetic
* 하드웨어
  - Parrot bebop 2 drone

## 4. 결과물

* moveit이라는 매니퓰레이터를 모션플래닝하는 패키지를 이용
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
<img src="/image/drone_model.png" width="60%" height="60%"></img>
  - moveit_setup_assistant로 생성한 bebop_path_planning demo.launch 실행화면
<img src="/image/rivz.gif" width="60%" height="60%"></img>

* moveit 상에서 point cloud subscribe
  - octomap-server로 point cloud를 발행했으나, 드론이 맵을 장애물로 인식하지 않고 통과
  - bebop_path_planning 패키지의 config에 [sensors_3d](https://github.com/ldj5123/ROSque/blob/Navigation/bebop_path_planning/config/sensors_3d.yaml) point cloud topic을 수정
```
sensors:
    - sensor_plugin: occupancy_map_monitor/PointCloudOctomapUpdater
      point_cloud_topic: /my_topic
      max_range: 40.0
      point_subsample: 10
      padding_offset: 0.1
      padding_scale: 1.0
      filtered_cloud_topic: filtered_cloud
```
  - point_cloud_io 패키지를 이용해 point_cloud_topic에서 설정한 토픽명으로 point cloud 발행

<img src="/image/moveit_map.png" width="60%" height="60%"></img>
 
* path_planning을 통한 Navigation 구현
  - bebop_path_planning에서 plan했을 때 move_group/display_planned_path로 point 좌표값을 발행하는 것을 확인하고, 각 point로 이동하는 [알고리즘](https://github.com/ldj5123/ROSque/blob/Navigation/rosque_navi/src/path.h "path.h") 개발
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
- 
## 5. 장애요인 및 해결사항
* SLAM으로 생성한 ply파일의 크기가 너무 클 경우, rviz에서 point cloud Subscribe 및 path planning 실행 지연 또는 불가 
* D435는 고사양을 요구해 Localization 시 지연 시간이 길어져, rviz상에서 실제 드론의 정확한 위치추정 불가
* 생성된 3D맵과 실제 공간의 괴리에 따른 드론 제어의 어려움
