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
Speed[0]=0.2;
Speed[1]=0.2;
Speed[2]=0.1;
Speed[3]=0.2;
Speed[4]=0.25;
Speed[5]=0.2;


times[0] = 0.4;
times[1] = 1.44;
times[2] = 2.6;
times[3] = 3.4;
times[4] = 4.2;
times[5] = 4.92;

//names.push_back("HeadPitch");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[0][0] = 0.4;
keys[0][0] = 0.148756;
//times[0][1] = 1.44;
keys[0][1] = 0.148756;
//times[0][2] = 2.6;
keys[0][2] = 0.486828;
//times[0][3] = 3.4;
keys[0][3] = -0.213268;
//times[0][4] = 4.2;
keys[0][4] = -0.213268;
//times[0][5] = 4.92;
keys[0][5] = 0.148756;

//names.push_back("HeadYaw");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[1][0] = 0.4;
keys[1][0] = -0.0383921;
//times[1][1] = 1.44;
keys[1][1] = -0.0383921;
//times[1][2] = 2.6;
keys[1][2] = 0.153358;
//times[1][3] = 3.4;
keys[1][3] = 0.099668;
//times[1][4] = 4.2;
keys[1][4] = 0.099668;
//times[1][5] = 4.92;
keys[1][5] = -0.038392;

//names.push_back("LAnklePitch");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[2][0] = 0.4;
keys[2][0] = 0.0689881;
//times[2][1] = 1.44;
keys[2][1] = 0.0689881;
//times[2][2] = 2.6;
keys[2][2] = -0.242414;
//times[2][3] = 3.4;
keys[2][3] = -0.090548;
//times[2][4] = 4.2;
keys[2][4] = -0.090548;
//times[2][5] = 4.92;
keys[2][5] = 0.0689882;

//names.push_back("LAnkleRoll");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[3][0] = 0.4;
keys[3][0] = -0.0705221;
//times[3][1] = 1.44;
keys[3][1] = 0.224006;
//times[3][2] = 2.6;
keys[3][2] = 0.216336;
//times[3][3] = 3.4;
keys[3][3] = 0.375872;
//times[3][4] = 4.2;
keys[3][4] = 0.375872;
//times[3][5] = 4.92;
keys[3][5] = -0.0705221;

//names.push_back("LElbowRoll");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[4][0] = 0.4;
keys[4][0] = -0.607422;
//times[4][1] = 1.44;
keys[4][1] = -0.607422;
//times[4][2] = 2.6;
keys[4][2] = -0.598218;
//times[4][3] = 3.4;
keys[4][3] = -1.50941;
//times[4][4] = 4.2;
keys[4][4] = -1.50941;
//times[4][5] = 4.92;
keys[4][5] = -0.607422;

//names.push_back("LElbowYaw");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[5][0] = 0.4;
keys[5][0] = -1.19043;
//times[5][1] = 1.44;
keys[5][1] = -1.19043;
//times[5][2] = 2.6;
keys[5][2] = -1.19963;
//times[5][3] = 3.4;
keys[5][3] = -1.30394;
//times[5][4] = 4.2;
keys[5][4] = -1.30394;
//times[5][5] = 4.92;
keys[5][5] = -1.19043;

//names.push_back("LHand");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[6][0] = 0.4;
keys[6][0] = 0.4152;
//times[6][1] = 1.44;
keys[6][1] = 0.4152;
//times[6][2] = 2.6;
keys[6][2] = 0.3336;
//times[6][3] = 3.4;
keys[6][3] = 0.4848;
//times[6][4] = 4.2;
keys[6][4] = 0.4848;
//times[6][5] = 4.92;
keys[6][5] = 0.4152;

//names.push_back("LHipPitch");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[7][0] = 0.4;
keys[7][0] = 0.213268;
//times[7][1] = 1.44;
keys[7][1] = 0.200996;
//times[7][2] = 2.6;
keys[7][2] = 0.14117;
//times[7][3] = 3.4;
keys[7][3] = 0.239346;
//times[7][4] = 4.2;
keys[7][4] = 0.24088;
//times[7][5] = 4.92;
keys[7][5] = 0.213269;

//names.push_back("LHipRoll");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[8][0] = 0.4;
keys[8][0] = 0.0567999;
//times[8][1] = 1.44;
keys[8][1] = -0.179436;
//times[8][2] = 2.6;
keys[8][2] = -0.379435;
//times[8][3] = 3.4;
keys[8][3] = -0.369652;
//times[8][4] = 4.2;
keys[8][4] = -0.369652;
//times[8][5] = 4.92;
keys[8][5] = 0.0567998;

//names.push_back("LHipYawPitch");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[9][0] = 0.4;
keys[9][0] = -0.14262;
//times[9][1] = 1.44;
keys[9][1] = -0.179436;
//times[9][2] = 2.6;
keys[9][2] = -0.297554;
//times[9][3] = 3.4;
keys[9][3] = -0.113474;
//times[9][4] = 4.2;
keys[9][4] = -0.102736;
//times[9][5] = 4.92;
keys[9][5] = -0.14262;

//names.push_back("LKneePitch");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[10][0] = 0.4;
keys[10][0] = -0.0874801;
//times[10][1] = 1.44;
keys[10][1] = -0.0874801;
//times[10][2] = 2.6;
keys[10][2] = 0.28068;
//times[10][3] = 3.4;
keys[10][3] = -0.090548;
//times[10][4] = 4.2;
keys[10][4] = -0.092082;
//times[10][5] = 4.92;
keys[10][5] = -0.0874801;

//names.push_back("LShoulderPitch");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[11][0] = 0.4;
keys[11][0] = 1.59685;
//times[11][1] = 1.44;
keys[11][1] = 1.59685;
//times[11][2] = 2.6;
keys[11][2] = 1.60759;
//times[11][3] = 3.4;
keys[11][3] = 1.93126;
//times[11][4] = 4.2;
keys[11][4] = 1.93126;
//times[11][5] = 4.92;
keys[11][5] = 1.59685;

//names.push_back("LShoulderRoll");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[12][0] = 0.4;
keys[12][0] = 0.056716;
//times[12][1] = 1.44;
keys[12][1] = 0.056716;
//times[12][2] = 2.6;
keys[12][2] = 0.0183661;
//times[12][3] = 3.4;
keys[12][3] = 0.14262;
//times[12][4] = 4.2;
keys[12][4] = 0.14262;
//times[12][5] = 4.92;
keys[12][5] = 0.056716;

//names.push_back("LWristYaw");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[13][0] = 0.4;
keys[13][0] = 0.0935321;
//times[13][1] = 1.44;
keys[13][1] = 0.0935321;
//times[13][2] = 2.6;
keys[13][2] = 0.0705221;
//times[13][3] = 3.4;
keys[13][3] = 0.05058;
//times[13][4] = 4.2;
keys[13][4] = 0.05058;
//times[13][5] = 4.92;
keys[13][5] = 0.093532;

//names.push_back("RAnklePitch");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[14][0] = 0.4;
keys[14][0] = 0.066004;
//times[14][1] = 1.44;
keys[14][1] = 0.066004;
//times[14][2] = 2.6;
keys[14][2] = 0.546146;
//times[14][3] = 3.4;
keys[14][3] = 0.328318;
//times[14][4] = 4.2;
keys[14][4] = 0.00310993;
//times[14][5] = 4.92;
keys[14][5] = 0.066004;

//names.push_back("RAnkleRoll");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[15][0] = 0.4;
keys[15][0] = 0.090548;
//times[15][1] = 1.44;
keys[15][1] = 0.10282;
//times[15][2] = 2.6;
keys[15][2] = 0.0813439;
//times[15][3] = 3.4;
keys[15][3] = 0.10282;
//times[15][4] = 4.2;
keys[15][4] = 0.188724;
//times[15][5] = 4.92;
keys[15][5] = 0.090548;

//names.push_back("RElbowRoll");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[16][0] = 0.4;
keys[16][0] = 0.523136;
//times[16][1] = 1.44;
keys[16][1] = 0.523136;
//times[16][2] = 2.6;
keys[16][2] = 0.55535;
//times[16][3] = 3.4;
keys[16][3] = 0.64739;
//times[16][4] = 4.2;
keys[16][4] = 0.64739;
//times[16][5] = 4.92;
keys[16][5] = 0.523136;

//names.push_back("RElbowYaw");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[17][0] = 0.4;
keys[17][0] = 1.3284;
//times[17][1] = 1.44;
keys[17][1] = 1.32994;
//times[17][2] = 2.6;
keys[17][2] = 1.51555;
//times[17][3] = 3.4;
keys[17][3] = 1.39283;
//times[17][4] = 4.2;
keys[17][4] = 1.39283;
//times[17][5] = 4.92;
keys[17][5] = 1.3284;

//names.push_back("RHand");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[18][0] = 0.4;
keys[18][0] = 0.312;
//times[18][1] = 1.44;
keys[18][1] = 0.312;
//times[18][2] = 2.6;
keys[18][2] = 0.3208;
//times[18][3] = 3.4;
keys[18][3] = 0.3524;
//times[18][4] = 4.2;
keys[18][4] = 0.3524;
//times[18][5] = 4.92;
keys[18][5] = 0.312;

//names.push_back("RHipPitch");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[19][0] = 0.4;
keys[19][0] = 0.193242;
//times[19][1] = 1.44;
keys[19][1] = 0.16563;
//times[19][2] = 2.6;
keys[19][2] = -0.39428;
//times[19][3] = 3.4;
keys[19][3] = -0.128898;
//times[19][4] = 4.2;
keys[19][4] = 0.11194;
//times[19][5] = 4.92;
keys[19][5] = 0.193243;

//names.push_back("RHipRoll");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[20][0] = 0.4;
keys[20][0] = -0.0935321;
//times[20][1] = 1.44;
keys[20][1] = -0.191708;
//times[20][2] = 2.6;
keys[20][2] = -0.337438;
//times[20][3] = 3.4;
keys[20][3] = -0.516916;
//times[20][4] = 4.2;
keys[20][4] = -0.516916;
//times[20][5] = 4.92;
keys[20][5] = -0.093532;

//names.push_back("RHipYawPitch");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[21][0] = 0.4;
keys[21][0] = -0.14262;
//times[21][1] = 1.44;
keys[21][1] = -0.179436;
//times[21][2] = 2.6;
keys[21][2] = -0.297554;
//times[21][3] = 3.4;
keys[21][3] = -0.113474;
//times[21][4] = 4.2;
keys[21][4] = -0.102736;
//times[21][5] = 4.92;
keys[21][5] = -0.14262;

//names.push_back("RKneePitch");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[22][0] = 0.4;
keys[22][0] = -0.0858622;
//times[22][1] = 1.44;
keys[22][1] = -0.0858622;
//times[22][2] = 2.6;
keys[22][2] = -0.0858622;
//times[22][3] = 3.4;
keys[22][3] = -0.0858622;
//times[22][4] = 4.2;
keys[22][4] = -0.0858622;
//times[22][5] = 4.92;
keys[22][5] = -0.0858622;

//names.push_back("RShoulderPitch");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[23][0] = 0.4;
keys[23][0] = 1.53251;
//times[23][1] = 1.44;
keys[23][1] = 1.63989;
//times[23][2] = 2.6;
keys[23][2] = 1.62301;
//times[23][3] = 3.4;
keys[23][3] = 1.63989;
//times[23][4] = 4.2;
keys[23][4] = 1.63989;
//times[23][5] = 4.92;
keys[23][5] = 1.53251;

//names.push_back("RShoulderRoll");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[24][0] = 0.4;
keys[24][0] = -0.135034;
//times[24][1] = 1.44;
keys[24][1] = -0.20253;
//times[24][2] = 2.6;
keys[24][2] = -0.214802;
//times[24][3] = 3.4;
keys[24][3] = -0.245482;
//times[24][4] = 4.2;
keys[24][4] = -0.207132;
//times[24][5] = 4.92;
keys[24][5] = -0.135034;

//names.push_back("RWristYaw");
////timesarraySetSize(6);
//keysarraySetSize(6);

//times[25][0] = 0.4;
keys[25][0] = 0.130348;
//times[25][1] = 1.44;
keys[25][1] = 0.0444441;
//times[25][2] = 2.6;
keys[25][2] = 0.87894;
//times[25][3] = 3.4;
keys[25][3] = 1.69503;
//times[25][4] = 4.2;
keys[25][4] = 1.69503;
//times[25][5] = 4.92;
keys[25][5] = 0.130348;

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
