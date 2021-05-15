#!/usr/bin/env python

import math
from math import sin, cos, pi
import sympy as sp

import rospy
import tf
from numpy import *
from numpy.linalg import inv
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Point, Pose, Quaternion, Twist, Vector3

class Server:
	def __init__(self):
		self.alp = sp.Matrix([[0*pi/180, 120*pi/180, 240*pi/180]]).transpose() #robot specification
		self.enc = sp.Matrix([[0., 0., 0.]]).transpose()
		self.position = sp.Matrix([[0., 0., 0.]]).transpose()
		self.ts = 0.1#0.0635
		self.th = 0.*pi/180.
		self.ppr = 91.
		self.l = 0.20 #wheel position from the center of robot 20 cm
		self.r = 0.05 #wheel radius 5 cm
		self.Jr = self.jacobianR()
		self.w_enc = array([[0.,0.,0.]]).T
		self.current_time = rospy.Time.now()
		self.last_time = rospy.Time.now()
		
	def get_encoder(self, dat):
		#k = 3.956 * pi/180.
		k = 2.*pi*self.r
		self.enc[0, 0] = k*dat.y/self.ppr #w1 y = belakang
		self.enc[1, 0] = k*dat.z/self.ppr #w2 z = kanan
		self.enc[2, 0] = k*dat.x/self.ppr #w3 x = kiri
		self.update_position()

	def jacobianR(self):
		Js=sp.Matrix([[0.,0.,0.],[0.,0.,0.],[0.,0.,0.]])
		Js[0,0]=sp.cos(self.alp[0,0])
		Js[0,1]=sp.cos(self.alp[1,0])
		Js[0,2]=sp.cos(self.alp[2,0])
		Js[1,0]=sp.sin(self.alp[0,0])
		Js[1,1]=sp.sin(self.alp[1,0])
		Js[1,2]=sp.sin(self.alp[2,0])
		Js[2,0]=1./self.l
		Js[2,1]=1./self.l
		Js[2,2]=1./self.l
		#print(Jr)
		return self.r*Js

	def jacobianW(self,th,Jr):
		rotZ = sp.Matrix([[sp.cos(th), -sp.sin(th), 0.], [sp.sin(th), sp.cos(th), 0.], [0., 0., 1]])
		#print(rotZ)
		Jw = rotZ*Jr
		return Jw

	def update_position(self):
		self.current_time = rospy.Time.now()
		#==================== position update from encoder =====================================
		self.w_enc[0,0] = self.enc[0]/self.ts#w1
		self.w_enc[1,0] = self.enc[1]/self.ts#w2
		self.w_enc[2,0] = self.enc[2]/self.ts#w3
		J = self.jacobianW(self.th, self.Jr)
		#compute x dot
		x_dot = J*self.w_enc
		self.Jinv = J.inv()
		#scalling the x_dot
		x_dot[0,0] = x_dot[0,0] * 6. / 0.46# * 6. / 9.3
		x_dot[1,0] = x_dot[1,0] * 9. / 0.69# * 9. / 13.74
		x_dot[2,0] = x_dot[2,0] * 2 * pi# * 6.28 / 20.40
		#twist value
		vx = x_dot[0,0]
		vy = x_dot[1,0]
		vth = x_dot[2,0]
		#update position
		self.position[0,0] = self.position[0,0] + x_dot[0,0] * self.ts #x
		self.position[1,0] = self.position[1,0] + x_dot[1,0] * self.ts #y
		self.position[2,0] = self.position[2,0] + x_dot[2,0] * self.ts #th
		if(self.position[2,0]<0):
			self.position[2,0] = self.position[2,0] % (-360*pi/180.)
		else:
			self.position[2,0] = self.position[2,0] % (360*pi/180.)
		#update pos
		x = self.position[0,0]
		y = self.position[1,0]
		self.th = self.position[2,0]
		#quartenion
		odom_quat = tf.transformations.quaternion_from_euler(0, 0, self.th)
		odom_broadcaster.sendTransform(
			(x, y, 0.),
			odom_quat,
			self.current_time,
			"base_link1",
			"odom1"
		)
		odom.header.stamp = self.current_time
		odom.header.frame_id = "odom1"
		odom.pose.pose = Pose(Point(x, y, 0.), Quaternion(*odom_quat))
		odom.child_frame_id = "base_link1"
		odom.twist.twist = Twist(Vector3(vx, vy, 0), Vector3(0, 0, vth))
		odom1.x = x
		odom1.y = y
		odom1.z = self.th
		odom_pub.publish(odom)
		pub1.publish(odom1)
		print self.th
		
if __name__ == "__main__":
	rospy.init_node("odometry1_node")
	odom_pub = rospy.Publisher("odom1", Odometry, queue_size=50)
	pub1 = rospy.Publisher("robot1/odometry", Vector3, queue_size=1)
	odom_broadcaster = tf.TransformBroadcaster()
	odom = Odometry()
	odom1 = Vector3()
	server = Server()
	try:
		rospy.Subscriber('/robot1/encoder', Vector3, server.get_encoder)
		rospy.spin()
	except rospy.ROSInterruptException:
		pass
