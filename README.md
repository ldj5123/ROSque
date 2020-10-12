 Active tracking
==============
## 1. 목적
* 실내외 공간에서 드론으로 특정 피사체를 추적할 수 있는 시스템 구축

## 2. 주요 기능
* 드론의 단안 카메라 및 OpenCV를 이용한 목표 피사체 인지(Target searching), 거리유지(Maintaining), 충돌회피(Collision Avoidance)

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
  - OpenCV를 이용한 학습된 피사체 인식
* active_tarcking 
  - dnn_detect로 인식한 피사체 중 target_object 추적
* bebop_teleop
  - 드론 직접조종이 필요할 때 사용
    
#### 5-2. topic
<img src="/image/active_tracking.png" width="100%" height="100%"></img>

## 6. 결과물
영상, 이미지

## 7. 문제점 및 보완사항
* 저화질의 단안 카메라는 dnn_detect로 먼거리의 피사체 인식불가 
* 인식된 target_object의 라벨링이 중복될 경우, 우선순위 설정 불가능
* 먼거리에 있는 장애물임에도 불구하고, 지정한 대각 거리 이상의 물체일 때는 회피 기동함
* 피사체의 크기에 따른 boundary box 대각거리의 차이로 지정한 거리 유지 불가능


