#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/Twist.h"

geometry_msgs::Twist twist;

void twistConverter (const geometry_msgs::PoseStamped::ConstPtr&msg) {
	ROS_INFO("Coordinate: [x: %.2f] [y: %.2f] [z: %.2f]", msg->pose.position.x, msg->pose.position.y, msg->pose.position.z);
}

int main (int argc, char** argv) {

	ros::init(argc, argv, "twist_service");

	ros::NodeHandle n;
	ros::Subscriber posesub = n.subscribe("posetopic", 1000, twistConverter);
	ros::Publisher posepub = n.advertise<geometry_msgs::PoseStamped>("posetopic", 1000);
	ros::Rate loop_rate(10);

	return 1;
}
