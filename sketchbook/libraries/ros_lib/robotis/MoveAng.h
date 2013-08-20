#ifndef _ROS_SERVICE_MoveAng_h
#define _ROS_SERVICE_MoveAng_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace robotis
{

static const char MOVEANG[] = "robotis/MoveAng";

  class MoveAngRequest : public ros::Msg
  {
    public:
      float angle;
      float angvel;
      int32_t blocking;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      int32_t * val_angle = (int32_t *) &(this->angle);
      int32_t exp_angle = (((*val_angle)>>23)&255);
      if(exp_angle != 0)
        exp_angle += 1023-127;
      int32_t sig_angle = *val_angle;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_angle<<5) & 0xff;
      *(outbuffer + offset++) = (sig_angle>>3) & 0xff;
      *(outbuffer + offset++) = (sig_angle>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_angle<<4) & 0xF0) | ((sig_angle>>19)&0x0F);
      *(outbuffer + offset++) = (exp_angle>>4) & 0x7F;
      if(this->angle < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_angvel = (int32_t *) &(this->angvel);
      int32_t exp_angvel = (((*val_angvel)>>23)&255);
      if(exp_angvel != 0)
        exp_angvel += 1023-127;
      int32_t sig_angvel = *val_angvel;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_angvel<<5) & 0xff;
      *(outbuffer + offset++) = (sig_angvel>>3) & 0xff;
      *(outbuffer + offset++) = (sig_angvel>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_angvel<<4) & 0xF0) | ((sig_angvel>>19)&0x0F);
      *(outbuffer + offset++) = (exp_angvel>>4) & 0x7F;
      if(this->angvel < 0) *(outbuffer + offset -1) |= 0x80;
      union {
        int32_t real;
        uint32_t base;
      } u_blocking;
      u_blocking.real = this->blocking;
      *(outbuffer + offset + 0) = (u_blocking.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_blocking.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_blocking.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_blocking.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->blocking);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t * val_angle = (uint32_t*) &(this->angle);
      offset += 3;
      *val_angle = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_angle |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_angle |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_angle |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_angle = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_angle |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_angle !=0)
        *val_angle |= ((exp_angle)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->angle = -this->angle;
      uint32_t * val_angvel = (uint32_t*) &(this->angvel);
      offset += 3;
      *val_angvel = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_angvel |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_angvel |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_angvel |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_angvel = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_angvel |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_angvel !=0)
        *val_angvel |= ((exp_angvel)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->angvel = -this->angvel;
      union {
        int32_t real;
        uint32_t base;
      } u_blocking;
      u_blocking.base = 0;
      u_blocking.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_blocking.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_blocking.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_blocking.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->blocking = u_blocking.real;
      offset += sizeof(this->blocking);
     return offset;
    }

    const char * getType(){ return MOVEANG; };
    const char * getMD5(){ return "0b06a5bbd694fba6102f1418541d5e49"; };

  };

  class MoveAngResponse : public ros::Msg
  {
    public:

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return MOVEANG; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class MoveAng {
    public:
    typedef MoveAngRequest Request;
    typedef MoveAngResponse Response;
  };

}
#endif
