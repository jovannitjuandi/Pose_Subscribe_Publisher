#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/PoseStamped.h"

void poseCallback (const geometry_msgs::PoseStamped::ConstPtr&msg) {
	ROS_INFO("Coordinate: [x: %.2f] [y: %.2f] [z: %.2f]", msg->pose.position.x, msg->pose.position.y, msg->pose.position.z);
}

int main (int argc, char** argv) {
	ros::init(argc, argv, "pose_subscriber");

	ros::NodeHandle n;
	ros::Subscriber posesub = n.subscribe("posetopic", 1000, poseCallback);

	ros::spin();

	return 0;
}
