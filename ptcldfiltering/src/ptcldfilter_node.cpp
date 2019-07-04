#include <ros/ros.h>
#include <iostream>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl_msgs/PolygonMesh.h>

ros::Publisher ptcld_pub;

void ptcldCallback(const sensor_msgs::PointCloud2ConstPtr& msg)
{
     // Convert the sensor_msgs/PointCloud2 data to pcl/PointCloud
    pcl::PointCloud<pcl::PointXYZ>::Ptr
        cloud(new pcl::PointCloud<pcl::PointXYZ> ()),
        cloud_filtered(new pcl::PointCloud<pcl::PointXYZ> ());
    pcl::fromROSMsg (*msg, *cloud);

    pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
    sor.setInputCloud (cloud);
    sor.setMeanK (50);
    sor.setStddevMulThresh (1.0);
    sor.filter (*cloud_filtered);

    sensor_msgs::PointCloud2::Ptr
        cloud_filtered2(new sensor_msgs::PointCloud2 ());
    pcl::toROSMsg (*cloud_filtered, *cloud_filtered2);

    // Publish the dataSize 
    ptcld_pub.publish (cloud_filtered2);
}

int main(int argc,char** argv)
{
    ros::init(argc,argv,"ptcldfilter_node");
    ros::NodeHandle(nh);
    ros::Rate loop_rate(5);

    ros::Subscriber ptcld_sub = nh.subscribe("/camera/depth/color/points",1,ptcldCallback);
    ptcld_pub = nh.advertise<sensor_msgs::PointCloud2>("/camera/depth/color/filter/points",10);
    while(ros::ok())
    {
        ros::spinOnce();
        loop_rate.sleep();
    }
}