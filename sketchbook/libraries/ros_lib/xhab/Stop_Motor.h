#ifndef _ROS_xhab_Stop_Motor_h
#define _ROS_xhab_Stop_Motor_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace xhab
{

  class Stop_Motor : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t motor_type;
      uint8_t motor_mode;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->motor_type >> (8 * 0)) & 0xFF;
      offset += sizeof(this->motor_type);
      *(outbuffer + offset + 0) = (this->motor_mode >> (8 * 0)) & 0xFF;
      offset += sizeof(this->motor_mode);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->motor_type =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->motor_type);
      this->motor_mode =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->motor_mode);
     return offset;
    }

    const char * getType(){ return "xhab/Stop_Motor"; };
    const char * getMD5(){ return "fa66aa12b64025fbca4809a76532e064"; };

  };

}
#endif