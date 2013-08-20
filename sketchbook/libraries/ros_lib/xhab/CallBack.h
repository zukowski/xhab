#ifndef _ROS_xhab_CallBack_h
#define _ROS_xhab_CallBack_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace xhab
{

  class CallBack : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t cid;
      uint8_t mid;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->cid >> (8 * 0)) & 0xFF;
      offset += sizeof(this->cid);
      *(outbuffer + offset + 0) = (this->mid >> (8 * 0)) & 0xFF;
      offset += sizeof(this->mid);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      this->cid =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->cid);
      this->mid =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->mid);
     return offset;
    }

    const char * getType(){ return "xhab/CallBack"; };
    const char * getMD5(){ return "f99a0c290fd809da36bc820f8c536b49"; };

  };

}
#endif