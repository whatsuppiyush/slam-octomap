#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <std_msgs/String.h>
#include <iostream>

sensor_msgs::Imu finalImu;

using namespace std;

void accelCallback(const sensor_msgs::Imu::ConstPtr& msg)
{
    finalImu.header.seq = msg->header.seq;
    finalImu.header.frame_id = "camera_link";

    // finalImu.orientation_covariance << msg->orientation_covariance;
    // finalImu.linear_acceleration_covariance << msg->linear_acceleration_covariance;

    finalImu.linear_acceleration.x = msg->linear_acceleration.x;
    finalImu.linear_acceleration.y = msg->linear_acceleration.y;
    finalImu.linear_acceleration.z = msg->linear_acceleration.z;   

};

void gyroCallback(const sensor_msgs::Imu::ConstPtr& msg)
{
    // finalImu.angular_velocity_covariance << msg.angular_velocity_covariance;

    finalImu.angular_velocity.x = msg->angular_velocity.x;
    finalImu.angular_velocity.y = msg->angular_velocity.y;
    finalImu.angular_velocity.z = msg->angular_velocity.z;
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "realsense_combined_imu");
    ros::NodeHandle(nh);
    ros::Subscriber accel_sub = nh.subscribe("/camera/accel/sample",10,accelCallback);
    ros::Subscriber gyro_sub = nh.subscribe("/camera/gyro/sample",10,gyroCallback);
    ros::Publisher imu_pub = nh.advertise<sensor_msgs::Imu>("/imu/data_raw",100);

    ros::Rate loop_rate(250);

    while(ros::ok())
    {
        finalImu.header.stamp = ros::Time::now();
        imu_pub.publish(finalImu);
        ros::spinOnce();
        loop_rate.sleep();
    }

}