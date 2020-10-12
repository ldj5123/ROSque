Navigation
==============
## 1. 목적
* 드론이 SLAM으로 작성한 맵을 기반의 장애물을 회피하며 자율비행
## 2. 주요 기능
* 3D맵을 구성하여 drone이 navigation을 수행

## 3. 개발환경
* 소프트웨어
  - Linux ubuntu 16.04
  - ROS kinetic
* 하드웨어
  - parrot bebop 2 drone

## 4. 프로젝트 기간
* 2020.9.19 ~ 2020.10.2

## 5. 진행과정
#### 5-1. ROS package
* bebop_autonomy
  - bebop 2 drone 사용을 위한 패키지
* move_it
  - drone에 맞게 urdf작성
  - moveit_setup_assistant 패키지를 사용해 moveit을 위한 모든 설정이 담긴 패키지 생성(test2)
* point_cloud_io
  - SLAM으로 생성한 ply파일의 point cloud를 topic으로 발행
* test2
  - point_cloud_io로 발행한 토픽을 받아 맵을 만들고 시작지점과 도착지점을 지정해 이동 동선을 만듦
* bebop_teleop
  - 드론의 직접조종이 필요할 때 사용
* rosque_navi
  - move_it에서 만든 이동 동선을 토대로 Navigation 구현

/*#### 5-2. 소스코드
* bebop_teleop
  - [bebop_teleop.cpp](https://github.com/ldj5123/ROSque/blob/Navigation/bebop_teleop/src/bebop_teleop.cpp "bebop_teleop")
* rosque_navi
  - [rosque_navi.cpp](https://github.com/ldj5123/ROSque/blob/Navigation/rosque_navi/src/rosque_navi.cpp "rosque_navi.cpp")
  - [path.h](https://github.com/ldj5123/ROSque/blob/Navigation/rosque_navi/src/path.h "path.h")*/
#### 5-3. topic
<img src="/image/rosque_navi.png" width="100%" height="100%"></img>

## 6. 결과물
영상, 이미지

## 7. 문제점 및 보완사항
* SLAM으로 생성한 파일의 크기가 너무 클 경우 rviz에서 point cloud Subscribe와 path planning 실행 지연 또는 불가 
* D435는 고사양을 요구해 Localization 시 지연 시간이 길어져 사용불가
* rviz상에서 실제 드론의 위치추정 불가
* 생성된 3D맵과 실제 공간의 괴리에 따른 드론 제어의 어려움
* 
