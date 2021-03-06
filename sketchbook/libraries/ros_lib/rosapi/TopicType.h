#ifndef _ROS_SERVICE_TopicType_h
#define _ROS_SERVICE_TopicType_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rosapi
{

static const char TOPICTYPE[] = "rosapi/TopicType";

  class TopicTypeRequest : public ros::Msg
  {
    public:
      char * topic;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t * length_topic = (uint32_t *)(outbuffer + offset);
      *length_topic = strlen( (const char*) this->topic);
      offset += 4;
      memcpy(outbuffer + offset, this->topic, *length_topic);
      offset += *length_topic;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_topic = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_topic; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_topic-1]=0;
      this->topic = (char *)(inbuffer + offset-1);
      offset += length_topic;
     return offset;
    }

    const char * getType(){ return TOPICTYPE; };
    const char * getMD5(){ return "d8f94bae31b356b24d0427f80426d0c3"; };

  };

  class TopicTypeResponse : public ros::Msg
  {
    public:
      char * type;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t * length_type = (uint32_t *)(outbuffer + offset);
      *length_type = strlen( (const char*) this->type);
      offset += 4;
      memcpy(outbuffer + offset, this->type, *length_type);
      offset += *length_type;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_type = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_type; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_type-1]=0;
      this->type = (char *)(inbuffer + offset-1);
      offset += length_type;
     return offset;
    }

    const char * getType(){ return TOPICTYPE; };
    const char * getMD5(){ return "dc67331de85cf97091b7d45e5c64ab75"; };

  };

  class TopicType {
    public:
    typedef TopicTypeRequest Request;
    typedef TopicTypeResponse Response;
  };

}
#endif
