/*
Call Back function for obtaining the control vector
The argument can be changed to that of incoming message
*/

void Prediction_step(const sensor_msgs::Imu::ConstPtr& control){
     
    Uk=UkProcess(*control);

    //Predicting belief of x
    Xhatk=Fk*Xk+Bk*Uk;

    //Predicting covariance of x
    CovarhatX=(Fk*CovarX)*Fk.transpose()+Qk;

    //Calculating kalman gain
    MatrixXf temp2,temp3;
    temp2=(Hk*CovarhatX)*Hk.transpose()+Rk;
    temp3=temp2.inverse();
    KGain=(CovarhatX*Hk.transpose())*temp3;

    std::cout << "Yo" << std::endl;

    // std::cout << "Predict" << std::endl;
}