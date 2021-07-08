#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/Twist.h"

// TODO: SETUP ORIENTATION FROM DEGREES TO QUATERNIONS

geometry_msgs::Twist twist;
geometry_msgs::PoseStamped previousPose;

void twistConverter (const geometry_msgs::PoseStamped::ConstPtr&msg) {
    auto timeDifference = (msg->header.stamp.sec + msg->header.stamp.sec/(1000000000.0)) - (previousPose.header.stamp.sec + previousPose.header.stamp.nsec/(1000000000.0));

    twist.linear.x = (msg->pose.position.x - previousPose.pose.position.x)/(timeDifference);
    twist.linear.y = (msg->pose.position.y - previousPose.pose.position.y)/(timeDifference);
    twist.linear.z = (msg->pose.position.z - previousPose.pose.position.z)/(timeDifference);

    twist.angular.x = (msg->pose.orientation.x - previousPose.pose.position.x)/(timeDifference);
    twist.angular.y = (msg->pose.orientation.y - previousPose.pose.position.y)/(timeDifference);
    twist.angular.z = (msg->pose.orientation.z - previousPose.pose.position.z)/(timeDifference);

    previousPose.pose.position.x = msg->pose.position.x;
    previousPose.pose.position.y = msg->pose.position.y;
    previousPose.pose.position.z = msg->pose.position.z;

    previousPose.pose.orientation.x = msg->pose.orientation.x;
    previousPose.pose.orientation.y = msg->pose.orientation.y;
    previousPose.pose.orientation.z = msg->pose.orientation.z;

    previousPose.header.stamp.sec = msg->header.stamp.sec; 
    previousPose.header.stamp.nsec = msg->header.stamp.nsec; 
}

int main (int argc, char** argv) {

	ros::init(argc, argv, "twist_service");

	ros::NodeHandle n;
	ros::Subscriber posesub = n.subscribe("posetopic", 1000, twistConverter);
	ros::Publisher twistpub = n.advertise<geometry_msgs::Twist>("twisttopic", 200);
	ros::Rate loop_rate(10);

    twist.linear.x = 0;
    twist.linear.y = 0;
    twist.linear.z = 0;

    twist.angular.x = 0;
    twist.angular.y = 0;
    twist.angular.z = 0;

    while (ros::ok()) {
	    twistpub.publish(twist);

	    ros::spinOnce();
	    loop_rate.sleep();
    }

	return 0;
}
