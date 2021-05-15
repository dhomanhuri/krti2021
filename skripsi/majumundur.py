#!/usr/bin/python





import dronekit
import dronekit_sitl
from pymavlink import mavutil
import time

print "import berhasil"
connection_string = 'udp:127.0.0.1:14551'

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
	if vehicle.rangefinder.distance >= 1.1:
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

print("Front")
i = 0
while i<30:
	vehicle.channels.overrides[3] = 1500
	vehicle.channels.overrides[1] = 1500
	vehicle.channels.overrides[2] = 1400
	time.sleep(0.25)
	print('maju: {0:.1f}'.format(i/4))
	i = i+1

print("Hover")
i = 0
while i<10:
	vehicle.channels.overrides[3] = 1500
	vehicle.channels.overrides[1] = 1500
	vehicle.channels.overrides[2] = 1500
	time.sleep(0.25)
	if i%1==0:
		print(i/4)
	i = i+1

print("Back")
i = 0
while i<30:
	vehicle.channels.overrides[3] = 1500
	vehicle.channels.overrides[1] = 1500
	vehicle.channels.overrides[2] = 1600
	time.sleep(0.25)
	i = i+1
	print('mundur: {0:.1f}'.format(i/4))


print("Hover")
i = 0
while i<10:
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
