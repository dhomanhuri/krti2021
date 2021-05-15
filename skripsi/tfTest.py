#!/usr/bin/env python  
import roslib
#roslib.load_manifest('learning_tf')
import rospy
import math
import tf
import geometry_msgs.msg
import turtlesim.srv

if __name__ == '__main__':
    rospy.init_node('drone_tf_listener')

    listener = tf.TransformListener()


    rate = rospy.Rate(10.0)
    while not rospy.is_shutdown():
        try:
            (trans,rot) = listener.lookupTransform('/drone', '/VTOL3', rospy.Time(0))
        except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
            continue

	
	print("{:.2f} ".format(trans[0])+"{:.2f} ".format(trans[1])+"{:.2f} --> ".format(trans[2]) +"{:.2f} ".format(rot[0]) +"{:.2f} ".format(rot[1]) +"{:.2f} ".format(rot[2]) +"{:.2f} ".format(rot[3])   )
	
        

        rate.sleep()
