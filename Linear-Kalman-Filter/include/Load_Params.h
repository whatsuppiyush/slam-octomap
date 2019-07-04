#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <geometry_msgs/PoseStamped.h>
#include <bits/stdc++.h>
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <math.h>
#include <stdio.h>

using namespace Eigen;

/*
Standard matrices for the Kalman Filter
Fk - State-Transition model
Qk - Process-Noise Covariance
Rk - Observation-Noise Covariance
Bk - Control-Input Model
Hk - Observation-Model
*/
MatrixXf Fk;
MatrixXf Qk;
MatrixXf Rk;
MatrixXf Bk;
MatrixXf Hk;

/*
Observation and Measurement Step Vectors/Matrices
Xk - Current state vector(Belief)
Xhatk - Predicted state vector
Zk - Measurement vector
Uk - Control Vector
covarx - Current covariance of X
covarhatx - Predicted covariance of X
KGain - Kalman Gain
*/
MatrixXf Xk,Xhatk; 
MatrixXf Zk,Uk;
MatrixXf CovarX,CovarhatX;
MatrixXf KGain;

void Load_Params(ros::NodeHandle nh){
	
	//Information about rows and columns of the required matrices
	int Hkrows, Hkcolumns;
	int Qkrows, Qkcolumns;
	int Fkrows, Fkcolumns;
	int Bkrows, Bkcolumns;
	int Rkrows, Rkcolumns;
	int Covar_order;
	int Xkorder, Zkorder, Ukorder;
	int KGainr, KGainc;

	//Loading the above information from parameters
	nh.getParam("/KalmanFilter/Hkr",Hkrows);
	nh.getParam("/KalmanFilter/Hkc",Hkcolumns);
	nh.getParam("/KalmanFilter/Qkr",Qkrows);
	nh.getParam("/KalmanFilter/Qkc",Qkcolumns);
	nh.getParam("/KalmanFilter/Fkr",Fkrows);
	nh.getParam("/KalmanFilter/Fkc",Fkcolumns);
	nh.getParam("/KalmanFilter/Bkr",Bkrows);
	nh.getParam("/KalmanFilter/Bkc",Bkcolumns);
	nh.getParam("/KalmanFilter/Rkr",Rkrows);
	nh.getParam("/KalmanFilter/Rkc",Rkcolumns);
	nh.getParam("/KalmanFilter/Cov_order",Covar_order);
	nh.getParam("/KalmanFilter/Xk",Xkorder);
	nh.getParam("/KalmanFilter/Zk",Zkorder);
	nh.getParam("/KalmanFilter/Uk",Ukorder);
	nh.getParam("/KalmanFilter/Kgainr",KGainr);
	nh.getParam("/KalmanFilter/Kgainc",KGainc);

	//Making the matrices of the given size
	Hk.resize(Hkrows,Hkcolumns);
	Qk.resize(Qkrows, Qkcolumns);
	Fk.resize(Fkrows,Fkcolumns);
	Bk.resize(Bkrows,Bkcolumns);
	Rk.resize(Rkrows,Rkcolumns);
	CovarX.resize(Covar_order,Covar_order);
	CovarhatX.resize(Covar_order,Covar_order);
	Xk.resize(Xkorder,1);
	Xhatk.resize(Xkorder,1);
	Zk.resize(Zkorder,1);
	Uk.resize(Ukorder,1);
	KGain.resize(KGainr,KGainc);


	float temp;

	//Loading the given Matrices from the Parameters
	char HkStr[]="/KalmanFilter/Hk00";
	for (int i=0;i<Hkrows;i++){
		for (int j=0;j<Hkcolumns;j++){
			HkStr[16]='0'+i;
			HkStr[17]='0'+j;
			nh.getParam(HkStr,temp);
			Hk(i,j)=temp;
		}
	}

	char QkStr[]="/KalmanFilter/Qk00";	
	for (int i=0;i<Qkrows;i++){
		for (int j=0;j<Qkcolumns;j++){
			QkStr[16]='0'+i;
			QkStr[17]='0'+j;
			nh.getParam(QkStr,temp);
			Qk(i,j)=temp;
		}
	}

	char FkStr[]="/KalmanFilter/Fk00";	
	for (int i=0;i<Fkrows;i++){
		for (int j=0;j<Fkcolumns;j++){
			FkStr[16]='0'+i;
			FkStr[17]='0'+j;
			nh.getParam(FkStr,temp);
			Fk(i,j)=temp;
		}
	}

	char BkStr[]="/KalmanFilter/Bk00";	
	for (int i=0;i<Bkrows;i++){
		for (int j=0;j<Bkcolumns;j++){
			BkStr[16]='0'+i;
			BkStr[17]='0'+j;
			nh.getParam(BkStr,temp);
			Bk(i,j)=temp;
		}
	}

	char RkStr[]="/KalmanFilter/Rk00";	
	for (int i=0;i<Rkrows;i++){
		for (int j=0;j<Rkcolumns;j++){
			RkStr[16]='0'+i;
			RkStr[17]='0'+j;
			nh.getParam(RkStr,temp);
			Rk(i,j)=temp;
		}
	}   

	for (int i=0;i<Covar_order;i++){
		for (int j=0;j<Covar_order;j++){
			CovarX(i,j)=(i==j)?1:0;
		}
	}

	std::cout << Hk << std::endl << std::endl;
	std::cout << Qk << std::endl << std::endl;
	std::cout << Fk << std::endl << std::endl;
	std::cout << Fk*Fk.transpose() << std::endl << std::endl;
	std::cout << Bk << std::endl << std::endl;
	std::cout << Rk << std::endl << std::endl;
	std::cout << CovarX;
}
