#!/usr/bin/env python

#I created a class cause I was thinking of merging all the questons. But the code wasnt readable so i split them.
import rospy
from geometry_msgs.msg import Twist

class move:
	def __init__(self):
	 	rospy.init_node('circle')
		self.pub = rospy.Publisher('cmd_vel', Twist, queue_size=10)
		
	def circle(self):
		radius = float(input("Enter the radius in units: "))
		twist = Twist()
		twist.linear.x = radius*0.1
		twist.angular.z = 0.1 
		self.pub.publish(twist)
		print twist
	

if __name__ == "__main__":
	
	mov = move()
	rate = rospy.Rate(1)
	
	while not rospy.is_shutdown():
		mov.circle()
		rate.sleep()
			


