Active tracking
==============
## 1. 목적
* 실내외 공간에서 드론으로 특정 물체를 추적할 수 있는 시스템 구축

## 2. 주요 기능
* 드론의 단안 카메라 및 OpenCV Dnn_detect를 이용한 물체 추적 
  - 목표 물체 탐색(Target searching), 거리 유지(Maintaining constant distance), 충돌 회피(Collision Avoidance)

## 3. 개발환경
* 소프트웨어
  - Linux ubuntu 16.04
  - ROS kinetic
* 하드웨어
  - Parrot bebop 2 drone

## 4. 장애요인 및 해결사항

1. 드론에 Realsense2 D435(Detph Camera)와 Raspberri pi 4를 부착 후, find_Object_2D를 사용
  * Depth Camera는 image frame (fps) 수신이 매우 느려 사용 불가, 데이터 처리 위한 고사양의 컴퓨팅 환경 요구, 
  * Find_Object_2D는 실시간 Target Object 지정 가능하나, 물체가 회전할 시 특이점이 변경되어 학습된 물체 인식 못함

2. Bebop2의 Monocular Camera와 dnn_detect package 사용
  * 4M 이상 거리의 물체 인식 불가, confidence 값을 0.5 이하로 낮추면 인식률이 높아지나 Labeling 정확도가 낮아짐
  * 인식된 Target object의 Labeling이 둘 이상일 경우, dnn_detect에서 Tracking 우선순위 설정불가 
  
3. 대각거리로 일정거리 유지 (수정, 코드 입력)
  * 물체의 크기에 따라 Bounding box일정거리 유지 불가능
  * Bounding box 크기가 기준 대각거리보다 클 때, 먼거리의 물체도 회피 기동함
  * 인식된 물체의 confidence가 0.75 이상일 경우에만 장애물로 인식할 수 있도록 함
  
4. remap 함수를 이용한 범위 변환
  * Bounding Box의 위치와 크기에 따른 속도
  * diagonal_distance1 (150 ~ 320) →  linear_x (0.2 ~ 0)
  * frame_x (0 ~ 856) →  angluar_z (-0.3 ~ 0.3)
  * frame_y (480 ~ 0) →  linear_z (-0.3 ~ 0.3)  



## 5. 결과물
active_tracking.bash
영상, 이미지

