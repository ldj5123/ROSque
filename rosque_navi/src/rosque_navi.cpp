#include "path.h"

int main(int argc, char** argv)
{
    int path_point;
    ros::init(argc, argv, "BebopController");
    std::cout << "insert path point count : ";
    std::cin >> path_point;
    ROS_INFO("START");

    BebopControl bebop(path_point);

    ros::AsyncSpinner spinner(4); // Use 4 threads
    spinner.start();
    ros::waitForShutdown();
    return 0;
}