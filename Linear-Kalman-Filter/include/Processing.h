#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <bits/stdc++.h>
#include <ros/ros.h>
#include <math.h>
#include <stdio.h>

//Necessary includes for the required messages.
#include <sensor_msgs/Imu.h>
#include <geometry_msgs/PoseStamped.h>

using namespace Eigen;

//Output to be published. Can be of different type for different needs
geometry_msgs::PoseStamped output;


/*
The Following functions are for processing the various vectors. Please change them according to needs
*/

//Function for the preprocessing of the control vector. Takes the control message(control) and returns Uk(result)
MatrixXf UkProcess(sensor_msgs::Imu control){
	
	/*
	Miscellaneous vectors/matrices for converting incoming data into a useable form.
	Can be omitted/changed according to needs  
	*/
	MatrixXf g(3,1);
	MatrixXf imutemp(3,1);  

	MatrixXf result(3,1);

    float Ax,Ay,Az;
    float Angx,Angy,Angz;    
    Quaternionf q,qrev;
    q = Quaternionf(control.orientation.w, control.orientation.x, control.orientation.y, control.orientation.z);
    MatrixXf rotmat = q.toRotationMatrix();
    MatrixXf rotmat2=rotmat.inverse();

    Ax=control.linear_acceleration.x;
    Ay=control.linear_acceleration.y;
    Az=control.linear_acceleration.z;
    imutemp << Ax,Ay,Az;
    g << 0,0,-9.8;
    result =imutemp+rotmat2*g;
    return result;
}

//Function for the preprocessing of the measurement vector. Takes the measurement message(measurement) and returns Zk(result)
MatrixXf ZkProcess(const geometry_msgs::PoseStamped measurement){
	
	MatrixXf result;
	result << measurement.pose.position.x,measurement.pose.position.y,measurement.pose.position.z;
	return result;
}

//Function for the preprocessing of the output message. Takes the measurement message(measure) and Belief(Xk) and returns output message(result)
geometry_msgs::PoseStamped OutputProcess (MatrixXf Belief,geometry_msgs::PoseStamped measure){

	geometry_msgs::PoseStamped result;

	result.header.stamp=measure.header.stamp;
    result.header.seq=measure.header.seq;
    result.header.frame_id=measure.header.frame_id;
    result.pose.orientation.x=measure.pose.orientation.x;
    result.pose.orientation.y=measure.pose.orientation.y;
    result.pose.orientation.z=measure.pose.orientation.z;
    result.pose.orientation.w=measure.pose.orientation.w;
    
    result.pose.position.x=Belief(0,0);
    result.pose.position.y=Belief(1,0);
    result.pose.position.z=Belief(2,0);

    return result;
}

