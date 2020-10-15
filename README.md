Active tracking
==============
## 1. 목적
* 실내외 공간에서 드론으로 특정 물체를 추적할 수 있는 시스템 구축

## 2. 주요 기능
* 드론의 단안 카메라 및 OpenCV dnn_detect를 이용한 물체 추적 
  - 목표 물체 탐색(Target searching), 거리 유지(Maintaining constant distance), 충돌 회피(Collision Avoidance)
* drone으로부터 전송받은 이미지를 dnn_detect를 통해 object 인식
* active_tracking에 추적할 object 입력
* 입력한 object 외의 object 중 bounding box의 크기가 크면 회피기동
* 입력한 object의 bounding box의 위치와 사이즈로 일정거리 유지하며 추적

<img src="/image/active_tracking_chart.png" width="95%" height="95%"></img>

## 3. 개발환경
* 소프트웨어
  - Linux ubuntu 16.04
  - ROS kinetic
* 하드웨어
  - Parrot bebop 2 drone
  
## 4. 설치 및 실행


## 5. 장애요인 및 해결사항

#### 5-1. 드론에 Realsense2 D435(Detph Camera)와 Raspberri pi 4를 부착 후, find_Object_2D 사용
  * Depth Camera는 image frame (fps) 수신이 느림 -> 데이처 처리 위한 고사양의 컴퓨팅 환경 요구
  * Find_Object_2D는 실시간 Target Object 지정가능하나, 물체 회전 시 특이점이 변경되어 인식 불가 
  
#### 5-2. Bebop2의 Monocular Camera와 dnn_detect로 변경
  * 4M 이상 거리의 물체 인식 불가 -> confidence 값을 0.5 이하로 낮추면 인식률 향상, Labeling 정확도 하락
  * Target object 둘 이상일 경우 -> dnn_detect의 Labeling은 Tracking 우선순위 설정 불가
  
#### 5-3. dnn_detect launch 추가
```
<!-- Run the dnn_detect node -->
<launch>
  <!-- namespace for camera input -->
  <arg name="camera" default="/"/>
  <arg name="image" default="/bebop/image_raw"/>
  <arg name="transport" default="compressed"/>

  <node pkg="dnn_detect" name="dnn_detect"
    type="dnn_detect" respawn="false">
    <param name="image_transport" value="$(arg transport)"/>
    <param name="publish_images" value="true" />
    <param name="data_dir" value="$(find dnn_detect)/model"/>
	<param name="min_confidence" value="0.5"/>

    <remap from="/camera/compressed" to="$(arg image)/$(arg transport)"/>
    <remap from="/camera_info" to="$(arg camera)/camera_info"/>
  </node>
</launch>
```
  
#### 5-4. Bounding box의 대각거리로 일정거리 유지 (수정, 코드 입력) 
  * 같은 거리에서도 물체의 크기에 따라 Bounding box 크기가 달라지면 동일한 거리유지 불가
  * Bounding box가 대각거리보다 클 때, 먼거리의 물체도 회피 기동 -> 물체의 confidence가 0.75 이상일 경우만 장애물로 인식하게 함
  ```
   if (diagonal_distance2 > 400 && object_center_y1 < 350 && object.confidence >= 0.75)

            ROS_INFO("obstacle");
            ROS_INFO("linear_x: -0.2");
  ```
   
#### 5-5. remap 함수를 이용한 범위 변환
  * Bounding Box의 위치와 크기에 따른 속도 제어
  * diagonal_distance1 (150 ~ 320) ->  linear_x (0.2 ~ 0)
  * frame_x (0 ~ 856) ->  angluar_z (-0.3 ~ 0.3)
  * frame_y (480 ~ 0) ->  linear_z (-0.3 ~ 0.3)
  ```
  void Calculator::calculate_distance() {

    geometry_msgs::Twist move_msg;

    move_msg.linear.x = remap(diagonal_distance1, 150, 320, 0.2, 0);
    if(diagonal_distance1 > 300)
    move_msg.linear.x = -0.2;                                                       				

    if(move_msg.linear.x <= 0.05 && move_msg.linear.x > 0)
    move_msg.linear.x = 0;

    move_msg.linear.z = remap(object_center_y1, image_center_y*2, 0, -0.3, 0.3); 
    move_msg.angular.z = remap(object_center_x1, image_center_x*2, 0, -0.3, 0.3);
    move_msg.angular.x = move_msg.angular.y = move_msg.linear.y = 0;

    move_pub.publish(move_msg);
    ROS_INFO("linear_x : %f", move_msg.linear.x);
    ROS_INFO("linear_z : %f", move_msg.linear.z);
    ROS_INFO("angular_z : %f", move_msg.angular.z);
}
  ```
#### 5-6. 
  * 여러물체를 한 다른 물체로 인식 커다란 물체로 인식하여 회피기동하는 문제 생김 (계단을 보트로, 의자를 소파로, 단상을 다이닝테이블로 인식하는경우 등등)
  * 전방에 대해 인식하는 물체만 회피 가능

## 6. 결과물
```
./rosque_active_tracking.sh
```

영상, 이미지

