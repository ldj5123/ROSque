#include "calculator.h"

Calculator::Calculator(int argc, char **argv, const char *target_object)
{
    this->init_argc = argc;
    this->init_argv = argv;
    this->target_object = target_object;
    this->diagonal_distance1 = 0;
    this->image_center_x = 856/2;
    this->image_center_y = 480/2;
}

void Calculator::node()
{
    ros::init(init_argc, init_argv, "calculate_Object");
    ros::NodeHandle nh;

    object_sub = nh.subscribe("/dnn_objects", 1, &Calculator::object_callback, this);
    move_pub = nh.advertise<geometry_msgs::Twist>("/bebop/cmd_vel", 1);
    ros::spin();
}

void Calculator::object_callback(const dnn_detect::DetectedObjectArray::ConstPtr &msg)
{
    int arr_size = msg->objects.size();

    for(int i = 0; i <arr_size; i++)
    {
        dnn_detect::DetectedObject object;
        object = msg -> objects.at(i);

         = sqrt(pow(object.x_max - object.x_min, 2) + pow(object.y_max - object.y_min,2)); // object bounding box 대각거리 계산

        system("clear screen");
        this->object_center_x1 = (object.x_max - object.x_min)/2 + object.x_min;
        this->object_center_y1 = (object.y_max - object.y_min)/2 + object.y_min;
        if (diagonal_distance > 400 && object_center_y1 < 350 && object.confidence >= 0.75) {

            ROS_INFO("obstacle");
            ROS_INFO("linear_x: -0.2");
            geometry_msgs::Twist move_msg;

            move_msg.linear.x = -0.2;  // 장애물 인식 후진
            move_msg.linear.y = move_msg.linear.z = 0;
            move_msg.angular.x = move_msg.angular.y = move_msg.angular.z = 0;

            move_pub.publish(move_msg);

            ROS_INFO("diagonal_distance : %d", diagonal_distance);
            ROS_INFO("%s, %f", object.class_name.c_str(), object.confidence);
        }else if(object.class_name == this->target_object) {

            diagonal_distance = sqrt(pow(object.x_max - object.x_min, 2) + pow(object.y_max - object.y_min,2));

            ROS_INFO("object_center_x : %d", object_center_x1);
            ROS_INFO("object_center_y : %d", object_center_y1);
            ROS_INFO("diagonal_distance : %d", diagonal_distance);
            ROS_INFO("%s, %f", object.class_name.c_str(), object.confidence);
            calculate_distance();
        }
    }
}

void Calculator::calculate_distance() {

    geometry_msgs::Twist move_msg;

    move_msg.linear.x = remap(diagonal_distance1, 150, 320, 0.2, 0); // 전진 후진  150 320
    if(diagonal_distance1 > 300)
    move_msg.linear.x = -0.2;                                                       				

    if(move_msg.linear.x <= 0.1 && move_msg.linear.x > 0)  // 일정거리 유지되면 정지
    move_msg.linear.x = 0;

    move_msg.linear.z = remap(object_center_y1, image_center_y*2, 0, -0.3, 0.3); // 상승 하강
    move_msg.angular.z = remap(object_center_x1, image_center_x*2, 0, -0.3, 0.3); // 좌우 회전
    move_msg.angular.x = move_msg.angular.y = move_msg.linear.y = 0;

    move_pub.publish(move_msg);
    ROS_INFO("linear_x : %f", move_msg.linear.x);
    ROS_INFO("linear_z : %f", move_msg.linear.z);
    ROS_INFO("angular_z : %f", move_msg.angular.z);
}

float Calculator::remap(float center, float image_max, float image_min, float speed_max, float speed_min)
{
    return ((center - image_min) / (image_max - image_min)) * (speed_max-speed_min) + (speed_min); // 선형보간법
    // new_value = ( (old_value - old_min) / (old_max - old_min) ) * (new_max - new_min) + new_min
}
