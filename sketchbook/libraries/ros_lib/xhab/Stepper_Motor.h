#ifndef _ROS_xhab_Stepper_Motor_h
#define _ROS_xhab_Stepper_Motor_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace xhab
{

  class Stepper_Motor : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t direction;
      bool enable_hold;
      uint32_t steps_desired;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->direction >> (8 * 0)) & 0xFF;
      offset += sizeof(this->direction);
      union {
        bool real;
        uint8_t base;
      } u_enable_hold;
      u_enable_hold.real = this->enable_hold;
      *(outbuffer + offset + 0) = (u_enable_hold.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->enable_hold);
      *(outbuffer + offset + 0) = (this->steps_desired >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->steps_desired >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->steps_desired >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->steps_desired >> (8 * 3)) & 0xFF;
      offset += sizeof(this->steps_desired);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->direction =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->direction);
      union {
        bool real;
        uint8_t base;
      } u_enable_hold;
      u_enable_hold.base = 0;
      u_enable_hold.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->enable_hold = u_enable_hold.real;
      offset += sizeof(this->enable_hold);
      this->steps_desired =  ((uint32_t) (*(inbuffer + offset)));
      this->steps_desired |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->steps_desired |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->steps_desired |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->steps_desired);
     return offset;
    }

    const char * getType(){ return "xhab/Stepper_Motor"; };
    const char * getMD5(){ return "11312ac62411b0b463610e96bb23506b"; };

  };

}
#endif