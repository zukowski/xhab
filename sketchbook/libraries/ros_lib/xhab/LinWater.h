#ifndef _ROS_xhab_LinWater_h
#define _ROS_xhab_LinWater_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace xhab
{

  class LinWater : public ros::Msg
  {
    public:
      std_msgs::Header header;
      bool pin_one;
      bool pin_two;
      int32_t mode;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_pin_one;
      u_pin_one.real = this->pin_one;
      *(outbuffer + offset + 0) = (u_pin_one.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->pin_one);
      union {
        bool real;
        uint8_t base;
      } u_pin_two;
      u_pin_two.real = this->pin_two;
      *(outbuffer + offset + 0) = (u_pin_two.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->pin_two);
      union {
        int32_t real;
        uint32_t base;
      } u_mode;
      u_mode.real = this->mode;
      *(outbuffer + offset + 0) = (u_mode.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_mode.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_mode.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_mode.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->mode);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_pin_one;
      u_pin_one.base = 0;
      u_pin_one.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->pin_one = u_pin_one.real;
      offset += sizeof(this->pin_one);
      union {
        bool real;
        uint8_t base;
      } u_pin_two;
      u_pin_two.base = 0;
      u_pin_two.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->pin_two = u_pin_two.real;
      offset += sizeof(this->pin_two);
      union {
        int32_t real;
        uint32_t base;
      } u_mode;
      u_mode.base = 0;
      u_mode.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_mode.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_mode.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_mode.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->mode = u_mode.real;
      offset += sizeof(this->mode);
     return offset;
    }

    const char * getType(){ return "xhab/LinWater"; };
    const char * getMD5(){ return "40af1f5924fb7b49470dfd941188768b"; };

  };

}
#endif