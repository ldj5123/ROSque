#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>

#include <stdio.h>
#include <termio.h>

#include <iostream>

int getch()
{
    int ch;

    struct termios buf, save;
    tcgetattr(0, &save);

    buf = save;

    buf.c_lflag &= ~(ICANON|ECHO);

    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;

    tcsetattr(0, TCSAFLUSH, &buf);
    ch = getchar();

    tcsetattr(0, TCSAFLUSH, &save);

    return ch;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "takeoff_and_land");
    ros::NodeHandle nh;

    ros::Publisher takeoff_pub = nh.advertise<std_msgs::Empty>("bebop/takeoff", 1);
    ros::Publisher land_pub = nh.advertise<std_msgs::Empty>("bebop/land", 1);
    ros::Publisher reset_pub = nh.advertise<std_msgs::Empty>("bebop/reset", 1);
    ros::Publisher move_pub = nh.advertise<geometry_msgs::Twist>("bebop/cmd_vel", 1);
    int togle = 1;
    while(ros::ok())
    {
        int input_data = getch();
        
        if(input_data == 32){      // 1이 입력된경우
            if(togle == 1){
                std_msgs::Empty msg;
                takeoff_pub.publish(msg);
                togle = 0;
            } else if (togle == 0){
                std_msgs::Empty msg;
                land_pub.publish(msg);
                togle = 1;
            }
        } else if (input_data == 119){  // w가 입력된경우
            geometry_msgs::Twist move_msg;
            move_msg.linear.x = 0.1;    move_msg.linear.y = 0;  move_msg.linear.z = 0;
            move_msg.angular.x = 0;     move_msg.angular.y = 0; move_msg.angular.z = 0;

            move_pub.publish(move_msg);
        } else if (input_data == 120){  // x가 입력된경우
            geometry_msgs::Twist move_msg;
            move_msg.linear.x = -0.1;   move_msg.linear.y = 0;  move_msg.linear.z = 0;
            move_msg.angular.x = 0;     move_msg.angular.y = 0; move_msg.angular.z = 0;

            move_pub.publish(move_msg);
        } else if (input_data == 115 || input_data == 106){  // s가 입력된경우
            geometry_msgs::Twist move_msg;
            move_msg.linear.x = 0;  move_msg.linear.y = 0;  move_msg.linear.z = 0;
            move_msg.angular.x = 0; move_msg.angular.y = 0; move_msg.angular.z = 0;

            move_pub.publish(move_msg);
        } else if (input_data == 97){  // a가 입력된경우
            geometry_msgs::Twist move_msg;
            move_msg.linear.x = 0;  move_msg.linear.y = 0.1;  move_msg.linear.z = 0;
            move_msg.angular.x = 0; move_msg.angular.y = 0; move_msg.angular.z = 0;

            move_pub.publish(move_msg);
        } else if (input_data == 100){  // d가 입력된경우
            geometry_msgs::Twist move_msg;
            move_msg.linear.x = 0;  move_msg.linear.y = -0.1;  move_msg.linear.z = 0;
            move_msg.angular.x = 0; move_msg.angular.y = 0; move_msg.angular.z = 0;

            move_pub.publish(move_msg);
        } else if (input_data == 117){  // u가 입력된경우
            geometry_msgs::Twist move_msg;
            move_msg.linear.x = 0;  move_msg.linear.y = 0;  move_msg.linear.z = 0.5;
            move_msg.angular.x = 0; move_msg.angular.y = 0; move_msg.angular.z = 0;

            move_pub.publish(move_msg);
        } else if (input_data == 109){  // m가 입력된경우
            geometry_msgs::Twist move_msg;
            move_msg.linear.x = 0;  move_msg.linear.y = 0;  move_msg.linear.z = -0.5;
            move_msg.angular.x = 0; move_msg.angular.y = 0; move_msg.angular.z = 0;

            move_pub.publish(move_msg);
        } else if (input_data == 104){  // h가 입력된경우
            geometry_msgs::Twist move_msg;
            move_msg.linear.x = 0;  move_msg.linear.y = 0;  move_msg.linear.z = 0.0;
            move_msg.angular.x = 0; move_msg.angular.y = 0; move_msg.angular.z = 0.05;

            move_pub.publish(move_msg);
        } else if (input_data == 107){  // k가 입력된경우
            geometry_msgs::Twist move_msg;
            move_msg.linear.x = 0;  move_msg.linear.y = 0;  move_msg.linear.z = 0.0;
            move_msg.angular.x = 0; move_msg.angular.y = 0; move_msg.angular.z = -0.05;

            move_pub.publish(move_msg);
        } else if (input_data == 'r'){  // r이 입력된경우
            std_msgs::Empty msg;
            reset_pub.publish(msg);
            togle = 1;
        }
        ros::spinOnce();
    }

    return 0;
}

// 1을 누르면 이륙      /bebop/takeoff  std_msgs/Empty
// 2를 누르면 착륙      /bebop/land     std_msgs/Empty