#ifndef _ROS_moveit_msgs_MoveGroupResult_h
#define _ROS_moveit_msgs_MoveGroupResult_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "moveit_msgs/MoveItErrorCodes.h"
#include "moveit_msgs/RobotState.h"
#include "moveit_msgs/RobotTrajectory.h"

namespace moveit_msgs
{

  class MoveGroupResult : public ros::Msg
  {
    public:
      moveit_msgs::MoveItErrorCodes error_code;
      moveit_msgs::RobotState trajectory_start;
      moveit_msgs::RobotTrajectory planned_trajectory;
      moveit_msgs::RobotTrajectory executed_trajectory;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->error_code.serialize(outbuffer + offset);
      offset += this->trajectory_start.serialize(outbuffer + offset);
      offset += this->planned_trajectory.serialize(outbuffer + offset);
      offset += this->executed_trajectory.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->error_code.deserialize(inbuffer + offset);
      offset += this->trajectory_start.deserialize(inbuffer + offset);
      offset += this->planned_trajectory.deserialize(inbuffer + offset);
      offset += this->executed_trajectory.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "moveit_msgs/MoveGroupResult"; };
    const char * getMD5(){ return "e1ef04a4054212d5f78ac410a54e99bc"; };

  };

}
#endif