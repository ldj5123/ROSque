Navigation
==============
## 1. 목적
* 드론이 SLAM으로 작성 기반의 장애물을 회피하며 자율비행
## 2. 주요 기능
* 3D맵을 구성하여 drone이 navigation을 수행

## 3. 개발환경
* 소프트웨어
  - Linux ubuntu 16.04
  - ROS kinetic
* 하드웨어
  - parrot bebop 2 drone

## 4. 개발시 발생한 장애요인 및 해결사항
* SLAM으로 생성한 파일의 크기가 너무 클 경우 rviz에서 point cloud Subscribe와 path planning 실행 지연 또는 불가 
* D435는 고사양을 요구해 Localization 시 지연 시간이 길어져 사용불가
* rviz상에서 실제 드론의 위치추정 불가
* 생성된 3D맵과 실제 공간의 괴리에 따른 드론 제어의 어려움

## 5. 결과물

* bebop
  - bebop_driver
  - bebop_teleop_node
  - point_cloud_io pkg
  : 발행한 topic에 대한 설명
  
* navigation
  - bebop_path_planning  
  - rosque_navi

* urdf를 작성하여 드론 모델링
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
![drone_model](https://user-images.githubusercontent.com/67685757/95724330-37369200-0cb1-11eb-8330-6d9267580ed1.png)

* moveit setup assistant로 생성한 bebop_path_planning demo.launch 실행화면
![moveit](https://user-images.githubusercontent.com/67685757/95725480-acef2d80-0cb2-11eb-9f44-b608c25d3187.png)

* point_cloud_io로 SLAM한 맵의 point cloud를 발행한 화면
![moveit_map](https://user-images.githubusercontent.com/67685757/95727014-977b0300-0cb4-11eb-9f18-721df8b9a441.png)

