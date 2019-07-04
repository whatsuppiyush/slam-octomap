cmake_minimum_required(VERSION 2.8.3)
project(filter)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  sensor_msgs
  std_msgs
  cmake_modules


)

find_package(Eigen REQUIRED)
#find_package(OpenCV REQUIRED)
#find_package(Boost REQUIRED COMPONENTS system)
#find_package(PCL REQUIRED COMPONENTS common io)

catkin_package(
   DEPENDS Eigen
  INCLUDE_DIRS include
   CATKIN_DEPENDS roscpp
)
include_directories(include
                    ${catkin_INCLUDE_DIRS}
                    ${Eigen_INCLUDE_DIRS})

## Declare a cpp executable
add_executable(KalmanFilter src/Main.cpp)
target_link_libraries(KalmanFilter
    ${catkin_LIBRARIES})
