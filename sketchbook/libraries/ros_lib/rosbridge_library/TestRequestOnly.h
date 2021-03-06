#ifndef _ROS_SERVICE_TestRequestOnly_h
#define _ROS_SERVICE_TestRequestOnly_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rosbridge_library
{

static const char TESTREQUESTONLY[] = "rosbridge_library/TestRequestOnly";

  class TestRequestOnlyRequest : public ros::Msg
  {
    public:
      int32_t data;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_data;
      u_data.real = this->data;
      *(outbuffer + offset + 0) = (u_data.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_data.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_data.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_data.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->data);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_data;
      u_data.base = 0;
      u_data.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_data.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_data.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_data.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->data = u_data.real;
      offset += sizeof(this->data);
     return offset;
    }

    const char * getType(){ return TESTREQUESTONLY; };
    const char * getMD5(){ return "da5909fbe378aeaf85e547e830cc1bb7"; };

  };

  class TestRequestOnlyResponse : public ros::Msg
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

    const char * getType(){ return TESTREQUESTONLY; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class TestRequestOnly {
    public:
    typedef TestRequestOnlyRequest Request;
    typedef TestRequestOnlyResponse Response;
  };

}
#endif
