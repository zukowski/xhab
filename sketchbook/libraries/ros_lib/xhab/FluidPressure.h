#ifndef _ROS_xhab_FluidPressure_h
#define _ROS_xhab_FluidPressure_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace xhab
{

  class FluidPressure : public ros::Msg
  {
    public:
      std_msgs::Header header;
      float side_pressure;
      float back_pressure;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_side_pressure;
      u_side_pressure.real = this->side_pressure;
      *(outbuffer + offset + 0) = (u_side_pressure.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_side_pressure.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_side_pressure.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_side_pressure.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->side_pressure);
      union {
        float real;
        uint32_t base;
      } u_back_pressure;
      u_back_pressure.real = this->back_pressure;
      *(outbuffer + offset + 0) = (u_back_pressure.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_back_pressure.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_back_pressure.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_back_pressure.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->back_pressure);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_side_pressure;
      u_side_pressure.base = 0;
      u_side_pressure.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_side_pressure.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_side_pressure.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_side_pressure.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->side_pressure = u_side_pressure.real;
      offset += sizeof(this->side_pressure);
      union {
        float real;
        uint32_t base;
      } u_back_pressure;
      u_back_pressure.base = 0;
      u_back_pressure.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_back_pressure.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_back_pressure.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_back_pressure.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->back_pressure = u_back_pressure.real;
      offset += sizeof(this->back_pressure);
     return offset;
    }

    const char * getType(){ return "xhab/FluidPressure"; };
    const char * getMD5(){ return "442d3f3279a4495edf4763fa5bf6022a"; };

  };

}
#endif