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

## 4. 개발시 발생한 장애요인 및 해결사항
* 저화질의 단안 카메라는 dnn_detect로 먼거리의 피사체 인식불가 
* 인식된 target_object의 라벨링이 중복될 경우, 우선순위 설정 불가능
* 먼거리에 있는 장애물임에도 불구하고, 지정한 대각 거리 이상의 물체일 때는 회피 기동함
* 피사체의 크기에 따른 boundary box 대각거리의 차이로 일정한 거리 유지 불가능

## 5. 결과물
영상, 이미지


