/*
Call Back function for obtaining the measurement vector.
The argument can be changed to that of incoming message
*/

void Update_step(const geometry_msgs::PoseStamped::ConstPtr& measurement){

    //Preproccessing for making the output message ready for publishing. Can be changed/omitted
    std::cout << "HI2" << std::endl;
	Zk << measurement->pose.position.x,measurement->pose.position.y,measurement->pose.position.z;
    
    //For the first value, set initial belief. Can be set to whatever you fancy
    static int ifFirst=1;
    if (ifFirst){
        ifFirst=0;
        Xk <<   measurement->pose.position.x,
                measurement->pose.position.y,
                measurement->pose.position.z,
                0,
                0,
                0;
        return;
    }
    //Calculating new belief of x
    Xk=Xhatk+KGain*(Zk-(Hk*Xhatk));
    std::cout << CovarhatX << std::endl;
    // std::cout << CovarhatX << std::endl;
    //Calculating new covariance of x
    CovarX=CovarhatX-((KGain*Hk)*CovarhatX);
    output=OutputProcess(Xk,*measurement);
}