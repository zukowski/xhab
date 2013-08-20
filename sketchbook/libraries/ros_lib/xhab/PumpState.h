#ifndef _ROS_xhab_PumpState_h
#define _ROS_xhab_PumpState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace xhab
{

  class PumpState : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t pump_mode;
      uint8_t valve_1_mode;
      uint8_t valve_2_mode;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->pump_mode >> (8 * 0)) & 0xFF;
      offset += sizeof(this->pump_mode);
      *(outbuffer + offset + 0) = (this->valve_1_mode >> (8 * 0)) & 0xFF;
      offset += sizeof(this->valve_1_mode);
      *(outbuffer + offset + 0) = (this->valve_2_mode >> (8 * 0)) & 0xFF;
      offset += sizeof(this->valve_2_mode);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->pump_mode =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->pump_mode);
      this->valve_1_mode =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->valve_1_mode);
      this->valve_2_mode =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->valve_2_mode);
     return offset;
    }

    const char * getType(){ return "xhab/PumpState"; };
    const char * getMD5(){ return "426a46b7d32e9fa92eed21dcdd1f0eec"; };

  };

}
#endif