#!/usr/bin/env python
import rospy
from service_first.srv import Add

if __name__ == '__main__':
    try:
        rospy.wait_for_service('add')
        add = rospy.ServiceProxy('add', Add)
        try:
            resp = add(1, 2)
            print(resp)
        except rospy.ServiceException as exc:
            print("Service did not process request: " + str(exc))
    except rospy.ROSInterruptException:
        pass
