SLAM
==============
## 1. 목적
* SLAM을 이용하여 드론으로 이동중 주변 환경에 대한 모델을 3D맵으로 생성, 사람이 접근하기 힘든 실내 공간을 인식할 수 있게 함
## 2. 주요 기능
* ROS를 이용해 임의의 실내공간을 localization하며 mapping 함.

## 3. 개발환경
* 소프트웨어
  - Linux ubuntu 16.04
  - ROS kinetic
* 하드웨어
  - parrot bebop 2 drone
  - Intel® RealSense™ Depth Camera D435
  - raspberry pi 4

## 4. 프로젝트 기간
* 2020.9.9 ~ 2020.9.18

## 5. 진행과정
#### 5-1. 하드웨어 구성
* raspberry pi 4에 D435 카메라를 연결 후, bebop 2 drone에 부착.
-드론사진-

#### 5-2. ROS package
* bebop_autonomy
  - ROS에서 bebop을 사용하기 위한 패키지
* realsense2_camera(D435)
  - pi 4에 realsense2_camera 패키지를 사용하려면 SDK를 설치 필요.
  - Intel 제조사는 pi4 32bit 환경 SDK 설치에 대한 지원이 없음.
  - ()을 통해 pi4 32비트에서 SDK 설치.
* rtabmap_ros
  - D435에 맞게 rtabmap.launch의 인자 기본값 수정.
  <pre>
  <code>
  arg name="rgb_topic"               default="/camera/color/image_raw"
  arg name="depth_topic"             default="/camera/aligned_depth_to_color/image_raw"
  arg name="camera_info_topic"       default="/camera/color/camera_info"
  arg name="depth_camera_info_topic" default="$(arg camera_info_topic)"
  arg name="queue_size"              default="90"
  </code>
  </pre>
* bebop_teleop
  - bebop 2 drone을 조종하는 노드 구현.


#### 5-3. topic
<img src="/image/slam_topic.png" width="100%" height="100%"></img>

## 6. 결과물
영상, 이미지

## 7. 개선할 점
#### D435와 Pi
  * 
