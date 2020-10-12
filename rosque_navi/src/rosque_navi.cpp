#include "path.h"

int main(int argc, char** argv)
{
    int path_point;
    ros::init(argc, argv, "BebopController");

    BebopControl bebop();

    ros::AsyncSpinner spinner(4); // Use 4 threads
    spinner.start();
    ros::waitForShutdown();
    return 0;
}
