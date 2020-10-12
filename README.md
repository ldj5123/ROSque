SLAM
==============
## 1. 목적
* SLAM을 이용하여 드론으로 주변 환경에 대한 모델을 3D맵으로 생성, 사람이 접근하기 힘든 실내 공간을 인식할 수 있게 함

## 2. 주요 기능
* 임의의 실내공간을 localization하며 mapping 함

## 3. 개발환경
* 소프트웨어
  - Linux ubuntu 16.04
  - ROS kinetic
* 하드웨어
  - parrot bebop 2 drone
  - Intel® RealSense™ Depth Camera D435
  - raspberry pi 4

## 4. 결과물
영상, 이미지

## 5. 개발시 발생한 장애요인 및 해결사항
1. Monocular SLAM으로 진행하려 했으나 특이점만 인식해 Mapping하다보니 정확도가 떨어져 depth camera를 활용
    * depth camera를 활용할 MCU로 Raspberry pi 3를 선택

2. D435를 사용하려면 USB 3.0이 필요하지만 Raspberry pi 3는 USB 2.0만 지원
    * pi 3로 진행하니 성능이 떨어져 영상전송 지연율 증가 (약 30,000ms)
    * MCU를 Lattepanda로 변경 진행 -> 성능은 좋지만 발열과 전원공급에 문제가 생김
    * MCU를 raspberry pi 4로 변경 진행 -> 10fps 확보
    * pi 4 사용시 영상수신 가능하지만 point cloud2를 subscribe하는데 network 성능이 낮아 jetson이나 odroid 보드를 사용하면 개선될 것으로 보임

3. pi 4의 외부전원으로 Lipo 배터리를 사용했는데 중량이 커져 드론의 비행시간이 줄어들고 pi 4를 드론의 위에 부착하다보니 무게중심이 높아져 비행안정성이 떨어짐
    * 드론의 배터리에서 전원공급을 받는다면 비행시간과 비행안정성을 개선할 수 있음

4. RGB-D 카메라는 고사양을 요구해 MCU의 사양에 따라 mapping 속도가 달라질 수 있을 것으로 보임
