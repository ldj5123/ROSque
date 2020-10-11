Active tracking
==============
## 1. 목적
* 실내외 공간에서 특정 피사체를 추적할 수 있는 시스템 구축
## 2. 주요 기능
* 목표 피사체 인지(Target searching), 거리유지(Maintaining), 충돌회피(Collision Avoidance)

## 3. 개발환경
* 소프트웨어
  - Linux ubuntu 16.04
  - ROS kinetic
* 하드웨어
  - parrot bebop 2 drone

## 4. 프로젝트 기간
* 2020.9.25 ~ 2020.10.15

## 5. 진행과정
#### 5-1. ROS package
* bebop_autonomy
  - bebop 2 drone 사용을 위한 패키지
* dnn_detect
* 

#### 5-2. 소스코드
* bebop_teleop
  - 전체 코드
    link
  - 코드 설명
* rosque_navi
  -전체 코드
    + rosque_navi.cpp link
    + path.h link
#### 5-3. topic
<img src="/image/slam_topic.png" width="100%" height="100%"></img>

## 6. 결과물
영상, 이미지

## 7. 문제점 및 보완사항
* SLAM으로 생성한 파일의 크기가 너무 클 경우 rviz에서 point cloud를 Subscribe 및 path planning 시 시간이 오래 걸림
* D435는 고사양을 요구해 Localization 시 지연 시간이 길어져 사용불가
* rviz상에서 실제 드론의 위치추정 불가
* 생성된 3D맵과 실제 공간의 괴리에 따른 드론 제어의 어려움
* 
