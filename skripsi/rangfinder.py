#!/usr/bin/python

import dronekit
import dronekit_sitl
from pymavlink import mavutil
import time
print "import berhasil"
connection_string = 'udp:10.42.0.161:14550'

print "set connection_string"
vehicle = dronekit.connect(connection_string, wait_ready=True, timeout=150)
print "connection_string success"
while True:
	print vehicle.rangefinder.distance
	time.sleep(0.1)
