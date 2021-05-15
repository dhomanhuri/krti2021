/**
* ROS node for rectifying omnidirectional camera image
* based on camera model provided by OCamCalib and the undistord
* function provided by ocam_functions.h
* https://sites.google.com/site/scarabotix/ocamcalib-toolbox  
* 
* Copyright 2019 Robotic Lab - The State Polytechnic of Malang Indonesia
* If you use this code, please cite the respective publications as
* listed on the above website.
*
* Omni2plc is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Omni2plc is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Omni2plc. If not, see <http://www.gnu.org/licenses/>.
*/



#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_ros/point_cloud.h>
#include <string>

#include <tf/transform_broadcaster.h>

#include <tf/tf.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <nav_msgs/Odometry.h>



#include <visp3/core/vpPixelMeterConversion.h>
#include <visp3/detection/vpDetectorQRCode.h>
#include <visp3/gui/vpDisplayGDI.h>
#include <visp3/gui/vpDisplayOpenCV.h>
#include <visp3/gui/vpDisplayX.h>
#include <visp3/io/vpImageIo.h>
#include <visp3/vision/vpPose.h>

#include <visp3/core/vpDisplay.h>
#include <visp3/core/vpPixelMeterConversion.h>

#include "pose_helper.h"

using namespace cv;
using namespace std;


ros::Publisher pub2;
image_transport::Publisher pub_image;

int displayResult = 0;



vpImage<unsigned char> I;
std::vector<vpPoint> point;


//! [Compute pose]
void computePose(std::vector<vpPoint> &point, const std::vector<vpImagePoint> &ip,
                 const vpCameraParameters &cam, bool init, vpHomogeneousMatrix &cMo)
{
  vpPose pose;
  double x = 0, y = 0;
  for (unsigned int i = 0; i < point.size(); i++) {
    vpPixelMeterConversion::convertPoint(cam, ip[i], x, y);
    point[i].set_x(x);
    point[i].set_y(y);
    pose.addPoint(point[i]);
  }

  if (init == true) {
    vpHomogeneousMatrix cMo_dem;
    vpHomogeneousMatrix cMo_lag;
    pose.computePose(vpPose::DEMENTHON, cMo_dem);
    pose.computePose(vpPose::LAGRANGE, cMo_lag);
    double residual_dem = pose.computeResidual(cMo_dem);
    double residual_lag = pose.computeResidual(cMo_lag);
    if (residual_dem < residual_lag)
      cMo = cMo_dem;
    else
      cMo = cMo_lag;
  }
  pose.computePose(vpPose::VIRTUAL_VS, cMo);
}
//! [Compute pose]

#if defined(VISP_HAVE_X11) || defined(VISP_HAVE_GDI) || defined(VISP_HAVE_OPENCV)
std::vector<vpImagePoint> track(vpImage<unsigned char> &I, std::vector<vpDot2> &dot, bool init)
{
  try {
    double distance_same_blob = 10.; // 2 blobs are declared same if their distance is less than this value
    std::vector<vpImagePoint> ip(dot.size());
    if (init) {
      vpDisplay::flush(I);
      for (unsigned int i = 0; i < dot.size(); i++) {
        dot[i].setGraphics(true);
        dot[i].setGraphicsThickness(2);
        std::stringstream ss;
        ss << "Click on point " << i+1;
        vpDisplay::displayText(I, 20, 20, "Status: initialize blob tracker", vpColor::red);
        vpDisplay::displayText(I, 40 + i*20, 20, ss.str(), vpColor::red);
        vpDisplay::flush(I);
        dot[i].initTracking(I);
        vpDisplay::flush(I);
      }
    } else {
      for (unsigned int i = 0; i < dot.size(); i++) {
        dot[i].track(I);
      }
    }
    for (unsigned int i = 0; i < dot.size(); i++) {
      ip[i] = dot[i].getCog();
      // Compare distances between all the dots to check if some of them are not the same
    }
    for (unsigned int i=0; i < ip.size(); i++) {
      for (unsigned int j=i+1; j < ip.size(); j++) {
        if (vpImagePoint::distance(ip[i], ip[j]) < distance_same_blob) {
          std::cout << "Traking lost: 2 blobs are the same" << std::endl;
          throw(vpException(vpException::fatalError, "Tracking lost: 2 blobs are the same"));
        }
      }
    }

    return ip;
  }
  catch(...) {
    std::cout << "Traking lost" << std::endl;
    throw(vpException(vpException::fatalError, "Tracking lost"));
  }
}
#endif




void imageCallback(const sensor_msgs::ImageConstPtr& msg){
		
	try	{

	cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
	
	//~ cv::imshow("view", cv_ptr->image);
    
    //~ cv::waitKey(2);

	
	
  	vpImageConvert::convert(cv_ptr->image, I);
  	vpDisplay::display(I); 


    


    // Camera parameters should be adapted to your camera
    vpCameraParameters cam(1280, 720, I.getWidth() / 2, I.getHeight() / 2);

    // 3D model of the QRcode: here we consider a 17cm by 17cm QRcode
    std::vector<vpPoint> point;
    point.push_back(vpPoint(-0.085, -0.085, 0)); // QRcode point 0 3D coordinates in plane Z=0
    point.push_back(vpPoint( 0.085, -0.085, 0)); // QRcode point 1 3D coordinates in plane Z=0
    point.push_back(vpPoint( 0.085,  0.085, 0)); // QRcode point 2 3D coordinates in plane Z=0
    point.push_back(vpPoint(-0.085,  0.085, 0)); // QRcode point 3 3D coordinates in plane Z=0

    vpHomogeneousMatrix cMo;
    bool init = true;
    vpDetectorQRCode detector;

      bool status = detector.detect(I);

      std::ostringstream legend;
      legend << detector.getNbObjects() << " bar code detected";
      vpDisplay::displayText(I, (int)I.getHeight() - 30, 10, legend.str(), vpColor::red);

      if (status) { // true if at least one QRcode is detected
        for (size_t i = 0; i < detector.getNbObjects(); i++) {

          std::vector<vpImagePoint> p = detector.getPolygon(i); // get the four corners location in the image

          for (size_t j = 0; j < p.size(); j++) {
            vpDisplay::displayCross(I, p[j], 14, vpColor::red, 3);
            std::ostringstream number;
            number << j;
            vpDisplay::displayText(I, p[j] + vpImagePoint(15, 5), number.str(), vpColor::blue);
          }

          computePose(point, p, cam, init, cMo); // resulting pose is available in cMo var
          std::cout << "Pose translation (meter): " << cMo.getTranslationVector().t() << std::endl
                    << "Pose rotation (quaternion): " << vpQuaternionVector(cMo.getRotationMatrix()).t() << std::endl;
          vpDisplay::displayFrame(I, cMo, cam, 0.05, vpColor::none, 3);

		  std::ostringstream thetext;

		  thetext << "Text: " << detector.getMessage(i) ;
          vpDisplay::displayText(I, (int)I.getHeight() - 15*(i)-45, 10, thetext.str(), vpColor::red);
          
          
          
          
		  static tf::TransformBroadcaster br;
			tf::Transform transform;
			tf::Quaternion q;
			vpQuaternionVector qv = vpQuaternionVector(cMo.getRotationMatrix());
			q[0] = qv[0];
			q[1] = qv[1];
			q[2] = qv[2];
			q[3] = qv[3];
			
			transform.setOrigin( tf::Vector3(cMo.getTranslationVector()[0],cMo.getTranslationVector()[1],cMo.getTranslationVector()[2] ));
			transform.setRotation(q);
			
			std::ostringstream thetext2;
		
			if (detector.getMessage(i) == "VTOL 3")
				thetext2 << "VTOL3";
			else if (detector.getMessage(i) == "VTOL 2")
				thetext2 << "VTOL2";
			else if (detector.getMessage(i) == "VTOL 1")
				thetext2 << "VTOL1";				
			else
				thetext2 << "VTOL";				
			
			br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "drone", thetext2.str() ));

          
          
        }
      }

      vpDisplay::displayText(I, (int)I.getHeight() - 15, 10, "Press Escape to quit...", vpColor::red);
	  vpDisplay::flush(I);   
	  
	  
	  char key;
	  bool ret = vpDisplay::getKeyboardEvent(I, &key, false);
      if ((ret) && (key == 27))
			ros::shutdown();

	  
         


	  //~ vpTime::wait(10);


	}
	catch (cv_bridge::Exception& e)  {
		ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
	}
}

int main(int argc, char **argv){
	
	
	
#if defined(VISP_HAVE_ZBAR)
  try {
    vpImageIo::read(I, "/home/dhomanhuri/catkin_ws_krti2020/src/KRTI2020/src/1280_720.jpg");
    

  #if defined(VISP_HAVE_X11)
      vpDisplayX d(I);
  #elif defined(VISP_HAVE_GDI)
      vpDisplayGDI d(I);
  #elif defined(VISP_HAVE_OPENCV)
      vpDisplayOpenCV d(I);
  #endif


	cv::namedWindow("view");
    
	
	
	// Initialise ROS
	ros::init(argc, argv, "qrpose_estimation");
	ros::NodeHandle nh;
	
	
    

  

	// Initialise subscriber and publisher
	image_transport::ImageTransport it(nh);
	image_transport::TransportHints hints("compressed");
	image_transport::Subscriber sub = it.subscribe("/usb_cam2/image_raw", 1, imageCallback,hints);
	
	
	
  
	// Spin ROS
	ros::spin();
	

  } catch (const vpException &e) {
    std::cout << "Catch an exception: " << e.getMessage() << std::endl;
  }

#else
  std::cout << "ViSP is not build with zbar 3rd party." << std::endl;
#endif
  cv::destroyWindow("view");
}
