# slam-octomap

Tested with Intel Realsense D435i stereo camera. Capable of localizing in GPS denied environment while building a 3-D map of the surrounding. 

Installation Instructions - Ubuntu 16.04 with ROS Kinetic
---------------------------------------------------------

1. First install ROS Kinetic in your system following this guide, prefer Ubuntu 16.04

[Ubuntu Installation](https://aerial-robotics-iitk.gitbook.io/wiki/tutorials/workspace-setup/installing-ubuntu)

[ROS Installation](https://aerial-robotics-iitk.gitbook.io/wiki/tutorials/workspace-setup/ros-setup)

2. Install additional libraries
```
sudo apt-get install ros-kinetic-octomap-ros
```

* If you are using Intel Realsense install SDK and driver first from [here](https://github.com/AerialRobotics-IITK/realsense.git)

3. Setup your workspace

```
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
git clone https://github.com/da-piyushpatel/slam-octomap.git 
cd ~/catkin_ws
catkin build
echo "~/catkin_ws/devel/setup.bash"
```

Sources
-------
The realsense camera is provided with accelerometer and gyroscope, using this algorithm onc can find out cmaera's orientation in 3D space

* [imu_filter_madgwick](https://x-io.co.uk/open-source-imu-and-ahrs-algorithms)

* https://github.com/IntelRealSense/realsenense-ros
* http://wiki.ros.org/imu_filter_madgwick

`roslaunch realsense2_camera rs_camera.launch  unite_imu_method:=copy filters:=pointcloud`

` rosrun imu_filter_madgwick imu_filter_node _use_magnetic_field_msg:=false _publish_debug_topics:=true`

* To know more about the codes and this project see the attached SURGE_report.pdf
