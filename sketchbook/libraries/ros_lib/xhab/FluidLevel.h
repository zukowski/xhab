#ifndef _ROS_xhab_FluidLevel_h
#define _ROS_xhab_FluidLevel_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace xhab
{

  class FluidLevel : public ros::Msg
  {
    public:
      std_msgs::Header header;
      float top_lvl;
      float mid_lvl;
      float bot_lvl;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_top_lvl;
      u_top_lvl.real = this->top_lvl;
      *(outbuffer + offset + 0) = (u_top_lvl.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_top_lvl.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_top_lvl.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_top_lvl.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->top_lvl);
      union {
        float real;
        uint32_t base;
      } u_mid_lvl;
      u_mid_lvl.real = this->mid_lvl;
      *(outbuffer + offset + 0) = (u_mid_lvl.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_mid_lvl.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_mid_lvl.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_mid_lvl.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->mid_lvl);
      union {
        float real;
        uint32_t base;
      } u_bot_lvl;
      u_bot_lvl.real = this->bot_lvl;
      *(outbuffer + offset + 0) = (u_bot_lvl.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_bot_lvl.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_bot_lvl.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_bot_lvl.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->bot_lvl);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_top_lvl;
      u_top_lvl.base = 0;
      u_top_lvl.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_top_lvl.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_top_lvl.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_top_lvl.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->top_lvl = u_top_lvl.real;
      offset += sizeof(this->top_lvl);
      union {
        float real;
        uint32_t base;
      } u_mid_lvl;
      u_mid_lvl.base = 0;
      u_mid_lvl.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_mid_lvl.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_mid_lvl.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_mid_lvl.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->mid_lvl = u_mid_lvl.real;
      offset += sizeof(this->mid_lvl);
      union {
        float real;
        uint32_t base;
      } u_bot_lvl;
      u_bot_lvl.base = 0;
      u_bot_lvl.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_bot_lvl.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_bot_lvl.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_bot_lvl.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->bot_lvl = u_bot_lvl.real;
      offset += sizeof(this->bot_lvl);
     return offset;
    }

    const char * getType(){ return "xhab/FluidLevel"; };
    const char * getMD5(){ return "7073b382fc2e87f24904cc064e36f5f8"; };

  };

}
#endif