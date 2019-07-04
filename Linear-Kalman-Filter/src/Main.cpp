#include "Processing.h"
#include "Load_Params.h"
#include "Update.h"
#include "Prediction.h"

int main(int argc, char** argv){

    ros::init(argc,argv,"KalmanFilter");
    ros::NodeHandle nh;     
  
    //Loading the parameters
    Load_Params(nh);
  
    //Subscriber and Publisher for the data. Can be remapped in the launch file to the topic required
    ros::Subscriber Image=nh.subscribe("Measurement_data",100,Update_step);
    ros::Subscriber Imu=nh.subscribe("Prediction_data",100,Prediction_step);
    ros::Publisher fused = nh.advertise<geometry_msgs::PoseStamped>("Filtered_data", 10);

    ros::Rate loop_rate(100);
    while(ros::ok()){
        fused.publish(output);
        // std::cout << CovarhatX << std::endl;
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}       

