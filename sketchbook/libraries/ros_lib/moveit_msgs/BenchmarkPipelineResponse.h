#ifndef _ROS_moveit_msgs_BenchmarkPipelineResponse_h
#define _ROS_moveit_msgs_BenchmarkPipelineResponse_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "moveit_msgs/MotionPlanDetailedResponse.h"
#include "moveit_msgs/MoveItErrorCodes.h"

namespace moveit_msgs
{

  class BenchmarkPipelineResponse : public ros::Msg
  {
    public:
      moveit_msgs::MotionPlanDetailedResponse response;
      char * filename;
      moveit_msgs::MoveItErrorCodes error_code;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->response.serialize(outbuffer + offset);
      uint32_t * length_filename = (uint32_t *)(outbuffer + offset);
      *length_filename = strlen( (const char*) this->filename);
      offset += 4;
      memcpy(outbuffer + offset, this->filename, *length_filename);
      offset += *length_filename;
      offset += this->error_code.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->response.deserialize(inbuffer + offset);
      uint32_t length_filename = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_filename; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_filename-1]=0;
      this->filename = (char *)(inbuffer + offset-1);
      offset += length_filename;
      offset += this->error_code.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "moveit_msgs/BenchmarkPipelineResponse"; };
    const char * getMD5(){ return "12d83032a288ae45ea569cc5d5337d89"; };

  };

}
#endif