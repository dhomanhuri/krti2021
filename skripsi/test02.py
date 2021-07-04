#!/usr/bin/env python  
import roslib
#roslib.load_manifest('learning_tf')
import rospy
import math
import tf
import geometry_msgs.msg
import turtlesim.srv
import dronekit
import dronekit_sitl
from pymavlink import mavutil
import time
use_px =1
tVTOL1_now = 0
count =0
tVTOL1_prev = 0
out=1500


if use_px==1:
    print "import success"
    connection_string = 'udp:10.42.0.161:14550'
    print "set connection_string"
    vehicle = dronekit.connect(connection_string, wait_ready=True, timeout=150)
    print "connection_string success"

    print("Waitting the drone is armed")
    while not vehicle.armed:
        time.sleep(0.5)

    print("Drone is ARMED")
    time.sleep(1)

    print("Taking off")
    while True:
        vehicle.channels.overrides[3] = 1610
        if vehicle.rangefinder.distance >= 0.6:
            print('Reached target altitude: {0:.2f}m'.format(vehicle.rangefinder.distance))
            break
        else:
            print("Altitude: {0:.2f}m".format(vehicle.rangefinder.distance))
        time.sleep(0.25)

    print("Hover")
    i = 0
    while i<15:
        vehicle.channels.overrides[3] = 1500
        vehicle.channels.overrides[1] = 1500
        vehicle.channels.overrides[2] = 1500
        time.sleep(0.25)
        if i%1==0:
            print(i/4)
        i = i+1

if __name__ == '__main__':
    rospy.init_node('drone_tf_listener')

    listener = tf.TransformListener()
    print("masuk main")


    rate = rospy.Rate(10.0)
    while not rospy.is_shutdown():
        tVTOL1_prev=tVTOL1_now
        if use_px == 1:
            if tVTOL1_now==0:
                vehicle.channels.overrides[3] = 1500
                vehicle.channels.overrides[1] = 1500
                vehicle.channels.overrides[2] = 1500
                time.sleep(0.25)



        try:
            (trans,rot) = listener.lookupTransform('/drone', '/VTOL1', rospy.Time(0))
            tVTOL1_now = listener.getLatestCommonTime("/drone", "/VTOL1")
        except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
            continue



	#print("{:.2f} ".format(trans[0])+"{:.2f} ".format(trans[1])+"{:.2f} --> ".format(trans[2]) +"{:.2f} ".format(rot[0]) +"{:.2f} ".format(rot[1]) +"{:.2f} ".format(rot[2]) +"{:.2f} ".format(rot[3])   )
        #print ("LR="+str(trans[0])+"UD="+str(trans[1])+"UK="+str(trans[2]))

        #print ("fuzzy skripsi")
        #x_axis = input('Masukan x = ')
        ix_axis = float(trans[0])
        #y_axis = input('Masukan y = ')
        iy_axis = float(trans[1])
        #print (ix_axis)


        left = 0.0
        middle = 0.0
        right =0.0

        up = 0.0
        a_middle = 0.0
        down = 0.0

        if ix_axis <= -0.15 :
            left = 1
            middle = 0
            right = 0

        if ix_axis > -0.15 and ix_axis < -0.02 :
            left = (-0.02 - ix_axis) / (-0.02 - (-0.15)) 
            middle = (ix_axis - (-0.15)) / (-0.02 - (-0.15))
            right = 0

        if ix_axis >= -0.02 and ix_axis <= 0.02 :
            left = 0
            middle = 1
            right = 0

        if ix_axis > 0.02 and ix_axis < 0.15 :
            left = 0
            middle = (0.15 - ix_axis) / 0.15 - 0.02
            right = (ix_axis - 0.02) / 0.15 - 0.02

        if ix_axis >= 0.15 :
            left = 0
            middle = 0
            right = 1

        if iy_axis <= -0.15 :
            down = 1
            a_middle = 0
            up = 0

        if iy_axis > -0.15 and iy_axis < -0.02 :
            down = (-0.02 - iy_axis) / (-0.02 - (-0.15)) 
            a_middle = (iy_axis - (-0.15)) / (-0.02 - (-0.15))
            up = 0

        if iy_axis >= -0.02 and iy_axis <= 0.02 :
            down = 0
            a_middle = 1
            up = 0

        if iy_axis > 0.02 and iy_axis < 0.15 :
            down = 0
            a_middle = (0.15 - iy_axis) / 0.15 - 0.02
            up = (iy_axis - 0.02) / 0.15 - 0.02

        if iy_axis >= 0.15 :
            down = 0
            a_middle = 0
            up = 1


        #print ("hasil fuzzyfikasi")
        print ("left = "+str(left)+" middle = "+str(middle)+" right = "+str(right))   

        #print ("down = ", down)
        #print ("a_middle = ", a_middle)
        #print ("up = ", up)        

        rule1=1500-(left*100)
        rule2a=1400+(middle*100)
        rule2b=1600-(middle*100)
        rule3=1500+(right*100)

        print(rule1)
        print(rule2a)
        print(rule2b)
        print(rule3)

        out=((rule1*left)+(rule2a*middle)+(rule2b*middle)+(rule3*right))/(left+middle+middle+right)
        

        count=0
        while tVTOL1_now == tVTOL1_prev:
            print ("asda")
            count=count+1
            try:
                (trans,rot) = listener.lookupTransform('/drone', '/VTOL1', rospy.Time(0))
                tVTOL1_now = listener.getLatestCommonTime("/drone", "/VTOL1")
            except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
                continue
            time.sleep(0.1)

            if count == 10:
                out=1500
                break

        print("out=",out)
        
        print(tVTOL1_now)
        
        if use_px==1:
            vehicle.channels.overrides[3] = 1500
            vehicle.channels.overrides[1] = int(out)
            vehicle.channels.overrides[2] = 1500



        rate.sleep()

if use_px==1:
    print("Setting LAND mode...")
    vehicle.mode = dronekit.VehicleMode('LAND')
    time.sleep(10)

    # Close vehicle object before exiting script
    print("Close vehicle object")
    vehicle.close()
