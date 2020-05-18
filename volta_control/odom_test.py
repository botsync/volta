#!/usr/bin/env python

import rospy
import time
from geometry_msgs.msg import Twist

def mover():
  pub = rospy.Publisher('/cmd_vel',Twist,queue_size=1)
  time.sleep(1)
  twist = Twist()
  twist.linear.x = 0
  twist.linear.y = 0
  twist.linear.z = 0
  twist.angular.x = 0
  twist.angular.y = 0
  twist.angular.z = -0.314
  pub.publish(twist)

  time.sleep(10)

  twist = Twist()
  twist.linear.x = 0
  twist.linear.y = 0
  twist.linear.z = 0
  twist.angular.x = 0
  twist.angular.y = 0
  twist.angular.z = 0
  pub.publish(twist)

if __name__ == '__main__':
  rospy.init_node('mover', anonymous=True)
  try:
    mover()
    print ("Done")
  except KeyboardInterrupt:
    pass