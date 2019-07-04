cmake_minimum_required(VERSION 2.8.3)
project(localization)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  nav_msgs
  roscpp
  rospy
  sensor_msgs
  std_msgs
  tf
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES localization
#  CATKIN_DEPENDS geometry_msgs nav_msgs roscpp rospy sensor_msgs std_msgs tf
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(realsense_imu_comb_node src/realsense_comb_imu.cpp)
target_link_libraries(realsense_imu_comb_node
  ${catkin_LIBRARIES}
)

add_executable(tf_pub src/tf_publisher.cpp)
target_link_libraries(tf_pub
  ${catkin_LIBRARIES}
)

add_executable(odom_node src/odom_node.cpp)
target_link_libraries(odom_node
  ${catkin_LIBRARIES}
)
