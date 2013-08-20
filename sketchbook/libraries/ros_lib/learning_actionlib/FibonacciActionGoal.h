#ifndef _ROS_learning_actionlib_FibonacciActionGoal_h
#define _ROS_learning_actionlib_FibonacciActionGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "actionlib_msgs/GoalID.h"
#include "learning_actionlib/FibonacciGoal.h"

namespace learning_actionlib
{

  class FibonacciActionGoal : public ros::Msg
  {
    public:
      std_msgs::Header header;
      actionlib_msgs::GoalID goal_id;
      learning_actionlib::FibonacciGoal goal;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->goal_id.serialize(outbuffer + offset);
      offset += this->goal.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->goal_id.deserialize(inbuffer + offset);
      offset += this->goal.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "learning_actionlib/FibonacciActionGoal"; };
    const char * getMD5(){ return "006871c7fa1d0e3d5fe2226bf17b2a94"; };

  };

}
#endif