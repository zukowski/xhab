#ifndef _ROS_xhab_ArduinoState_h
#define _ROS_xhab_ArduinoState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace xhab
{

  class ArduinoState : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t LinActState;
      uint8_t LinActWaterState;
      uint8_t PumpState;
      uint8_t UpStreamValveState;
      uint8_t DownStreamValveState;
      uint8_t LED0State;
      uint8_t LED1State;
      uint8_t LED2State;
      uint8_t LED3State;
      uint8_t LED4State;
      uint8_t LED5State;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->LinActState >> (8 * 0)) & 0xFF;
      offset += sizeof(this->LinActState);
      *(outbuffer + offset + 0) = (this->LinActWaterState >> (8 * 0)) & 0xFF;
      offset += sizeof(this->LinActWaterState);
      *(outbuffer + offset + 0) = (this->PumpState >> (8 * 0)) & 0xFF;
      offset += sizeof(this->PumpState);
      *(outbuffer + offset + 0) = (this->UpStreamValveState >> (8 * 0)) & 0xFF;
      offset += sizeof(this->UpStreamValveState);
      *(outbuffer + offset + 0) = (this->DownStreamValveState >> (8 * 0)) & 0xFF;
      offset += sizeof(this->DownStreamValveState);
      *(outbuffer + offset + 0) = (this->LED0State >> (8 * 0)) & 0xFF;
      offset += sizeof(this->LED0State);
      *(outbuffer + offset + 0) = (this->LED1State >> (8 * 0)) & 0xFF;
      offset += sizeof(this->LED1State);
      *(outbuffer + offset + 0) = (this->LED2State >> (8 * 0)) & 0xFF;
      offset += sizeof(this->LED2State);
      *(outbuffer + offset + 0) = (this->LED3State >> (8 * 0)) & 0xFF;
      offset += sizeof(this->LED3State);
      *(outbuffer + offset + 0) = (this->LED4State >> (8 * 0)) & 0xFF;
      offset += sizeof(this->LED4State);
      *(outbuffer + offset + 0) = (this->LED5State >> (8 * 0)) & 0xFF;
      offset += sizeof(this->LED5State);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->LinActState =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->LinActState);
      this->LinActWaterState =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->LinActWaterState);
      this->PumpState =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->PumpState);
      this->UpStreamValveState =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->UpStreamValveState);
      this->DownStreamValveState =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->DownStreamValveState);
      this->LED0State =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->LED0State);
      this->LED1State =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->LED1State);
      this->LED2State =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->LED2State);
      this->LED3State =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->LED3State);
      this->LED4State =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->LED4State);
      this->LED5State =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->LED5State);
     return offset;
    }

    const char * getType(){ return "xhab/ArduinoState"; };
    const char * getMD5(){ return "8873ce95d0f160d571358aaebfa141b1"; };

  };

}
#endif