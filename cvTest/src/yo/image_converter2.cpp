#include <ros/ros.h>
#include "std_msgs/String.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <fstream>

#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <time.h>
#include <signal.h>
#include <vector>
#include <opencv2/opencv.hpp>

#include <opencv2/core/core.hpp>

#include <iomanip>
	
using namespace std;
using namespace cv;
static const std::string OPENCV_WINDOW = "Image window";

class BallPosition
	{
	cv::Point Position[5];
	public:		
		BallPosition(){
			for(int i=0;i<5;i++){
				Position[i].x=0;
				Position[i].y=0;
			}
		}
		void SetPosition(int x,int y){
			Position[0]=cv::Point(x,y);
			Position[1]=Position[0];
			Position[2]=Position[1];
			Position[3]=Position[2];
			Position[4]=Position[3];
		}

		cv::Point GetPosition(){
			cv::Point Sum;
			cv::Point Average;
			for(int i=0;i<5;i++){
				Sum.x=Position[i].x;
				Sum.y=Position[i].y;
			}
			Average.x=Sum.x/5;
			Average.y=Sum.y/5;
			ROS_INFO("Position: %d,%d",(int)Average.x,(int)Average.y);
			return Average;
		}
};	

BallPosition Pos;	
class ImageConverter
	{
		ros::NodeHandle nh_;
		image_transport::ImageTransport it_;
		image_transport::Subscriber image_sub_;
		image_transport::Publisher image_pub_;

	public:
	  ImageConverter(): it_(nh_)
	  {
ROS_INFO("2ssg3a");
	try
         {
	    image_sub_ = it_.subscribe("/nao_robot/naoqi_driver_node/camera/front/image_raw", 1, &ImageConverter::imageCb, this);//"/nao_robot/naoqi_driver/camera/front/image_raw"/usb_cam/image_raw.
         }
         catch (cv::Exception& e)
         {
             // 例外をキャッチしたらエラーメッセージを表示
             ROS_ERROR("cv exception: %s", e.what());
             return;
         }
		image_pub_ = it_.advertise("/image_converter/output_video", 1);
		cv::namedWindow(OPENCV_WINDOW);
	ROS_INFO("jk)'fea");
	  }

	  ~ImageConverter()
	  {
		 cv::destroyWindow(OPENCV_WINDOW);
	  }
	
	void imageCb(const sensor_msgs::ImageConstPtr& msg)
	{
ROS_INFO("KWOf");
	cv_bridge::CvImagePtr cv_ptr;

	try
	{
		cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
	}
	catch (cv_bridge::Exception& e)
	{
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}
///////////////////////////////////////////////////////////////////
	try
	{
	int UCX=cv_ptr->image.cols;//UseCameraX
	int UCY=cv_ptr->image.rows;//UseCameraY
	cv::Mat rgbmat = cv_ptr->image;
	cv::Mat hsv_skin_img = cv::Mat(Size(UCX, UCY), CV_8UC3);
	cv::Mat smooth_img;
	cv::Mat hsv_img;
	int area;
		cv::namedWindow("rgbmat", cv::WND_PROP_ASPECT_RATIO);
	cv::namedWindow("hsv_skin_img", cv::WND_PROP_ASPECT_RATIO);

	cv::flip(rgbmat, rgbmat, 1);
	hsv_skin_img = Scalar(0,0,0);
	cv::medianBlur(rgbmat,smooth_img,7); //ノイズがあるので平滑化
	cv::cvtColor(smooth_img,hsv_img,CV_BGR2HSV);	 //HSVに変換		  //指定した領域から赤色検出
	cv::Rect roi(rgbmat.cols/2 - UCX/2, rgbmat.rows/2 - UCY/2, UCX, UCY);
	cv::Mat hsv_img_roi = hsv_img(roi);
	cv::Mat hsv_skin_img_roi = hsv_skin_img(roi);

	for(int x=0; x<UCX;x++)
	  {
		 for(int y=0; y<UCY; y++)
			{
		 		int a = hsv_img_roi.step*x+(y*3);
		 		if(hsv_img_roi.data[a] >=  0 && hsv_img_roi.data[a] <= 7 && hsv_img_roi.data[a+1] >= 100 && hsv_img_roi.data[a+2] >= 100 ) //HSVでの検出
				{
				//肌色部分を白に
				hsv_skin_img_roi.data[a] = 255;
				hsv_skin_img_roi.data[a+1] = 255;
				hsv_skin_img_roi.data[a+2] = 255;					 
				}
			}
	  }		  
	cv::Mat gray_img = cv::Mat(Size(UCX, UCY),CV_8UC3);
	cv::Mat bin_img = cv::Mat(Size(UCX, UCY),CV_8UC3);
	cv::cvtColor(hsv_skin_img, gray_img, CV_BGR2GRAY);
	std::vector<std::vector<cv::Point> > contours;
	std::vector<std::vector<cv::Point> > contours_subset;
	cv::threshold(gray_img, bin_img, 0, 255, THRESH_BINARY|THRESH_OTSU);
	cv::findContours(bin_img, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	//area = 0;
	double max_size=0;
	int max_id=-1;
	for(int i=0; i<contours.size(); i++){
		//area=contourArea(contours.at(i));
		//cout << "sum = " << area << endl;
		//if(area > 5000 && area < 15000)
		contours_subset.push_back(contours.at(i));
		//cv::Scalar color( rand()&255, rand()&255, rand()&255 );
   	//cv::drawContours( rgbmat, contours, i, color, CV_FILLED, 8, contours );
		//cv::drawContours( rgbmat, contours_subset, -1, Scalar(0,255,0), 4 );

	  if(contours[i].size()>max_size){
		   max_size=contours[i].size();
		   max_id=i;
	  }
	}
	if(max_id > -1){
		cv::Moments mu = moments( contours[max_id]);
		if(mu.m00 > 0){
			cv::Point2f mc = Point2f( mu.m10/mu.m00 , mu.m01/mu.m00 );
			if (rgbmat.rows > 60 && rgbmat.cols > 60)
				cv::circle(rgbmat, cv::Point(mc.x, mc.y), 10, CV_RGB(0,255,0));
			//ROS_INFO("x: %f  y: %f", mc.x, mc.y);
			Pos.SetPosition((int)mc.x, (int)mc.y);
			//ROS_INFO("x: %d  y: %d", Pos.GetPosition().x,Pos.GetPosition().y);
		}else
			ROS_ERROR("Tracking Failed");
	}else
			ROS_ERROR("Tracking Failed");

	//表示
	cv::imshow("rgbmat",rgbmat);//cv::imshow(OPENCV_WINDOW,dImg);
	cv::imshow("hsv_skin_img",hsv_skin_img);
	int key = cv::waitKey(3);
	//if(key > 0 && ((key & 0xFF) == 27)) break; // shutdown on escape	 }
	 

///////////////////////////////////////////////////////////////////
/*
	// Draw an example circle on the video stream
	if (cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
		cv::circle(cv_ptr->image, cv::Point(120, 120), 120, CV_RGB(0,255,0));
	
	// Update GUI Window
	cv::imshow(OPENCV_WINDOW, cv_ptr->image);
	cv::waitKey(3);
	
	// Output modified video stream
	image_pub_.publish(cv_ptr->toImageMsg());

	cv::imshow(OPENCV_WINDOW,dImg);
	cv::waitKey(3);
*/
	  }
	}
         catch (cv::Exception& e)
         {
             // 例外をキャッチしたらエラーメッセージを表示
             ROS_ERROR("cv exception: %s", e.what());
             return;
         }
};

int main(int argc, char** argv)
{

	ros::init(argc, argv, "image_converter");
	ImageConverter ic;

	Pos.GetPosition();

	ros::NodeHandle nh;
	ros::Publisher BallDetect_pub;
	std_msgs::String msg;
	  stringstream ss;
	  //ss << Pos.x << "," << Pos.y << endl;
	msg.data="s";//ss;//+","+Pos.y.ToString();
	BallDetect_pub = nh.advertise<std_msgs::String>("ball_detect",100);
	BallDetect_pub.publish(msg);
	ROS_INFO("%s",msg.data.c_str());

	ros::spin();

	return 0;
}
