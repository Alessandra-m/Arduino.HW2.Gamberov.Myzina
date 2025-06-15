#!/usr/bin/env python3

import threading
import rospy
from std_msgs.msg import ColorRGBA

rospy.init_node('lcd_pub', anonymous=True)
pub_ = rospy.Publisher('computer/lcd/cmd', ColorRGBA, queue_size=10)

msg = ColorRGBA()


msg.b = 0
msg.r = 0
msg.g = 0

def pub():
    global pub_, msg
    pub.publish(msg)

def talker():
    global msg
    pub = rospy.Publisher('computer/lcd/cmd', ColorRGBA, queue_size=10)
    rospy.init_node('lcd_pub', anonymous=True)
    rate = rospy.Rate(10) # 10hz

    while not rospy.is_shutdown():
        msg = ColorRGBA()
        char = input().lower()
        if char == "w":
            msg.r = 1
            msg.g = 0
            msg.b = 0
            msg.a = 0
        elif char == "a":
            msg.g = 1
            msg.r = 0
            msg.b = 0
            msg.a = 0
        elif char == "s":
            msg.b = 1
            msg.r = 0
            msg.g = 0
            msg.a = 0
        elif char == "d":
            msg.a = 1
            msg.b = 0
            msg.r = 0
            msg.g = 0
        elif char == " ":
            exit()
        pub.publish(msg)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
