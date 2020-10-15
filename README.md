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
  - Parrot bebop 2 drone
  - Intel® RealSense™ Depth Camera D435 
  - Raspberry pi 4

## 4. 설치 및 실행
#### 4.1.  git clone
```
$ cd catkin_ws

$ git clone -b SLAM --single-branch https://github.com/ldj5123/ROSque.git

$ catkin_make
```

#### 4.2. realsense2_camera 패키지를 pi에 설치

#### 4.3. 실행

```
$ roscore
```
rtabmap 실행
```
$ roslaunch rtabmap_ros d435_rtabmap.launch
```
bebop autonomy 실행
```
$ roslaunch bebop_driver bebop_node.launch
```
bebop 원격 조종 노드 실행
```
$ rosrun bebop_teleop bebop_teleop_node 
```
pi에서 실행 (노트북에 카메라를 연결하여 SLAM 가능)
```
$ roslaunch realsense2_camera rs_camera.launch 
```

## 5. 장애요인 및 해결사항
#### 5-1. Monocular SLAM으로 진행하려 했으나 특이점만 인식해 Mapping하다보니 정확도가 떨어져 Depth camera를 활용
  * Depth camera를 활용할 MCU로 Raspberry pi 3를 선택

#### 5-2. D435를 사용하려면 USB 3.0이 필요하지만 Raspberry pi 3는 USB 2.0만 지원
  * pi 3로 진행하니 성능이 떨어져 영상전송 지연율 증가 (약 30,000ms)
  * MCU를 Lattepanda로 변경 진행 -> 성능은 좋지만 발열과 전원공급에 문제가 생김
  * MCU를 Raspberry pi 4로 변경 진행 -> 10fps 확보
  * pi 4 사용시 영상수신 가능하지만 point cloud2를 subscribe하는데 network 성능이 낮아 jetson이나 odroid 보드를 사용하면 개선될 것으로 보임

#### 5-3. pi 4의 외부전원으로 Lipo 배터리를 사용했는데 중량이 커져 드론의 비행시간이 줄어들고 pi 4를 드론의 위에 부착하다보니 무게중심이 높아져 비행안정성이 떨어짐
  * 드론의 배터리에서 전원공급을 받는다면 비행시간과 비행안정성을 개선할 수 있음

    <img src="/image/ROSque_battery.png" width="48%" height="48%"></img>
    <img src="/image/ROSque_bebop2.png" width="48%" height="48%"></img>

#### 5-4. RGB-D 카메라는 고사양을 요구해 MCU의 사양에 따라 mapping 속도가 달라질 수 있을 것으로 보임

#### 5-5. 빛반사에 의해 센서가 거리를 오인식해 voxel 생성

## 6. 결과물
* 강당 SLAM

<img src="/image/SLAM_sample.gif" width="95%" height="95%"></img>

<img src="/image/SLAM.png" width="48%" height="48%"></img>
<img src="/image/SLAM2.png" width="48%" height="48%"></img>
<img src="/image/SLAM_hall_full.png" width="48%" height="48%"></img>
<img src="/image/SLAM_hall_full2.png" width="48%" height="48%"></img>
