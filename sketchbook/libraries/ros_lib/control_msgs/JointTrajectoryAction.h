#ifndef _ROS_control_msgs_JointTrajectoryAction_h
#define _ROS_control_msgs_JointTrajectoryAction_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "control_msgs/JointTrajectoryActionGoal.h"
#include "control_msgs/JointTrajectoryActionResult.h"
#include "control_msgs/JointTrajectoryActionFeedback.h"

namespace control_msgs
{

  class JointTrajectoryAction : public ros::Msg
  {
    public:
      control_msgs::JointTrajectoryActionGoal action_goal;
      control_msgs::JointTrajectoryActionResult action_result;
      control_msgs::JointTrajectoryActionFeedback action_feedback;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->action_goal.serialize(outbuffer + offset);
      offset += this->action_result.serialize(outbuffer + offset);
      offset += this->action_feedback.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->action_goal.deserialize(inbuffer + offset);
      offset += this->action_result.deserialize(inbuffer + offset);
      offset += this->action_feedback.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "control_msgs/JointTrajectoryAction"; };
    const char * getMD5(){ return "368cde325f76ad543f39a85373230b73"; };

  };

}
#endif