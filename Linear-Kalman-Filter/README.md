## Linear Kalman Filter Algorithm
This is a C++ implementation of the Linear Kalman Filter, designed for use with the ROS Framework. Even though the code has been written for a specific use case, it can be used anywhere with a few minor changes. It uses the Eigen library for the matrix math, so make sure you have that installed. See : [Getting started with Eigen](https://eigen.tuxfamily.org/dox/GettingStarted.html)

Please read [Bzarg's website](http://www.bzarg.com/p/how-a-kalman-filter-works-in-pictures/) to know the basics of the working of the Kalman Filter algorithm.It is an excellent website and the working of the Kalman Filter has been explained pretty nicely. All the variable names used are taken from this website.

To use this filter, make a new workspace and clone the files into the src folder. Make sure you are in the root directory
    
    mkdir -p ~/Filter/src
    cd ~/Filter/
    catkin build
    cd src
    git clone https://github.com/Kshitij1K/Linear-Kalman-Filter/
    
Now the filter has to be modified for your use case. You need to make changes to the CMakeLists.txt, Params.yaml, Main.cpp, Prediction.h, Update.h, Processing.h files. 

###### Changes to the CMakeLists.txt
In the following code (Line 4) 
    
    find_package(catkin REQUIRED COMPONENTS
    geometry_msgs
    roscpp
    sensor_msgs
    std_msgs
    cmake_modules


    )
    
add the dependencies required by your sensors.

###### Changes to Params.yaml
You need to change every parameter here, according to your sensor model. All the parameters are in the form of matrices, however they have been written linearly in the YAML file. Detailed instructions are commented in the YAML file.

###### Changes to Main.cpp
In the line 17, change the message type inside the angular brackets <> to whatever message type you want to publish.

###### Changes to Prediction.h
In the line 6, change the argument of the function to whatever message type you are going to use for the prediction step. It should be a constant pointer.

###### Changes to Update.h
In the line 6, change the argument of the function to whatever message type you are going to use for the update step. It should be a constant pointer.

###### Changes to Processing.h
In this file, you need to do the following
1. Add the necessary includes for the messages used in prediction, measurement, and update steps.(After line 11)
2. Declare the output message, by changing it to whatever message type you want to publish (line 16)
3. Change the functions UkProcess, ZkProcess and OutputProcess functions. These functions basically take the data in sensor messages, put them in matrix form, and return the matrices(UkProcess and ZkProcess) and vice-versa(OutputProcess). In case any processing on the messages is required, add them in the corresponding functions. (I have done some processing in the UkProcess and OutputProcess functions, remove those if necessary)

###### Changes to KF.launch 
In line 6,7,8 change the remappings of Measurement_data, Prediction_data  and Filtered_data to the corresponding topics which you are going to subscribe/publish. Measurement_data should be remapped to the topic on which data for the measurement step is going to be recieved, Prediction_data should be remapped to the topic on which data for the prediction step is going to be recieved and Filtered_data should be remapped to the topic on which you are going to publish the filtered data

After all these changes have been made, you can build and launch the filter using the following commands. Make sure you are in the root directory

    cd Filter
    catkin build
    source devel/setup.bash
    roslaunch filter KF.launch
    
And you are good to go! If you have any problems, please open a new issue on this repository
    
