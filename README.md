# krti2021
ssh ubiquity
jalankan usbcam2 "roslaunch usb_cam usb1.launch"
jalankan qrpose detection "rosrun krti2020 qrpose_detection /usb_cam2/image_raw /home/ubuntu/catkin_ws/src/KRTI2020/src/640_480_2.png cvdoff vdoff"
arahkan Ros master ke raspi
jalan tftest.py
tf sudah dapat di kontrol
