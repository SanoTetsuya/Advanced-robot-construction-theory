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
  ros::Publisher pb = n.advertise<naoqi_bridge_msgs::JointAnglesWithSpeedActionGoal>("/nao_robot/pose/joint_angles_action/goal", 1000); ///nao_robot/pose/joint_angles_action/goal", 1000); 
  ros::Rate loop_rate(10);

	double begin =ros::Time::now().toSec();
	double Now =ros::Time::now().toSec();
	double t;//経過時間
	int MotironNumber=0;//現在のモーション番号
	const int MaxMotironNumber = 8; 
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
Speed[4]=0.2;
Speed[5]=0.15;
Speed[6]=0.05;
Speed[7]=0.05;
times[0] = 0.36;
times[1] = 3.12;
times[2] = 4.96;
times[3] = 5.16;
times[4] = 5.32;
times[5] = 5.52;
times[6] = 7.16;
times[7] = 8.44;
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[0][0] = 0.36;
keys[0][0] = 0.154976;
//times[0][1] = 3.12;
keys[0][1] = 0.154976;
//times[0][2] = 4.96;
keys[0][2] = 0.170316;
//times[0][3] = 5.16;
keys[0][3] = 0.154976;
//times[0][4] = 5.32;
keys[0][4] = 0.254976;
//times[0][5] = 5.52;
keys[0][5] = 0.381054;
//times[0][6] = 7.16;
keys[0][6] = 0.354976;
//times[0][7] = 8.44;
keys[0][7] = 0.154976;

//names.push_back("HeadYaw");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[1][0] = 0.36;
keys[1][0] = 0.0183661;
//times[1][1] = 3.12;
keys[1][1] = 0.0183661;
//times[1][2] = 4.96;
keys[1][2] = 0.0183661;
//times[1][3] = 5.16;
keys[1][3] = 0.0183661;
//times[1][4] = 5.32;
keys[1][4] = 0.0183661;
//times[1][5] = 5.52;
keys[1][5] = -0.00157595;
//times[1][6] = 7.16;
keys[1][6] = 0.0183661;
//times[1][7] = 8.44;
keys[1][7] = 0.0183661;

//names.push_back("LAnklePitch");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[2][0] = 0.36;
keys[2][0] = 0.0904641;
//times[2][1] = 3.12;
keys[2][1] = 0.0689881;
//times[2][2] = 4.96;
keys[2][2] = -0.00924587;
//times[2][3] = 5.16;
keys[2][3] = 0.0444441;
//times[2][4] = 5.32;
keys[2][4] = 0.0444441;
//times[2][5] = 5.52;
keys[2][5] = 0.0429101;
//times[2][6] = 7.16;
keys[2][6] = 0.0;
//times[2][7] = 8.44;
keys[2][7] = 0.09;

//names.push_back("LAnkleRoll");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[3][0] = 0.36;
keys[3][0] = -0.224212;
//times[3][1] = 3.12;
keys[3][1] = 0.231676;
//times[3][2] = 4.96;
keys[3][2] = 0.449562;
//times[3][3] = 5.16;
keys[3][3] = 0.385076;
//times[3][4] = 5.32;
keys[3][4] = 0.385076;
//times[3][5] = 5.52;
keys[3][5] = 0.377406;
//times[3][6] = 7.16;
keys[3][6] = 0.300000;
//times[3][7] = 8.44;
keys[3][7] = -0.024212;

//names.push_back("LElbowRoll");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[4][0] = 0.36;
keys[4][0] = -0.398798;
//times[4][1] = 3.12;
keys[4][1] = -0.398798;
//times[4][2] = 4.96;
keys[4][2] = -0.36505;
//times[4][3] = 5.16;
keys[4][3] = -0.375788;
//times[4][4] = 5.32;
keys[4][4] = -0.375788;
//times[4][5] = 5.52;
keys[4][5] = -0.375788;
//times[4][6] = 7.16;
keys[4][6] = -0.375788;
//times[4][7] = 8.44;
keys[4][7] = -0.398797;

//names.push_back("LElbowYaw");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[5][0] = 0.36;
keys[5][0] = -1.18429;
//times[5][1] = 3.12;
keys[5][1] = -1.18429;
//times[5][2] = 4.96;
keys[5][2] = -1.19503;
//times[5][3] = 5.16;
keys[5][3] = -1.18429;
//times[5][4] = 5.32;
keys[5][4] = -1.18429;
//times[5][5] = 5.52;
keys[5][5] = -1.18736;
//times[5][6] = 7.16;
keys[5][6] = -1.18429;
//times[5][7] = 8.44;
keys[5][7] = -1.18429;

//names.push_back("LHand");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[6][0] = 0.36;
keys[6][0] = 0.2904;
//times[6][1] = 3.12;
keys[6][1] = 0.2904;
//times[6][2] = 4.96;
keys[6][2] = 0.2904;
//times[6][3] = 5.16;
keys[6][3] = 0.2904;
//times[6][4] = 5.32;
keys[6][4] = 0.2904;
//times[6][5] = 5.52;
keys[6][5] = 0.2904;
//times[6][6] = 7.16;
keys[6][6] = 0.2904;
//times[6][7] = 8.44;
keys[6][7] = 0.2904;

//names.push_back("LHipPitch");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[7][0] = 0.36;
keys[7][0] = 0.122762;
//times[7][1] = 3.12;
keys[7][1] = 0.119694;
//times[7][2] = 4.96;
keys[7][2] = 0.16418;
//times[7][3] = 5.16;
keys[7][3] = 0.108956;
//times[7][4] = 5.32;
keys[7][4] = 0.108956;
//times[7][5] = 5.52;
keys[7][5] = 0.108956;
//times[7][6] = 7.16;
keys[7][6] = 0.108956;
//times[7][7] = 8.44;
keys[7][7] = 0.122762;

//names.push_back("LHipRoll");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[8][0] = 0.36;
keys[8][0] = 0.178218;
//times[8][1] = 3.12;
keys[8][1] = -0.184038;
//times[8][2] = 4.96;
keys[8][2] = -0.335904;
//times[8][3] = 5.16;
keys[8][3] = -0.325166;
//times[8][4] = 5.32;
keys[8][4] = -0.325166;
//times[8][5] = 5.52;
keys[8][5] = -0.325166;
//times[8][6] = 7.16;
keys[8][6] = -0.314428;
//times[8][7] = 8.44;
keys[8][7] = 0.1782179;

//names.push_back("LHipYawPitch");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[9][0] = 0.36;
keys[9][0] = 0.170232;
//times[9][1] = 3.12;
keys[9][1] = -0.170232;
//times[9][2] = 4.96;
keys[9][2] = -0.141086;
//times[9][3] = 5.16;
keys[9][3] = -0.202446;
//times[9][4] = 5.32;
keys[9][4] = -0.202446;
//times[9][5] = 5.52;
keys[9][5] = -0.202446;
//times[9][6] = 7.16;
keys[9][6] = -0.191708;
//times[9][7] = 8.44;
keys[9][7] = 0.170232;

//names.push_back("LKneePitch");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[10][0] = 0.36;
keys[10][0] = -0.092082;
//times[10][1] = 3.12;
keys[10][1] = -0.092082;
//times[10][2] = 4.96;
keys[10][2] = -0.0598679;
//times[10][3] = 5.16;
keys[10][3] = -0.0813439;
//times[10][4] = 5.32;
keys[10][4] = -0.0813439;
//times[10][5] = 5.52;
keys[10][5] = -0.0874801;
//times[10][6] = 7.16;
keys[10][6] = -0.0813439;
//times[10][7] = 8.44;
keys[10][7] = -0.092082;

//names.push_back("LShoulderPitch");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[11][0] = 0.36;
keys[11][0] = 1.4726;
//times[11][1] = 3.12;
keys[11][1] = 1.49561;
//times[11][2] = 4.96;
keys[11][2] = 1.52322;
//times[11][3] = 5.16;
keys[11][3] = 1.51095;
//times[11][4] = 5.32;
keys[11][4] = 1.51095;
//times[11][5] = 5.52;
keys[11][5] = 1.49407;
//times[11][6] = 7.16;
keys[11][6] = 1.51095;
//times[11][7] = 8.44;
keys[11][7] = 1.4726;

//names.push_back("LShoulderRoll");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[12][0] = 0.36;
keys[12][0] = 0.162562;
//times[12][1] = 3.12;
keys[12][1] = 0.176368;
//times[12][2] = 4.96;
keys[12][2] = 0.0720561;
//times[12][3] = 5.16;
keys[12][3] = 0.0858622;
//times[12][4] = 5.32;
keys[12][4] = 0.0858622;
//times[12][5] = 5.52;
keys[12][5] = 0.075124;
//times[12][6] = 7.16;
keys[12][6] = 0.0858622;
//times[12][7] = 8.44;
keys[12][7] = 0.162562;

//names.push_back("LWristYaw");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[13][0] = 0.36;
keys[13][0] = 0.0904641;
//times[13][1] = 3.12;
keys[13][1] = 0.0904641;
//times[13][2] = 4.96;
keys[13][2] = 0.102736;
//times[13][3] = 5.16;
keys[13][3] = 0.102736;
//times[13][4] = 5.32;
keys[13][4] = 0.102736;
//times[13][5] = 5.52;
keys[13][5] = 0.0873961;
//times[13][6] = 7.16;
keys[13][6] = 0.102736;
//times[13][7] = 8.44;
keys[13][7] = 0.0904641;

//names.push_back("RAnklePitch");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[14][0] = 0.36;
keys[14][0] = 0.0521979;
//times[14][1] = 3.12;
keys[14][1] = 0.0368581;
//times[14][2] = 4.96;
keys[14][2] = -0.509246;
//times[14][3] = 5.16;
keys[14][3] = -0.475498;
//times[14][4] = 5.32;
keys[14][4] = -0.544528;
//times[14][5] = 5.52;
keys[14][5] = -0.0137641;
//times[14][6] = 7.16;
keys[14][6] = 0.0890141;
//times[14][7] = 8.44;
keys[14][7] = 0.0521979;

//names.push_back("RAnkleRoll");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[15][0] = 0.36;
keys[15][0] = 0.16563;
//times[15][1] = 3.12;
keys[15][1] = 0.10282;
//times[15][2] = 4.96;
keys[15][2] = 0.138102;
//times[15][3] = 5.16;
keys[15][3] = 0.10282;
//times[15][4] = 5.32;
keys[15][4] = 0.10282;
//times[15][5] = 5.52;
keys[15][5] = 0.115092;
//times[15][6] = 7.16;
keys[15][6] = 0.297638;
//times[15][7] = 8.44;
keys[15][7] = 0.100000;

//names.push_back("RElbowRoll");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[16][0] = 0.36;
keys[16][0] = 0.19428;
//times[16][1] = 3.12;
keys[16][1] = 0.43263;
//times[16][2] = 4.96;
keys[16][2] = 0.452572;
//times[16][3] = 5.16;
keys[16][3] = 0.408086;
//times[16][4] = 5.32;
keys[16][4] = 0.408086;
//times[16][5] = 5.52;
keys[16][5] = 0.39428;
//times[16][6] = 7.16;
keys[16][6] = 0.408086;
//times[16][7] = 8.44;
keys[16][7] = 0.19428;

//names.push_back("RElbowYaw");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[17][0] = 0.36;
keys[17][0] = 1.18727;
//times[17][1] = 3.12;
keys[17][1] = 1.46493;
//times[17][2] = 4.96;
keys[17][2] = 1.77786;
//times[17][3] = 5.16;
keys[17][3] = 1.49714;
//times[17][4] = 5.32;
keys[17][4] = 1.49714;
//times[17][5] = 5.52;
keys[17][5] = 1.47106;
//times[17][6] = 7.16;
keys[17][6] = 1.49714;
//times[17][7] = 8.44;
keys[17][7] = 1.18727;

//names.push_back("RHand");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[18][0] = 0.36;
keys[18][0] = 0.2884;
//times[18][1] = 3.12;
keys[18][1] = 0.2884;
//times[18][2] = 4.96;
keys[18][2] = 0.2884;
//times[18][3] = 5.16;
keys[18][3] = 0.2884;
//times[18][4] = 5.32;
keys[18][4] = 0.2884;
//times[18][5] = 5.52;
keys[18][5] = 0.2884;
//times[18][6] = 7.16;
keys[18][6] = 0.2884;
//times[18][7] = 8.44;
keys[18][7] = 0.2884;

//names.push_back("RHipPitch");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[19][0] = 0.36;
keys[19][0] = 0.128814;
//times[19][1] = 3.12;
keys[19][1] = 0.136484;
//times[19][2] = 4.96;
keys[19][2] = -0.128898;
//times[19][3] = 5.16;
keys[19][3] = -0.11816;
//times[19][4] = 5.32;
keys[19][4] = -0.228608;
//times[19][5] = 5.52;
keys[19][5] = -0.690342;
//times[19][6] = 7.16;
keys[19][6] = -0.069072;
//times[19][7] = 8.44;
keys[19][7] = 0.128814;

//names.push_back("RHipRoll");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[20][0] = 0.36;
keys[20][0] = 0.076452;
//times[20][1] = 3.12;
keys[20][1] = -0.2628521;
//times[20][2] = 4.96;
keys[20][2] = -0.500042;
//times[20][3] = 5.16;
keys[20][3] = -0.713558;
//times[20][4] = 5.32;
keys[20][4] = -0.584992;
//times[20][5] = 5.52;
keys[20][5] = -0.346932;
//times[20][6] = 7.16;
keys[20][6] = -0.240796;
//times[20][7] = 8.44;
keys[20][7] = -0.076453;

//names.push_back("RHipYawPitch");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[21][0] = 0.36;
keys[21][0] = -0.170232;
//times[21][1] = 3.12;
keys[21][1] = -0.170232;
//times[21][2] = 4.96;
keys[21][2] = -0.141086;
//times[21][3] = 5.16;
keys[21][3] = -0.202446;
//times[21][4] = 5.32;
keys[21][4] = -0.202446;
//times[21][5] = 5.52;
keys[21][5] = -0.202446;
//times[21][6] = 7.16;
keys[21][6] = -0.191708;
//times[21][7] = 8.44;
keys[21][7] = -0.170232;

//names.push_back("RKneePitch");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[22][0] = 0.36;
keys[22][0] = -0.0858622;
//times[22][1] = 3.12;
keys[22][1] = -0.0858622;
//times[22][2] = 4.96;
keys[22][2] = 1.38122;
//times[22][3] = 5.16;
keys[22][3] = 0.786984;
//times[22][4] = 5.32;
keys[22][4] = 0.786984;
//times[22][5] = 5.52;
keys[22][5] = 0.575002;
//times[22][6] = 7.16;
keys[22][6] = 0.3737899;
//times[22][7] = 8.44;
keys[22][7] = -0.0800000;

//names.push_back("RShoulderPitch");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[23][0] = 0.36;
keys[23][0] = 1.48649;
//times[23][1] = 3.12;
keys[23][1] = 1.43126;
//times[23][2] = 4.96;
keys[23][2] = 1.43798;
//times[23][3] = 5.16;
keys[23][3] = 1.41439;
//times[23][4] = 5.32;
keys[23][4] = 1.41439;
//times[23][5] = 5.52;
keys[23][5] = 1.46194;
//times[23][6] = 7.16;
keys[23][6] = 1.41439;
//times[23][7] = 8.44;
keys[23][7] = 1.48649;

//names.push_back("RShoulderRoll");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[24][0] = 0.36;
keys[24][0] = -0.165714;
//times[24][1] = 3.12;
keys[24][1] = -1.10912;
//times[24][2] = 4.96;
keys[24][2] = -1.09225;
//times[24][3] = 5.16;
keys[24][3] = -1.10145;
//times[24][4] = 5.32;
keys[24][4] = -1.10145;
//times[24][5] = 5.52;
keys[24][5] = -1.03703;
//times[24][6] = 7.16;
keys[24][6] = -1.10145;
//times[24][7] = 8.44;
keys[24][7] = -0.165714;

//names.push_back("RWristYaw");
////timesarraySetSize(8);
//keysarraySetSize(8);

//times[25][0] = 0.36;
keys[25][0] = 0.098134;
//times[25][1] = 3.12;
keys[25][1] = -0.0798099;
//times[25][2] = 4.96;
keys[25][2] = -0.17185;
//times[25][3] = 5.16;
keys[25][3] = -0.158044;
//times[25][4] = 5.32;
keys[25][4] = -0.158044;
//times[25][5] = 5.52;
keys[25][5] = -0.147306;
//times[25][6] = 7.16;
keys[25][6] = -0.158044;
//times[25][7] = 8.44;
keys[25][7] = 0.0981341;


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
