#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/PoseStamped.h"

int main (int argc, char **argv) {
	ros::init(argc, argv, "pose_publisher");

	ros::NodeHandle n;
	ros::Publisher posepub = n.advertise<geometry_msgs::PoseStamped>("posetopic", 1000);
	ros::Rate loop_rate(10);

	geometry_msgs::PoseStamped msg;

	// initialize data
	msg.pose.position.x = 0;
	msg.pose.position.y = 0;
	msg.pose.position.z = 0;

	msg.pose.orientation.x = 0;
	msg.pose.orientation.y = 0;
	msg.pose.orientation.z = 0;
	msg.pose.orientation.w = 0;

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
		
		msg.header.frame_id = "frame name";

		// publish to topic
		posepub.publish(msg);

		// in case of call back
		ros::spinOnce();

		// makes up for the rest of the time to get to 10Hz
		// as specified in ros::Rate
		loop_rate.sleep();
	}
}
