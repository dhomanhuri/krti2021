#!/usr/bin/env python

import rospy
from std_msgs.msg import Float32MultiArray



def a(msg):
	return rospy.loginfo(msg.data[0])



if __name__ == '__main__':

	rospy.init_node('listener', anonymous=False)

	a=rospy.Subscriber('koordinat', Float32MultiArray, a)
	print ("ini a "+str(a))
	rospy.spin()
	