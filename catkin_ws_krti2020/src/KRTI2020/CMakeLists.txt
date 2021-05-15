cmake_minimum_required(VERSION 2.8.3)
project(krti2020)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(VISP REQUIRED visp_core visp_blob visp_vision visp_io visp_gui visp_detection visp_sensor)

include(${VISP_USE_FILE})

include_directories(${VISP_INCLUDE_DIRS})

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  rospy
  sensor_msgs
  std_msgs
  roscpp
  image_transport	

  pcl_conversions
  pcl_ros


)

find_package(OpenCV REQUIRED)

find_package(cmake_modules REQUIRED)
find_package(Eigen REQUIRED)
include_directories($(Eigen_INCLUDE_DIRS))



###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES cam2pcl
#  CATKIN_DEPENDS cv_bridge rospy sensor_msgs std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


add_executable(qrpose_detection src/qrpose_detection.cpp)
target_link_libraries(qrpose_detection ${catkin_LIBRARIES} ${OpenCV_LIBS} ${VISP_LIBRARIES})


