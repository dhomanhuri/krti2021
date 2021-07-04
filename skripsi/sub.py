#!/usr/bin/env python
import roslib; roslib.load_manifest('visp_auto_tracker')
import rospy
import tf.transformations
from geometry_msgs.msg import PoseStamped

def callback(msg):
    rospy.loginfo("Received at goal message!")
    rospy.loginfo("Timestamp: " + str(msg.header.stamp))
    rospy.loginfo("frame_id: " + str(msg.header.frame_id))

    # Copying for simplicity
    position = msg.pose.position
    quat = msg.pose.orientation
    rospy.loginfo("Point Position: [ %f, %f, %f ]"%(position.x, position.y, position.z))
    rospy.loginfo("Quat Orientation: [ %f, %f, %f, %f]"%(quat.x, quat.y, quat.z, quat.w))

    # Also print Roll, Pitch, Yaw
    euler = tf.transformations.euler_from_quaternion([quat.x, quat.y, quat.z, quat.w])
    rospy.loginfo("Euler Angles: %s"%str(euler))  

def listener():
    rospy.init_node('goal_listener', anonymous=True)
    rospy.Subscriber("/move_base_simple/goal", PoseStamped, callback)
    rospy.spin()

if __name__ == '__main__':
    listener()
