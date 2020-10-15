#ifndef CALCULATE_DISTANCE_CPP_CALCULATOR_H
#define CALCULATE_DISTANCE_CPP_CALCULATOR_H

#include <ros/ros.h>    
#include <dnn_detect/DetectedObject.h>
#include <dnn_detect/DetectedObjectArray.h>
#include <cmath>
#include <geometry_msgs/Twist.h>

class Calculator {
    private:
        int init_argc;
        char** init_argv;

        const char* target_object;

        int image_center_x;
        int image_center_y;
        int object_center_x1;
        int object_center_y1;
        int diagonal_distance1;
        int diagonal_distance2;

        ros::Subscriber object_sub;
        ros::Publisher move_pub;

    public:
        Calculator (int argc, char** argv, const char* target_object);
        void node();
        void object_callback(const dnn_detect::DetectedObjectArray::ConstPtr& msg);
        void calculate_distance();
        float remap(float center, float image_max, float image_min, float speed_max, float speed_min);
};

#endif //CALCULATE_DISTANCE_CPP_CALCULATOR_H
