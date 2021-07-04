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


print("Setting LAND mode...")
vehicle.mode = dronekit.VehicleMode('LAND')
time.sleep(10)

# Close vehicle object before exiting script
print("Close vehicle object")
vehicle.close()
