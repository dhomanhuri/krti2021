#! /usr/bin/env python

from tf import TransformBroadcaster
import rospy
from rospy import Time 

def main():
    rospy.init_node('my_broadcaster')
    
    b = TransformBroadcaster()
    
    translation = (0.0, 0.0, 0.0)
    rotation = (0.0, 0.0, 0.0, 1.0)
    rate = rospy.Rate(5)  # 5hz
    
    while not rospy.is_shutdown():
        
        translation = (2.1, 2.2, 0.0)
        
        
        b.sendTransform(translation, rotation, Time.now(), '/drone', '/ilyastf')
        rate.sleep()
    


if __name__ == '__main__':
    main()