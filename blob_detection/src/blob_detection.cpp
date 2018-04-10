#include <cv.h>
#include <highgui.h>
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
RNG rng(12345);

int main( )
{


Mat im1 = imread( "/home/ubuntu/Desktop/gopro_55");
SimpleBlobDetector::Params params;
namedWindow("imaaaa",CV_WINDOW_NORMAL);
imshow("imaaaa",im1);
params.filterByArea = true;
params.maxArea = 1000;
//params.minArea = 1000;

params.filterByCircularity = false;
params.minCircularity =0.45;

// Filter by Convexity
params.filterByConvexity = false;
params.minConvexity = 00;

// Filter by Inertia
params.filterByInertia = false;
params.minInertiaRatio = 0.01;

cout<<"hiii"<<endl;
vector<KeyPoint> keypoints;

// Set up detector with params
SimpleBlobDetector detector(params);
// imshow("dest",dest);
detector.detect( im1, keypoints);
Mat im_with_keypoints;
drawKeypoints( im1, keypoints, im_with_keypoints, Scalar(60,90,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );// Show blobs

imshow("keypoints", im_with_keypoints );
cout<<"keypoints   "<<keypoints.size()<<endl;
drawKeypoints( im1, keypoints, im_with_keypoints, CV_RGB(255,0,0), DrawMatchesFlags::DEFAULT);

for(int i=0; i<keypoints.size(); i++){
circle(im1, keypoints[i].pt, 10000, cvScalar(23,30,255), 100);
cout<<"key Points Point"<<keypoints[i].pt<<endl;

}

waitKey(0);
return 0;
}
