#ifndef _ROS_xhab_SensorData_h
#define _ROS_xhab_SensorData_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "xhab/Temperature.h"
#include "xhab/FluidPressure.h"
#include "xhab/FluidLevel.h"
#include "xhab/ValveState.h"
#include "xhab/PumpState.h"

namespace xhab
{

  class SensorData : public ros::Msg
  {
    public:
      std_msgs::Header header;
      xhab::Temperature temp_data;
      xhab::FluidPressure pressure_data;
      xhab::FluidLevel fluid_lvl_data;
      xhab::ValveState valve_data;
      xhab::PumpState pump_data;
      int32_t moisture_data;
      int32_t ph_data;
      int32_t ec_data;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->temp_data.serialize(outbuffer + offset);
      offset += this->pressure_data.serialize(outbuffer + offset);
      offset += this->fluid_lvl_data.serialize(outbuffer + offset);
      offset += this->valve_data.serialize(outbuffer + offset);
      offset += this->pump_data.serialize(outbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_moisture_data;
      u_moisture_data.real = this->moisture_data;
      *(outbuffer + offset + 0) = (u_moisture_data.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_moisture_data.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_moisture_data.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_moisture_data.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->moisture_data);
      union {
        int32_t real;
        uint32_t base;
      } u_ph_data;
      u_ph_data.real = this->ph_data;
      *(outbuffer + offset + 0) = (u_ph_data.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ph_data.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ph_data.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ph_data.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ph_data);
      union {
        int32_t real;
        uint32_t base;
      } u_ec_data;
      u_ec_data.real = this->ec_data;
      *(outbuffer + offset + 0) = (u_ec_data.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ec_data.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ec_data.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ec_data.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ec_data);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->temp_data.deserialize(inbuffer + offset);
      offset += this->pressure_data.deserialize(inbuffer + offset);
      offset += this->fluid_lvl_data.deserialize(inbuffer + offset);
      offset += this->valve_data.deserialize(inbuffer + offset);
      offset += this->pump_data.deserialize(inbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_moisture_data;
      u_moisture_data.base = 0;
      u_moisture_data.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_moisture_data.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_moisture_data.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_moisture_data.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->moisture_data = u_moisture_data.real;
      offset += sizeof(this->moisture_data);
      union {
        int32_t real;
        uint32_t base;
      } u_ph_data;
      u_ph_data.base = 0;
      u_ph_data.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ph_data.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ph_data.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ph_data.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ph_data = u_ph_data.real;
      offset += sizeof(this->ph_data);
      union {
        int32_t real;
        uint32_t base;
      } u_ec_data;
      u_ec_data.base = 0;
      u_ec_data.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ec_data.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ec_data.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ec_data.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ec_data = u_ec_data.real;
      offset += sizeof(this->ec_data);
     return offset;
    }

    const char * getType(){ return "xhab/SensorData"; };
    const char * getMD5(){ return "72383ff65f4d498c940582aae2da6164"; };

  };

}
#endif