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

## 4. 결과물
영상, 이미지

## 5. 개발시 발생한 장애요인 및 해결사항
* SLAM으로 생성한 파일의 크기가 너무 클 경우 rviz에서 point cloud Subscribe와 path planning 실행 지연 또는 불가 
* D435는 고사양을 요구해 Localization 시 지연 시간이 길어져 사용불가
* rviz상에서 실제 드론의 위치추정 불가
* 생성된 3D맵과 실제 공간의 괴리에 따른 드론 제어의 어려움
