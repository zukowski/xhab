#ifndef _ROS_xhab_LEDState_h
#define _ROS_xhab_LEDState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace xhab
{

  class LEDState : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t id;
      uint8_t value;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->id >> (8 * 0)) & 0xFF;
      offset += sizeof(this->id);
      *(outbuffer + offset + 0) = (this->value >> (8 * 0)) & 0xFF;
      offset += sizeof(this->value);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->id =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->id);
      this->value =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->value);
     return offset;
    }

    const char * getType(){ return "xhab/LEDState"; };
    const char * getMD5(){ return "a2e5271623c63fbfee1582ef58bfaace"; };

  };

}
#endif