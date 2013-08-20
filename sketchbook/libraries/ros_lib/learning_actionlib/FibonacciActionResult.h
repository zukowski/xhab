#ifndef _ROS_learning_actionlib_FibonacciActionResult_h
#define _ROS_learning_actionlib_FibonacciActionResult_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "actionlib_msgs/GoalStatus.h"
#include "learning_actionlib/FibonacciResult.h"

namespace learning_actionlib
{

  class FibonacciActionResult : public ros::Msg
  {
    public:
      std_msgs::Header header;
      actionlib_msgs::GoalStatus status;
      learning_actionlib::FibonacciResult result;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->status.serialize(outbuffer + offset);
      offset += this->result.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->status.deserialize(inbuffer + offset);
      offset += this->result.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "learning_actionlib/FibonacciActionResult"; };
    const char * getMD5(){ return "bee73a9fe29ae25e966e105f5553dd03"; };

  };

}
#endif