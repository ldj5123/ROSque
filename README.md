SLAM
==============
## 1. 목적
* 
## 2. 주요 기능
* ROS를 이용해 임의의 실내공간을 localization하며 mapping 함

## 3. 주요 하드웨어
* Intel® RealSense™ Depth Camera D435
* parrot bebop 2 drone
* raspberry pi 4
* 노트북

## 4. 프로젝트 기간
* 2020.9.9 ~ 2020.9.18

## 5. 진행과정
#### 5-1. 하드웨어 구성
* raspberry pi 4 에 d435 카메라를 연결한 후 pi를 bebop 2 drone에 부착
-드론사진-

#### 5-2. ROS package
* bebop_autonomy
* realsense2_camera(d435)
  - pi 4에 realsense2_camera 패키지를 사용하려면 SDK를 설치해야하는데 intel에서 pi 4 32bit환경에 대한 SDK설치 지원을 안해주어 어려움이 있었으나
멘토의 도움으로 pi4 32비트에서 SDK를 설치
* rtabmap_ros
  - 사용하려는 카메라에 맞게 rtabmap.launch의 인자 기본값을 수정
  <pre>
  <code>
  arg name="rgb_topic"               default="/camera/color/image_raw"
  arg name="depth_topic"             default="/camera/aligned_depth_to_color/image_raw"
  arg name="camera_info_topic"       default="/camera/color/camera_info"
  arg name="depth_camera_info_topic" default="$(arg camera_info_topic)"
  </code>
  </pre>
  - pi의 사양이 낮아 이미지 전송속도가 느려 queue_size를 90으로 늘려주어 
* bebop_teleop
  - bebop 2 drone을 조종하는 노드


#### 5-3. topic
<img src="/image/slam_topic.png" width="100%" height="100%"></img>

## 6. 결과물
영상, 이미지

## 7. 개선할점
