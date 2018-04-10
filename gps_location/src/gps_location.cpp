#include <opencv2/opencv.hpp>
#include<iostream>
#include <math.h>
#include <iomanip>

using namespace cv;
using namespace std;

vector<KeyPoint> keypoints;
Point2f position(Mat image,Point2f gps_co_ordinate,float megnetometer,float height,float aparture,vector<KeyPoint> keypoints);

Point2f acctual;
float radius=6367449;
Mat cvt_gray( Mat image1);
Point2f contour(Mat dest);
float a=1;
int get_precision=6;



////  now values are in cmmmm;

float alpha=0.01;
float beta=0.01;
double  megnetometer_reading =45.4556744;

float height=0;
float aparture=0;
Point image_position;

Point2d  co_ordinate ;
//Point2f
//Point2f  co_ordinate ;
//cout<<"co_ordinate"<<co_ordinate<<endl;


float pi=3.144;



Mat cvt_gray( Mat image1){
Mat dest;
cvtColor(image1,dest,CV_BGR2GRAY);
imshow("gray",dest);
return dest;
}



Point2f position(Mat image,Point2d co_ordinate,float megnetometer,float height,float aparture,vector<KeyPoint> keypoints)
{


	for(int i=0; i<keypoints.size(); i++){
		cout<<"key PointszzzzzzzzPoint"<<keypoints[i].pt<<endl;
//		cout<<"key Points xxxxxxxxxxxPoint"<<keypoints[i].pt.x<<endl;
//		cout<<"key Points yyyyyyyyyyyPoint"<<keypoints[i].pt.y<<endl;
//



	cout<<"gps_coordinate"<<setprecision(get_precision)<<co_ordinate<<endl;
	Point centre_of_image;
	centre_of_image.x=image.cols/2;
		centre_of_image.y=image.rows/2;



	//	imshow("Input  mbv Image", image);

	cout<<"   centre of imagee   "<<setprecision(get_precision)<<centre_of_image<<endl;
		Point2f difference;







		//if degreee  increases  latitude and logitude increase


//
		 difference.x=keypoints[i].pt.x-centre_of_image.x;
		 difference.y=keypoints[i].pt.y-centre_of_image.y;


		 //if degreee  increases  latitude and logitude decrease
// 		         difference.x=centre_of_image.x-keypoints[i].pt.x;
//		 		 difference.y=centre_of_image.y-keypoints[i].pt.y;

		 		 //if latitude inc and logitude decrease
//
//		 		 difference.x=centre_of_image.x-keypoints[i].pt.x;
//		 		 difference.y=keypoints[i].pt.y-centre_of_image.y;
//


		 		 //if lat dec and log inc



//
//		          difference.x=keypoints[i].pt.x-centre_of_image.x;
//		          difference.y=centre_of_image.y-keypoints[i].pt.y;












		// in image points
		// // multiplying factor
		//
		////image position wrst to ground
		Point2f distance_of_object_in_ground;
		// megnetometer rreading
		// accurate readings in horizontal and vertical distance

		distance_of_object_in_ground.x=alpha*difference.x*cosf(megnetometer_reading);
		distance_of_object_in_ground.y=beta*difference.y*sinf(megnetometer_reading);

	//	distance_of_object_in_ground.x=89.55;
		//	distance_of_object_in_ground.y=33.55;
		//  calculation of co_ordinates
		//  latitude and logitude 
		//  1seconds =30.715 meter
		//  1 minuts = 1834 meter
		//    6,378,137 m 
		//  a=0.99664719
		// // logitude 
		// // no. of logitude 



		float ta=a*tanf(co_ordinate.y);

		float invers_of_tan=atanf(ta);

		//// meters in 1 degree
		float position_of_logutude_in_meter=(pi/180)*radius*cosf(invers_of_tan);
		//
		//// meters in 1 seconds
		float meters_in_one_seconds_of_logitude=position_of_logutude_in_meter/3600;

		//// degree in 1 seconds
		//// degree_in_1_seconds =  0.000277778; m
		//
		float degree_in_1_seconds = 0.000277778;

		float seconds_in_1_meter_of_logitude=1/meters_in_one_seconds_of_logitude;

		  ///horizontal distance calulation
		float degree_in_1_meter_of_logitude_X=seconds_in_1_meter_of_logitude*degree_in_1_seconds;



	//  -------------------------------------------------------------------------

		//----------------------vertical calculation

		//On the GRS80 or WGS84 spheroid at sea level at the equator, one latitudinal second measures
		//30.715 metres,one latitudinal minute is 1843 metres and one latitudinal degree is 110.6 kilometres.

		float meters_in_1_seconds_latitude=30.715;
		float  seconds_in_1_meters=1/meters_in_1_seconds_latitude;
		float  degree_in_1_meters_of_litudelat_Y=degree_in_1_seconds*seconds_in_1_meters;

		///// CALCULATE  LATITUDE AND LOGITDE OF REAL IMAGE

		Point2f deviation_in_degree;
		deviation_in_degree.x= distance_of_object_in_ground.x*degree_in_1_meter_of_logitude_X;
		deviation_in_degree.y=distance_of_object_in_ground.y*degree_in_1_meters_of_litudelat_Y;
	    cout<<"deviation"<<deviation_in_degree<<endl;

	//	Point2f acctual;
		acctual.x=deviation_in_degree.x+co_ordinate.x;
		acctual.y=deviation_in_degree.y+co_ordinate.y;

		cout<<"acctual "<<setprecision(get_precision)<<acctual<<endl;
	}
	return  acctual;
}


Point2f contour(Mat dest){


	Point pt;
	vector<vector<Point> > contours1;
	  vector<Vec4i> hierarchy;
findContours(dest.clone(),contours1,hierarchy,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE);
	drawContours(dest,contours1,-1,Scalar(150,111,155),2);
	imshow("countour_output",dest);
	//cout<<contours1.size()<<endl;

	for(int i=0;i<contours1.size();i++){

	//	cout<<contours1.size()<<endl;

 double cont =contourArea(contours1[i],false);

    // cout<<cont<<endl;


//////// putText(dest,"h2",Point(t.x,t.y),CV_FONT_NORMAL,1,Scalar(115,225,225),1);
//    imshow("text",dest);
	Moments mymoments = moments(contours1[i]);
	double m01 = mymoments.m01;
    double m10 = mymoments.m10;
	double m00 = mymoments.m00;


	if(m00 > 100)	{
		pt.x = m10/m00;
		pt.y=  m01/m00;
	}
//cout<<"point coordinate "<<pt<<endl;
	}
return pt;
}

int main(int argc, char** argv) {
	//Mat  inputImage;
	Mat input_image = imread("check");
	//Mat input_image = imread( "/home/ubuntu/Desktop/gopro_55");
	Point2f centre_of_image;

	centre_of_image.x=input_image.rows/2;
	centre_of_image.y=input_image.cols/2;
	co_ordinate.x =67.333467644;
	co_ordinate.y =67.7345657877;



	 cout << std::fixed;
	  cout << setprecision(get_precision) << megnetometer_reading <<endl;


	cout<<"co ordinatee  "<<setprecision(get_precision) <<co_ordinate<<endl;


	SimpleBlobDetector::Params params;

	params.filterByArea = true;
	params.maxArea = 40000;
	//params.minArea = 1000;

	params.filterByCircularity = false;
	params.minCircularity =0.45;

	// Filter by Convexity
	params.filterByConvexity = false;
	params.minConvexity = 00;

	// Filter by Inertia
	params.filterByInertia = false;
	params.minInertiaRatio = 0.01;


	vector<KeyPoint> keypoints;

	// Set up detector with params
	SimpleBlobDetector detector(params);
	// imshow("dest",dest);
	detector.detect( input_image, keypoints);
	Mat im_with_keypoints;
	drawKeypoints( input_image, keypoints, im_with_keypoints, Scalar(60,90,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );// Show blobs

	imshow("keypoints", im_with_keypoints );
	cout<<"keypoints   "<<keypoints.size()<<endl;
	//drawKeypoints( input_image, keypoints, im_with_keypoints, CV_RGB(255,0,0), DrawMatchesFlags::DEFAULT);
	cout<<"keypoints   "<<keypoints.size()<<endl;
	for(int i=0; i<keypoints.size(); i++){
	circle(input_image, keypoints[i].pt, 10000, cvScalar(23,30,255), 100);
	cout<<"key Points Point"<<keypoints[i].pt<<endl;

	}



	imshow("Input Image", input_image);
 Mat cvt=cvt_gray(input_image);

 Point position_in_image=contour(cvt);
//cout<<"   ccccccccccc   "<<centre_of_image<<endl;

	Point2f pos= position(input_image,co_ordinate,megnetometer_reading, height, aparture,keypoints);
cout  <<"  position error in gps cpo ordinates of object in image "<<setprecision(get_precision)<<pos<<endl;


cout <<"assume 100 meter duistance of that bject from centre of image in ground and megnetometer reading os 45 degere"<<endl;
//	cout<<acctual<<"hkjh,ghggjhj"<<endl;
		waitKey(0);
	return 0;
}
