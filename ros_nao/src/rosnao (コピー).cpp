#include "ros/ros.h"
#include<iostream>
using namespace std;
#include <naoqi_bridge_msgs/JointAnglesWithSpeedActionGoal.h>
#include <sensor_msgs/JointState.h>
#include <cmath>

void set_array(double src[17], double dst[17])
{
  for(int i = 0; i < 17; ++i)
  {
    dst[i] = src[i];
  }
} 


int main(int argc, char** argv)
{ 
  ros::init(argc, argv, "rosnao"); 
  ros::NodeHandle n;
  ros::Publisher pb = n.advertise<naoqi_bridge_msgs::JointAnglesWithSpeedActionGoal>("/nao_robot/pose/joint_angles_action/goal", 1000); 
  ros::Rate loop_rate(10);

	double begin =ros::Time::now().toSec();
	double Now =ros::Time::now().toSec();
	double t;//経過時間
	int MotironNumber=0;//現在のモーション番号
	const int MaxMotironNumber = 6;
	const int JointNumber =26;//制御関節数 
	double keys[JointNumber][MaxMotironNumber];
	double times[MaxMotironNumber],Speed[MaxMotironNumber];
	//目標関節角の定義
	double goal_angle[JointNumber];



/////////////////////////////////////////////////////////////////////
times[0] = 1;
times[1] = 2;
times[2] = 3.2;
times[3] = 3.4;
times[4] = 4.8;
times[5] = 6.6;

//names.push_back("HeadPitch");
//times[0].arraySetSize(6);
//keysarraySetSize(6);

//times[0][0] = 1;
keys[0][0] = 0.0367741;
//times[0][1] = 2;
keys[0][1] = 0.061318;
//times[0][2] = 3.2;
keys[0][2] = 0.0291041;
//times[0][3] = 3.6;
keys[0][3] = 0.033706;
//times[0][4] = 4.8;
keys[0][4] = 0.0291041;
//times[0][5] = 6.6;
keys[0][5] = 0.0367741;

//names.push_back("HeadYaw");
//times[1].arraySetSize(6);
//keysarraySetSize(6);

//times[1][0] = 1;
keys[1][0] = -0.174919;
//times[1][1] = 2;
keys[1][1] = -0.372804;
//times[1][2] = 3.2;
keys[1][2] = -0.184122;
//times[1][3] = 3.6;
keys[1][3] = -0.395814;
//times[1][4] = 4.8;
keys[1][4] = -0.184122;
//times[1][5] = 6.6;
keys[1][5] = -0.174919;

//names.push_back("LAnklePitch");
//times[2].arraySetSize(6);
//keysarraySetSize(6);

//times[2][0] = 1;
keys[2][0] = -0.205598;
//times[2][1] = 2;
keys[2][1] = 0.052114;
//times[2][2] = 3.2;
keys[2][2] = -0.372804;
//times[2][3] = 3.6;
keys[2][3] = 0.521518;
//times[2][4] = 4.8;
keys[2][4] = -0.372804;
//times[2][5] = 6.6;
keys[2][5] = -0.205598;

//names.push_back("LAnkleRoll");
//times[3].arraySetSize(6);
//keysarraySetSize(6);

//times[3][0] = 1;
keys[3][0] = -0.0168321;
//times[3][1] = 2;
keys[3][1] = -0.246933;
//times[3][2] = 3.2;
keys[3][2] = -0.254602;
//times[3][3] = 3.6;
keys[3][3] = -0.228525;
//times[3][4] = 4.8;
keys[3][4] = -0.254602;
//times[3][5] = 6.6;
keys[3][5] = -0.0168321;

//names.push_back("LElbowRoll");
//times[4].arraySetSize(6);
//keysarraySetSize(6);

//times[4][0] = 1;
keys[4][0] = -0.661111;
//times[4][1] = 2;
keys[4][1] = -0.670316;
//times[4][2] = 3.2;
keys[4][2] = -0.656511;
//times[4][3] = 3.6;
keys[4][3] = -0.256136;
//times[4][4] = 4.8;
keys[4][4] = -0.656511;
//times[4][5] = 6.6;
keys[4][5] = -0.661111;

//names.push_back("LElbowYaw");
//times[5].arraySetSize(6);
//keysarraySetSize(6);

//times[5][0] = 1;
keys[5][0] = -2.08567;
//times[5][1] = 2;
keys[5][1] = -2.07555;
//times[5][2] = 3.2;
keys[5][2] = -2.08567;
//times[5][3] = 3.6;
keys[5][3] = -2.08567;
//times[5][4] = 4.8;
keys[5][4] = -2.08567;
//times[5][5] = 6.6;
keys[5][5] = -2.08567;

//names.push_back("LHand");
//times[6].arraySetSize(6);
//keysarraySetSize(6);

//times[6][0] = 1;
keys[6][0] = 0.986;
//times[6][1] = 2;
keys[6][1] = 0.9856;
//times[6][2] = 3.2;
keys[6][2] = 0.9856;
//times[6][3] = 3.6;
keys[6][3] = 0.9868;
//times[6][4] = 4.8;
keys[6][4] = 0.9856;
//times[6][5] = 6.6;
keys[6][5] = 0.986;

//names.push_back("LHipPitch");
//times[7].arraySetSize(6);
//keysarraySetSize(6);

//times[7][0] = 1;
keys[7][0] = 0.154976;
//times[7][1] = 2;
keys[7][1] = -0.130348;
//times[7][2] = 3.2;
keys[7][2] = -0.759288;
//times[7][3] = 3.6;
keys[7][3] = -0.550664;
//times[7][4] = 4.8;
keys[7][4] = -0.759288;
//times[7][5] = 6.6;
keys[7][5] = 0.154976;

//names.push_back("LHipRoll");
//times[8].arraySetSize(6);
//keysarraySetSize(6);

//times[8][0] = 1;
keys[8][0] = -0.00149202;
//times[8][1] = 2;
keys[8][1] = 0.0429941;
//times[8][2] = 3.2;
keys[8][2] = 0.075208;
//times[8][3] = 3.6;
keys[8][3] = 0.0138481;
//times[8][4] = 4.8;
keys[8][4] = 0.075208;
//times[8][5] = 6.6;
keys[8][5] = -0.00149202;

//names.push_back("LHipYawPitch");
//times[9].arraySetSize(6);
//keysarraySetSize(6);

//times[9][0] = 1;
keys[9][0] = -0.28068;
//times[9][1] = 2;
keys[9][1] = -0.360449;
//times[9][2] = 3.2;
keys[9][2] = -0.291418;
//times[9][3] = 3.6;
keys[9][3] = -0.0996681;
//times[9][4] = 4.8;
keys[9][4] = -0.291418;
//times[9][5] = 6.6;
keys[9][5] = -0.28068;

//names.push_back("LKneePitch");
//times[10].arraySetSize(6);
//keysarraySetSize(6);

//times[10][0] = 1;
keys[10][0] = 0.269941;
//times[10][1] = 2;
keys[10][1] = 0.25767;
//times[10][2] = 3.2;
keys[10][2] = 1.36982;
//times[10][3] = 3.6;
keys[10][3] = 0.141086;
//times[10][4] = 4.8;
keys[10][4] = 1.36982;
//times[10][5] = 6.6;
keys[10][5] = 0.269941;

//names.push_back("LShoulderPitch");
//times[11].arraySetSize(6);
//keysarraySetSize(6);

//times[11][0] = 1;
keys[11][0] = 1.67355;
//times[11][1] = 2;
keys[11][1] = 1.79781;
//times[11][2] = 3.2;
keys[11][2] = 1.81774;
//times[11][3] = 3.6;
keys[11][3] = 2.08567;
//times[11][4] = 4.8;
keys[11][4] = 1.81774;
//times[11][5] = 6.6;
keys[11][5] = 1.67355;

//names.push_back("LShoulderRoll");
//times[12].arraySetSize(6);
//keysarraySetSize(6);

//times[12][0] = 1;
keys[12][0] = 0.0705221;
//times[12][1] = 2;
keys[12][1] = 0.983252;
//times[12][2] = 3.2;
keys[12][2] = 0.562937;
//times[12][3] = 3.6;
keys[12][3] = 0.952573;
//times[12][4] = 4.8;
keys[12][4] = 0.562937;
//times[12][5] = 6.6;
keys[12][5] = 0.0705221;

//names.push_back("LWristYaw");
//times[13].arraySetSize(6);
//keysarraySetSize(6);

//times[13][0] = 1;
keys[13][0] = 0.196309;
//times[13][1] = 2;
keys[13][1] = 0.0674542;
//times[13][2] = 3.2;
keys[13][2] = 0.030638;
//times[13][3] = 3.6;
keys[13][3] = 0.05058;
//times[13][4] = 4.8;
keys[13][4] = 0.030638;
//times[13][5] = 6.6;
keys[13][5] = 0.196309;

//names.push_back("RAnklePitch");
//times[14].arraySetSize(6);
//keysarraySetSize(6);

//times[14][0] = 1;
keys[14][0] = -0.326699;
//times[14][1] = 2;
keys[14][1] = -0.16563;
//times[14][2] = 3.2;
keys[14][2] = -0.412605;
//times[14][3] = 3.6;
keys[14][3] = -0.412605;
//times[14][4] = 4.8;
keys[14][4] = -0.412605;
//times[14][5] = 6.6;
keys[14][5] = -0.326699;

//names.push_back("RAnkleRoll");
//times[15].arraySetSize(6);
//keysarraySetSize(6);

//times[15][0] = 1;
keys[15][0] = 0.122762;
//times[15][1] = 2;
keys[15][1] = -0.208583;
//times[15][2] = 3.2;
keys[15][2] = -0.331302;
//times[15][3] = 3.6;
keys[15][3] = -0.331302;
//times[15][4] = 4.8;
keys[15][4] = -0.331302;
//times[15][5] = 6.6;
keys[15][5] = 0.122762;

//names.push_back("RElbowRoll");
//times[16].arraySetSize(6);
//keysarraySetSize(6);

//times[16][0] = 1;
keys[16][0] = 0.569155;
//times[16][1] = 2;
keys[16][1] = 0.553816;
//times[16][2] = 3.2;
keys[16][2] = 0.569155;
//times[16][3] = 3.6;
keys[16][3] = 0.553816;
//times[16][4] = 4.8;
keys[16][4] = 0.569155;
//times[16][5] = 6.6;
keys[16][5] = 0.569155;

//names.push_back("RElbowYaw");
//times[17].arraySetSize(6);
//keysarraySetSize(6);

//times[17][0] = 1;
keys[17][0] = 1.68736;
//times[17][1] = 2;
keys[17][1] = 1.6981;
//times[17][2] = 3.2;
keys[17][2] = 1.6981;
//times[17][3] = 3.6;
keys[17][3] = 1.70423;
//times[17][4] = 4.8;
keys[17][4] = 1.6981;
//times[17][5] = 6.6;
keys[17][5] = 1.68736;

//names.push_back("RHand");
//times[18].arraySetSize(6);
//keysarraySetSize(6);

//times[18][0] = 1;
keys[18][0] = 0.0944;
//times[18][1] = 2;
keys[18][1] = 0.1032;
//times[18][2] = 3.2;
keys[18][2] = 0.1032;
//times[18][3] = 3.6;
keys[18][3] = 0.1032;
//times[18][4] = 4.8;
keys[18][4] = 0.1032;
//times[18][5] = 6.6;
keys[18][5] = 0.0944;

//names.push_back("RHipPitch");
//times[19].arraySetSize(6);
//keysarraySetSize(6);

//times[19][0] = 1;
keys[19][0] = -0.0813439;
//times[19][1] = 2;
keys[19][1] = -0.385075;
//times[19][2] = 3.2;
keys[19][2] = -0.464844;
//times[19][3] = 3.6;
keys[19][3] = -0.467912;
//times[19][4] = 4.8;
keys[19][4] = -0.464844;
//times[19][5] = 6.6;
keys[19][5] = -0.0813439;

//names.push_back("RHipRoll");
//times[20].arraySetSize(6);
//keysarraySetSize(6);

//times[20][0] = 1;
keys[20][0] = -0.269941;
//times[20][1] = 2;
keys[20][1] = 0.075208;
//times[20][2] = 3.2;
keys[20][2] = 0.090548;
//times[20][3] = 3.6;
keys[20][3] = 0.0859461;
//times[20][4] = 4.8;
keys[20][4] = 0.090548;
//times[20][5] = 6.6;
keys[20][5] = -0.269941;

//names.push_back("RHipYawPitch");
//times[21].arraySetSize(6);
//keysarraySetSize(6);

//times[21][0] = 1;
keys[21][0] = -0.28068;
//times[21][1] = 2;
keys[21][1] = -0.360449;
//times[21][2] = 3.2;
keys[21][2] = -0.291418;
//times[21][3] = 3.6;
keys[21][3] = -0.0996681;
//times[21][4] = 4.8;
keys[21][4] = -0.291418;
//times[21][5] = 6.6;
keys[21][5] = -0.28068;

//names.push_back("RKneePitch");
//times[22].arraySetSize(6);
//keysarraySetSize(6);

//times[22][0] = 1;
keys[22][0] = 0.602905;
//times[22][1] = 2;
keys[22][1] = 0.675003;
//times[22][2] = 3.2;
keys[22][2] = 0.972599;
//times[22][3] = 3.6;
keys[22][3] = 0.971065;
//times[22][4] = 4.8;
keys[22][4] = 0.972599;
//times[22][5] = 6.6;
keys[22][5] = 0.602905;

//names.push_back("RShoulderPitch");
//times[23].arraySetSize(6);
//keysarraySetSize(6);

//times[23][0] = 1;
keys[23][0] = 1.76875;
//times[23][1] = 2;
keys[23][1] = 1.74267;
//times[23][2] = 3.2;
keys[23][2] = 1.75034;
//times[23][3] = 3.6;
keys[23][3] = 1.75646;
//times[23][4] = 4.8;
keys[23][4] = 1.75034;
//times[23][5] = 6.6;
keys[23][5] = 1.76875;

//names.push_back("RShoulderRoll");
//times[24].arraySetSize(6);
//keysarraySetSize(6);

//times[24][0] = 1;
keys[24][0] = -0.274628;
//times[24][1] = 2;
keys[24][1] = -0.185656;
//times[24][2] = 3.2;
keys[24][2] = -0.20253;
//times[24][3] = 3.6;
keys[24][3] = -0.176453;
//times[24][4] = 4.8;
keys[24][4] = -0.20253;
//times[24][5] = 6.6;
keys[24][5] = -0.274628;

//names.push_back("RWristYaw");
//times[25].arraySetSize(6);
//keysarraySetSize(6);

//times[25][0] = 1;
keys[25][0] = -0.207132;
//times[25][1] = 2;
keys[25][1] = -0.207132;
//times[25][2] = 3.2;
keys[25][2] = -0.207132;
//times[25][3] = 3.6;
keys[25][3] = -0.196393;
//times[25][4] = 4.8;
keys[25][4] = -0.207132;
//times[25][5] = 6.6;
keys[25][5] = -0.207132;

/////////////////////////////////////////////////////////////////////
  while(ros::ok())
  {
    Now = ros::Time::now().toSec();
    t = Now - begin;
    //std::cout << "playing" << std::endl;
    //std::cout << "t = " << t << std::endl;

    if(t > times[MotironNumber])
    {
	std::cout << "t = " << t << std::endl;
	for(int i = 0; i < JointNumber; ++i){
		 goal_angle[i] = keys[i][MotironNumber];
	}
	MotironNumber++;
	std::cout << "goal_angle = {";
	for(int j = 0; j < JointNumber; ++j){
		std::cout << goal_angle[j] << ", ";
	}
	std::cout << "Speed:"<<goal_angle[JointNumber] << "}" << std::endl;

	if(MotironNumber>MaxMotironNumber)return 0;
    }

	naoqi_bridge_msgs::JointAnglesWithSpeedActionGoal goal;
	goal.goal.joint_angles.joint_names.push_back("HeadPitch");
	goal.goal.joint_angles.joint_names.push_back("HeadYaw");
	goal.goal.joint_angles.joint_names.push_back("LAnklePitch");
	goal.goal.joint_angles.joint_names.push_back("LAnkleRoll");
	goal.goal.joint_angles.joint_names.push_back("LElbowRoll");
	goal.goal.joint_angles.joint_names.push_back("LElbowYaw");
	goal.goal.joint_angles.joint_names.push_back("LHand");
	goal.goal.joint_angles.joint_names.push_back("LHipPitch");
	goal.goal.joint_angles.joint_names.push_back("LHipRoll");
	goal.goal.joint_angles.joint_names.push_back("LHipYawPitch");
	goal.goal.joint_angles.joint_names.push_back("LKneePitch");
	goal.goal.joint_angles.joint_names.push_back("LShoulderPitch");
	goal.goal.joint_angles.joint_names.push_back("LShoulderRoll");
	goal.goal.joint_angles.joint_names.push_back("LWristYaw");
	goal.goal.joint_angles.joint_names.push_back("RAnklePitch");
	goal.goal.joint_angles.joint_names.push_back("RAnkleRoll");
	goal.goal.joint_angles.joint_names.push_back("RElbowRoll");
	goal.goal.joint_angles.joint_names.push_back("RElbowYaw");
	goal.goal.joint_angles.joint_names.push_back("RHand");
	goal.goal.joint_angles.joint_names.push_back("RHipPitch");
	goal.goal.joint_angles.joint_names.push_back("RHipRoll");
	goal.goal.joint_angles.joint_names.push_back("RHipYawPitch");
	goal.goal.joint_angles.joint_names.push_back("RKneePitch");
	goal.goal.joint_angles.joint_names.push_back("RShoulderPitch");
	goal.goal.joint_angles.joint_names.push_back("RShoulderRoll");
	goal.goal.joint_angles.joint_names.push_back("RWristYaw");

	for(int j = 0; j < JointNumber; ++j){
		goal.goal.joint_angles.joint_angles.push_back(goal_angle[j]);
	}
	goal.goal.joint_angles.speed = 0.25;//Speed[MotironNumber];
	pb.publish<naoqi_bridge_msgs::JointAnglesWithSpeedActionGoal>(goal);

	ros::spinOnce();
	loop_rate.sleep(); 
  }

  return 0;
}
