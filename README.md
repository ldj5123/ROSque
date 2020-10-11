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
  - move_it을 이용해 드론의 이동동선을 그려줌
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
