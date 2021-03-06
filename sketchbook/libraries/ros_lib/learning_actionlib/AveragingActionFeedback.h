#ifndef _ROS_learning_actionlib_AveragingActionFeedback_h
#define _ROS_learning_actionlib_AveragingActionFeedback_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "actionlib_msgs/GoalStatus.h"
#include "learning_actionlib/AveragingFeedback.h"

namespace learning_actionlib
{

  class AveragingActionFeedback : public ros::Msg
  {
    public:
      std_msgs::Header header;
      actionlib_msgs::GoalStatus status;
      learning_actionlib::AveragingFeedback feedback;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->status.serialize(outbuffer + offset);
      offset += this->feedback.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->status.deserialize(inbuffer + offset);
      offset += this->feedback.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "learning_actionlib/AveragingActionFeedback"; };
    const char * getMD5(){ return "78a4a09241b1791069223ae7ebd5b16b"; };

  };

}
#endif