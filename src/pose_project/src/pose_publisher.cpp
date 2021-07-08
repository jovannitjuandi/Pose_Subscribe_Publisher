#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/PoseStamped.h"
#include <boost/thread/thread.hpp>

// TODO: SET THIS UP WITH CLASSES AND AVOID GLOBAL VARIABLES

geometry_msgs::PoseStamped msg;

void getInput(int* rate) {
    ros::NodeHandle n;
	ros::Publisher posepub = n.advertise<geometry_msgs::PoseStamped>("inputthread", 10);
	ros::Rate loop_rate(*rate);

    while (ros::ok()) {
        std::string inputString;
	    std::cout << "Enter a unit of movement: ";
	    std::cin >> inputString;

        if (inputString == "w") 
	    {
		    msg.pose.position.y += 1;
	    } 
	    else if (inputString == "a") 
	    {
		    msg.pose.position.x -= 1;
	    }
	    else if (inputString == "s") 
	    {
		    msg.pose.position.y -= 1;
	    }
	    else if (inputString == "d") 
	    {
		    msg.pose.position.x += 1;
	    }

		ros::spinOnce();
		loop_rate.sleep();
    
    }
}

int main (int argc, char **argv) {
	ros::init(argc, argv, "pose_publisher");

    int rate_b = 10;
    boost::thread thread_b(getInput, &rate_b);

	ros::NodeHandle n;
	ros::Publisher posepub = n.advertise<geometry_msgs::PoseStamped>("posetopic", 1000);
	ros::Rate loop_rate(10);

	// initialize data
	msg.pose.position.x = 0;
	msg.pose.position.y = 0;
	msg.pose.position.z = 0;

	msg.pose.orientation.x = 0;
	msg.pose.orientation.y = 0;
	msg.pose.orientation.z = 0;
	msg.pose.orientation.w = 0;

    msg.header.stamp.sec = 0;
    msg.header.stamp.nsec = 0;

	while (ros::ok()) {
        msg.header.stamp.sec = ros::Time::now().sec;
        msg.header.stamp.nsec = ros::Time::now().nsec;
		posepub.publish(msg);

		ros::spinOnce();
		loop_rate.sleep();
	}

    return 0;
}
