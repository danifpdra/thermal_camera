#include <ros/console.h>
#include <ros/ros.h>
#include <rospack/rospack.h>
//-----------------
#include "stdio.h"
#include <algorithm> // std::max
#include <cmath>
#include <fstream>
#include <iostream>
#include <math.h>

/* openCv*/
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/core/core.hpp>
// #include <opencv2/core/eigen.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include <dynamic_reconfigure/server.h>
#include <ros/package.h>
#include <thermal_camera/TutorialsConfig.h>

using namespace std;
using namespace cv;

// class ImgCalib {
// public:
//   // publicadores
//   ImgCalib();

//   void loop_function();

// private:
//   // rosnode
//   ros::NodeHandle nh;
//   cv::Mat thermal_img;
//   image_transport::Subscriber img_sub;
//   image_transport::ImageTransport it;
//   std_msgs::Header header;
//   sensor_msgs::ImagePtr msg_thermal;
// };

// /**
//  * @brief Construct a new Thermal Cam:: Thermal Cam object
//  *
//  */
// ImgCalib::ImgCalib() : it(nh) {
//   img_sub = it.subscribe("thermal_camera/thermal_img_mono", 1,
//   imageCallback);
// }

// /**
//  * @brief Loop function
//  *
//  */
// void ThermalCam::loop_function() {}

void imageCallback(const sensor_msgs::ImageConstPtr &msg) {
  try {
    cv::imshow("Frame", cv_bridge::toCvShare(msg, "mono16")->image);
    cv::waitKey(30);
  } catch (cv_bridge::Exception &e) {
    ROS_ERROR("Could not convert from '%s' to 'mono16'.",
              msg->encoding.c_str());
  }
}

void CallBackFunc(int event, int x, int y, int flags, void *userdata) {
  if (event == EVENT_LBUTTONDOWN) {
    cout << "Left button of the mouse is clicked - position (" << x << ", " << y
         << ")" << endl;
  } else if (event == EVENT_RBUTTONDOWN) {
    cout << "Right button of the mouse is clicked - position (" << x << ", "
         << y << ")" << endl;
  } else if (event == EVENT_MBUTTONDOWN) {
    cout << "Middle button of the mouse is clicked - position (" << x << ", "
         << y << ")" << endl;
  } else if (event == EVENT_MOUSEMOVE) {
    cout << "Mouse move over the window - position (" << x << ", " << y << ")"
         << endl;
  }
}

int main(int argc, char **argv) {

  ros::init(argc, argv, "thermal_img_calibration");
  ros::NodeHandle nh;
  cv::namedWindow("Frame");
  // cv::startWindowThread();
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber img_sub =
      it.subscribe("/thermal_camera/thermal_img_mono", 1, imageCallback);
  setMouseCallback("Frame", CallBackFunc, NULL);
  ros::spin();
  cv::destroyWindow("Frame");
}
