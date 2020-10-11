Navigation
==============
## 1. 목적
* 
## 2. 주요 기능
* SLAM으로 작성한 맵을 기반으로 드론의 자율비행

## 3. 주요 하드웨어
* parrot bebop 2 drone
* 노트북

## 4. 프로젝트 기간
* 2020.9.21 ~ 2020.10.2

## 5. 진행과정
#### 5-1. ROS package
* bebop_autonomy
  - bebop 2 drone 을 사용하기위한 패키지
* move_it
  - bebop에 맞게 urdf작성 후 moveit_setup_assistant를 사용해 moveit을 위한 모든 설정이 담긴 패키지 생성(여기서는 test2)
* test2
  - point_cloud_io로 발행한 토픽을 받아 맵을 만들고 도착지점을 지정해 이동동선을 만들어준다
* point_cloud_io
  - SLAM으로 작성한 ply파일을 point cloud로 만들어 지정한 topic명으로 발행
* bebop_teleop
  - 드론의 직접조종이 필요할 때 사용
* rosque_navi
  - move_it에서 만든 이동동선을 토대로 이동하는것을 구현

#### 5-2. 소스코드
* bebop_teleop
  - 전체 코드
    link
  - 코드 설명
* rosque_navi
  -전체 코드
    + rosque_navi.cpp
    + path.h
#### 5-3. topic
<img src="/image/slam_topic.png" width="100%" height="100%"></img>

## 6. 결과물
영상, 이미지

## 7. 개선할점
