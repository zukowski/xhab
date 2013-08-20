#ifndef _ROS_moveit_msgs_BenchmarkPipelineRequest_h
#define _ROS_moveit_msgs_BenchmarkPipelineRequest_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "moveit_msgs/PlanningScene.h"
#include "moveit_msgs/MotionPlanRequest.h"

namespace moveit_msgs
{

  class BenchmarkPipelineRequest : public ros::Msg
  {
    public:
      moveit_msgs::PlanningScene scene;
      moveit_msgs::MotionPlanRequest motion_plan_request;
      uint32_t average_count;
      char * filename;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->scene.serialize(outbuffer + offset);
      offset += this->motion_plan_request.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->average_count >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->average_count >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->average_count >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->average_count >> (8 * 3)) & 0xFF;
      offset += sizeof(this->average_count);
      uint32_t * length_filename = (uint32_t *)(outbuffer + offset);
      *length_filename = strlen( (const char*) this->filename);
      offset += 4;
      memcpy(outbuffer + offset, this->filename, *length_filename);
      offset += *length_filename;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->scene.deserialize(inbuffer + offset);
      offset += this->motion_plan_request.deserialize(inbuffer + offset);
      this->average_count =  ((uint32_t) (*(inbuffer + offset)));
      this->average_count |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->average_count |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->average_count |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->average_count);
      uint32_t length_filename = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_filename; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_filename-1]=0;
      this->filename = (char *)(inbuffer + offset-1);
      offset += length_filename;
     return offset;
    }

    const char * getType(){ return "moveit_msgs/BenchmarkPipelineRequest"; };
    const char * getMD5(){ return "e1e534d47b0cf64525cd25df0f2425da"; };

  };

}
#endif