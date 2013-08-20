#ifndef _ROS_moveit_msgs_BenchmarkPluginResponse_h
#define _ROS_moveit_msgs_BenchmarkPluginResponse_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "moveit_msgs/PlannerInterfaceDescription.h"
#include "moveit_msgs/MotionPlanDetailedResponse.h"
#include "moveit_msgs/MoveItErrorCodes.h"

namespace moveit_msgs
{

  class BenchmarkPluginResponse : public ros::Msg
  {
    public:
      uint8_t planner_interfaces_length;
      moveit_msgs::PlannerInterfaceDescription st_planner_interfaces;
      moveit_msgs::PlannerInterfaceDescription * planner_interfaces;
      uint8_t responses_length;
      moveit_msgs::MotionPlanDetailedResponse st_responses;
      moveit_msgs::MotionPlanDetailedResponse * responses;
      char * filename;
      moveit_msgs::MoveItErrorCodes error_code;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = planner_interfaces_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < planner_interfaces_length; i++){
      offset += this->planner_interfaces[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = responses_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < responses_length; i++){
      offset += this->responses[i].serialize(outbuffer + offset);
      }
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
      uint8_t planner_interfaces_lengthT = *(inbuffer + offset++);
      if(planner_interfaces_lengthT > planner_interfaces_length)
        this->planner_interfaces = (moveit_msgs::PlannerInterfaceDescription*)realloc(this->planner_interfaces, planner_interfaces_lengthT * sizeof(moveit_msgs::PlannerInterfaceDescription));
      offset += 3;
      planner_interfaces_length = planner_interfaces_lengthT;
      for( uint8_t i = 0; i < planner_interfaces_length; i++){
      offset += this->st_planner_interfaces.deserialize(inbuffer + offset);
        memcpy( &(this->planner_interfaces[i]), &(this->st_planner_interfaces), sizeof(moveit_msgs::PlannerInterfaceDescription));
      }
      uint8_t responses_lengthT = *(inbuffer + offset++);
      if(responses_lengthT > responses_length)
        this->responses = (moveit_msgs::MotionPlanDetailedResponse*)realloc(this->responses, responses_lengthT * sizeof(moveit_msgs::MotionPlanDetailedResponse));
      offset += 3;
      responses_length = responses_lengthT;
      for( uint8_t i = 0; i < responses_length; i++){
      offset += this->st_responses.deserialize(inbuffer + offset);
        memcpy( &(this->responses[i]), &(this->st_responses), sizeof(moveit_msgs::MotionPlanDetailedResponse));
      }
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

    const char * getType(){ return "moveit_msgs/BenchmarkPluginResponse"; };
    const char * getMD5(){ return "acdcfb0008565074a1b4dcad3bbcbea6"; };

  };

}
#endif