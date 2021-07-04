#!/usr/bin/python

import dronekit
import dronekit_sitl
from pymavlink import mavutil
import time

connection_string = 'udp:192.168.1.79:14550'


vehicle = dronekit.connect(connection_string, wait_ready=True, timeout=120)

# Set vehicle mode
#desired_mode = 'LOITER'
#while vehicle.mode != desired_mode:
#  vehicle.mode = dronekit.VehicleMode(desired_mode)
#  time.sleep(0.5)
vehicle.mode = dronekit.VehicleMode('LOITER')
#drop_target(0)
print("Waitting the drone is armed")
#while not vehicle.armed:
#	time.sleep(0.5)

print("Drone is ARMED")

#while not vehicle.armed:
#    print("Arming motors")
#    vehicle.armed = True
#    time.sleep(0.5)

time.sleep(1)
print("Taking off")
vehicle.channels.overrides[3] = 1657
time.sleep(5)

print("Setting LAND mode...")
vehicle.mode = dronekit.VehicleMode('LAND')
time.sleep(10)

# Close vehicle object before exiting script
print("Close vehicle object")
vehicle.close()

