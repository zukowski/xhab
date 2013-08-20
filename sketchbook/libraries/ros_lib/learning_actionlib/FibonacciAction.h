#ifndef _ROS_learning_actionlib_FibonacciAction_h
#define _ROS_learning_actionlib_FibonacciAction_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "learning_actionlib/FibonacciActionGoal.h"
#include "learning_actionlib/FibonacciActionResult.h"
#include "learning_actionlib/FibonacciActionFeedback.h"

namespace learning_actionlib
{

  class FibonacciAction : public ros::Msg
  {
    public:
      learning_actionlib::FibonacciActionGoal action_goal;
      learning_actionlib::FibonacciActionResult action_result;
      learning_actionlib::FibonacciActionFeedback action_feedback;

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

    const char * getType(){ return "learning_actionlib/FibonacciAction"; };
    const char * getMD5(){ return "f59df5767bf7634684781c92598b2406"; };

  };

}
#endif