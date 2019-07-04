#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <math.h>
#include <stdio.h>
#include <sensor_msgs/Imu.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/PoseStamped.h>

using namespace std;

// Eigen::Quaternionf cam2world;
// Eigen::Matrix<float ,3,3> R;
// Eigen::Vector3f accel_global,accel_local,vel_curr,vel_last,curr_pose;
ros::Time current_time, last_time;

ros::Publisher odom_pub;
// geometry_msgs::TransformStamped odom_trans;
geometry_msgs::PoseStamped odom;

// void imuCallback(const sensor_msgs::Imu::ConstPtr& msg)
// {
//     current_time = ros::Time::now();
//     tf::Quaternion q(msg->orientation.x,msg->orientation.y,msg->orientation.z,msg->orientation.w);
//     q.normalize();
//     cam2world = Eigen::Quaternionf(q.w(),q.x(),q.y(),q.z());
//     R = cam2world.toRotationMatrix();

//     // convert accel to world frame
//     accel_local<<msg->linear_acceleration.x,
//                  msg->linear_acceleration.y,
//                  msg->linear_acceleration.z;

//     accel_global = R*accel_local;
//     accel_global(2,0) = accel_global(2,0) - 9.81;
//     double dt = (current_time - last_time).toSec();
//     // vel_curr(0,0) = vel_curr(0,0) + accel_global(0,0)*dt;
//     // vel_curr(1,0) = vel_curr(1,0) + accel_global(1,0)*dt;
//     // vel_curr(2,0) = vel_curr(2,0) + accel_global(2,0)*dt;

//     // curr_pose(0,0) = curr_pose(0,0) + vel_curr(0,0)*dt;
//     // curr_pose(1,0) = curr_pose(1,0) + vel_curr(1,0)*dt;
//     // curr_pose(2,0) = curr_pose(2,0) + vel_curr(2,0)*dt;

//     odom.header.stamp = msg->header.stamp;
//     odom.header.frame_id = "camera_link";
//     // odom.pose.position.x = curr_pose(0,0);
//     // odom.pose.position.y = curr_pose(1,0);
//     // odom.pose.position.z = curr_pose(2,0);
//     odom.pose.orientation.x = msg->orientation.x;
//     odom.pose.orientation.y = msg->orientation.y;
//     odom.pose.orientation.z = msg->orientation.z;
//     odom.pose.orientation.w = msg->orientation.w;

//     last_time = current_time;

//     odom_trans.header.stamp = msg->header.stamp;
//     odom_trans.header.frame_id = "odom";
//     odom_trans.child_frame_id = "camera_link";
//     odom_trans.transform.rotation.x = msg->orientation.x;
//     odom_trans.transform.rotation.y = msg->orientation.y;
//     odom_trans.transform.rotation.z = msg->orientation.z;
//     odom_trans.transform.rotation.w = msg->orientation.w;
//     // cout<<odom_trans.transform.rotation.z<<endl;

//     // odom_trans.transform.translation.x = curr_pose(0,0);
//     // odom_trans.transform.translation.y = curr_pose(1,0);
//     // odom_trans.transform.translation.z = curr_pose(2,0);


// }

void poseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    odom.header.seq = msg->header.seq;
    odom.header.stamp = msg->header.stamp;
    odom.header.frame_id = "camera_link";

    odom.pose.position.x = msg->pose.position.x;
    odom.pose.position.y = msg->pose.position.y;
    odom.pose.position.z = msg->pose.position.z;
}

void imuCallback(const sensor_msgs::Imu::ConstPtr& msg)
{
    odom.pose.orientation.x = msg->orientation.x;
    odom.pose.orientation.y = msg->orientation.y;
    odom.pose.orientation.z = msg->orientation.z;
    odom.pose.orientation.w = msg->orientation.w;
}
int main(int argc, char** argv){
  ros::init(argc, argv, "odometry_publisher");
  ros::NodeHandle n;
  ros::Rate loop_rate(250);
  tf::TransformBroadcaster odom_broadcaster;    
  ros::Subscriber imu_sub = n.subscribe("/imu/data",10,imuCallback);
  ros::Subscriber pose_sub = n.subscribe("/orb_slam2_rgbd/pose",10,poseCallback);
  odom_pub = n.advertise<geometry_msgs::PoseStamped>("/camera/odom_raw", 50);
  current_time = ros::Time::now();
  last_time = ros::Time::now();
    while(ros::ok())
    {
        // odom_broadcaster.sendTransform(odom_trans);
        odom_pub.publish(odom);
        ros::spinOnce();
        loop_rate.sleep();
    }

}