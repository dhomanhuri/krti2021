#!/usr/bin/python

# ===================================================================
# Take off and for 5 seconds
# When the QR VTOL1 is detected

# 
# Control : fuzzy logic
# Fuzzifikasi using fuzzy set 
# - under (- 0.02) is left
# - (-0.12) until 0.12 is middle
# - over 0.02 is right
# 
# Revision history:
# - x_axis fuzzy
# - y_axis fuzzy
# - error witch count until 10x error accept
# ===================================================================
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
count =0
tVTOL1_now = 0
tVTOL1_prev = 0
out=1500
out2=1500


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
        if vehicle.rangefinder.distance >= 1.2:
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
    print("Test 5m/s")


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
        print ("LR="+str(trans[0])+"UD="+str(trans[1]))
#        print ("LR="+str(trans[0])+"UD="+str(trans[1])+"FB="+str(trans[2]))

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


# x_axis fuzzifikasi
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

#y_axis fuzzyfikasi

        if iy_axis <= -0.15 :
            up = 1
            a_middle = 0
            down = 0

        if iy_axis > -0.15 and iy_axis < -0.02 :
            up = (-0.02 - iy_axis) / (-0.02 - (-0.15)) 
            a_middle = (iy_axis - (-0.15)) / (-0.02 - (-0.15))
            down = 0

        if iy_axis >= -0.02 and iy_axis <= 0.02 :
            up = 0
            a_middle = 1
            down = 0

        if iy_axis > 0.02 and iy_axis < 0.30 :
            up = 0
            a_middle = (0.30 - iy_axis) / 0.30 - 0.02
            down = (iy_axis - 0.02) / 0.30 - 0.02

        if iy_axis >= 0.30 :
            up = 0
            a_middle = 0
            down = 1



        #print ("down = ", down)
        #print ("a_middle = ", a_middle)
        #print ("up = ", up)        

        rule1=1500-(left*50)
        rule2a=1450+(middle*100)
        rule2b=1550-(middle*50)
        rule3=1550+(right*50)

#        print("rule1 = "+str(rule1))
 #       print("rule2a = "+str(rule2a))
  #      print("rule2b = "+str(rule2b))
   #     print("rule3 = "+str(rule3))

        a_rule1=1500-(down*200)
        a_rule2a=1300+(a_middle*100)
        a_rule2b=1600-(a_middle*100)
        a_rule3=1500+(up*100)

    #    print("arule1 = "+str(a_rule1))
     #   print("arule2a = "+str(a_rule2a))
      #  print("arule2b = "+str(a_rule2b))
       # print("arule3 = "+str(a_rule3))


        out=((rule1*left)+(rule2a*middle)+(rule2b*middle)+(rule3*right))/(left+middle+middle+right)
        
        out2=((a_rule1*down)+(a_rule2a*a_middle)+(a_rule2b*a_middle)+(a_rule3*up))/(down+a_middle+a_middle+up)

        

        count=0
        while tVTOL1_now == tVTOL1_prev:
            #print ("QR Lost "+str(count))
            count=count+1
            try:
                (trans,rot) = listener.lookupTransform('/drone', '/VTOL1', rospy.Time(0))
                tVTOL1_now = listener.getLatestCommonTime("/drone", "/VTOL1")
            except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
                continue
            time.sleep(0.1)

            if count == 5:
                out=1500
                break

#        print("out="+str(out)+"out2="+str(out2))
        #print ("hasil fuzzyfikasi")
#        print ("left = "+str(left)+":middle = "+str(middle)+":right = "+str(right)+":out="+str(out)+":down = "+str(down)+":a_middle = "+str(a_middle)+":up = "+str(up)+":out2="+str(out2))   
        
#        print(tVTOL1_now)
        
        if use_px==1:
            vehicle.channels.overrides[3] = int(out2)
            vehicle.channels.overrides[1] = int(out)
            #vehicle.channels.overrides[2] = 1500


        vehicle.channels.overrides[2] = 1410

        rate.sleep()

if use_px==1:
    print("Setting LAND mode...")
    vehicle.mode = dronekit.VehicleMode('LAND')
    time.sleep(10)

    # Close vehicle object before exiting script
    print("Close vehicle object")
    vehicle.close()
