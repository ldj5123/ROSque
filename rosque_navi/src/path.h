#ifndef PATH_H
#define PATH_H

#include "ros/ros.h"
#include "std_msgs/Empty.h"
#include "geometry_msgs/Twist.h"
#include "moveit_msgs/DisplayTrajectory.h"

#include <string>
#include <sstream>
#include <chrono>
#include <vector>
#include <math.h>

using std::vector;

#define PI 3.14159265358979
#define millsec     1000

class BebopControl
{
public:
    BebopControl(int pathPoint);

private:
    void target_to_bebop(float x_n, float y_n, float z_n, float yaw_n, float x, float y, float z, float yaw);
    float Quaternion2Yaw(float qz, float qw);

    vector<float> path_x;
    vector<float> path_y;
    vector<float> path_z;
    vector<float> path_w;
    int path_point;
    int path_count;

    ros::NodeHandle n;
    ros::Subscriber path_sub;
    ros::Publisher bebop_cmd;

    void path_callback(const moveit_msgs::DisplayTrajectory msg);
};

BebopControl::BebopControl(int pathPoint)
{
    path_count = 0;
    path_point = pathPoint;
    path_sub = n.subscribe("move_group/display_planned_path", 1, &BebopControl::path_callback, this);		
    bebop_cmd = n.advertise<geometry_msgs::Twist>("bebop/cmd_vel",1, true);

}

void BebopControl::path_callback(const moveit_msgs::DisplayTrajectory msg) {

    int i = 0;          // 현재 포인트
    int i_next = 0;     // 다음 포인트
    int point_size = msg.trajectory[0].multi_dof_joint_trajectory.points.size();    // 이동 동선의 좌표 수
    float qz = 0.0;     // rotation.z를 담기 위한 변수
    float qw = 0.0;     // rotation.w를 담기 위한 변수
    float distance = 0.0;
    ++path_count;       // path_count를 

    for (i = 0; i < point_size; i++) {
        // 만들어진 point_size 만큼 각각 x, y, z, w에 요소 추가
        path_x.push_back(msg.trajectory[0].multi_dof_joint_trajectory.points[i].transforms[0].translation.x);
        path_y.push_back(msg.trajectory[0].multi_dof_joint_trajectory.points[i].transforms[0].translation.y);
        path_z.push_back(msg.trajectory[0].multi_dof_joint_trajectory.points[i].transforms[0].translation.z);
        qz = msg.trajectory[0].multi_dof_joint_trajectory.points[i].transforms[0].rotation.z;
        qw = msg.trajectory[0].multi_dof_joint_trajectory.points[i].transforms[0].rotation.w;
        path_w.push_back(Quaternion2Yaw(qz, qw));
    }
    ROS_INFO("Get the Path, the total size of points is: %d", point_size);
    if (path_count != path_point) return;   // 입력한 path_point만큼 path_plan을 받기위해

    i = 0;
    i_next = 1;

    sleep(0.5); 

    ROS_INFO("Start to follow the path!!");
    while( i_next < path_x.size() )
    {
        distance = sqrtf( (path_x[i_next]-path_x[i])*(path_x[i_next]-path_x[i]) + (path_y[i_next]-path_y[i])*(path_y[i_next]-path_y[i]) + (path_z[i_next]-path_z[i])*(path_z[i_next]-path_z[i]) );
        if(distance <= 0.15)    // 현재의 좌표와 다음 좌표의 거리를 계산해 0.15 이하는 i_next만 증가시키며 건너뜀
            i_next++;
        if(distance > 0.15)
        {
            target_to_bebop(path_x[i_next],path_y[i_next],path_z[i_next],path_w[i_next],path_x[i],path_y[i],path_z[i],path_w[i]);
            i = i_next;
            i_next++;
        }
    }
    ROS_INFO("All of targets were published!!");
    path_x.clear();
    path_y.clear();
    path_z.clear();
    path_w.clear();
    path_count = 0;
    path_point = 0;
    std::cout << "insert path point count : ";
    std::cin >> path_point;
    ROS_INFO("START");
}

void BebopControl::target_to_bebop(float x_n, float y_n, float z_n, float yaw_n, float x, float y, float z, float yaw)
{
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    std::chrono::milliseconds mill = std::chrono::duration_cast<std::chrono::milliseconds>(start - start);
    float z_ = z_n - z;
    float y_ = y_n - y;
    float x_ = x_n - x;
    geometry_msgs::Twist cmdT;
    ROS_INFO("target x : %f\t target y : %f\t target z : %f", x_, y_, z_);
    while(mill.count() < millsec){      // while문을 들어갔을떄부터 bebop_cmd를 1초동안 반복
        std::chrono::system_clock::time_point End = std::chrono::system_clock::now();
        mill = std::chrono::duration_cast<std::chrono::milliseconds>(End - start);

        cmdT.linear.x = x_/8;
        cmdT.linear.y = y_/8;
        cmdT.linear.z = 0;

        cmdT.angular.x = cmdT.angular.y = cmdT.angular.z = 0;
        bebop_cmd.publish(cmdT);
    }
    ROS_INFO("linear x : %f\t linear y : %f\t linear z : %f", cmdT.linear.x, cmdT.linear.y, cmdT.linear.z);
}


float BebopControl::Quaternion2Yaw(float qz, float qw)
{
    return(atan2(2*qz*qw,1-2*qz*qz)*180/PI);
}


#endif
