#ifndef _ROS_moveit_msgs_BenchmarkPluginRequest_h
#define _ROS_moveit_msgs_BenchmarkPluginRequest_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "moveit_msgs/PlanningScene.h"
#include "moveit_msgs/MotionPlanRequest.h"
#include "moveit_msgs/PlannerInterfaceDescription.h"

namespace moveit_msgs
{

  class BenchmarkPluginRequest : public ros::Msg
  {
    public:
      moveit_msgs::PlanningScene scene;
      moveit_msgs::MotionPlanRequest motion_plan_request;
      uint8_t planner_interfaces_length;
      moveit_msgs::PlannerInterfaceDescription st_planner_interfaces;
      moveit_msgs::PlannerInterfaceDescription * planner_interfaces;
      uint8_t average_count_length;
      uint32_t st_average_count;
      uint32_t * average_count;
      uint32_t default_average_count;
      bool evaluate_goal_existence_only;
      char * filename;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->scene.serialize(outbuffer + offset);
      offset += this->motion_plan_request.serialize(outbuffer + offset);
      *(outbuffer + offset++) = planner_interfaces_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < planner_interfaces_length; i++){
      offset += this->planner_interfaces[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = average_count_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < average_count_length; i++){
      *(outbuffer + offset + 0) = (this->average_count[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->average_count[i] >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->average_count[i] >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->average_count[i] >> (8 * 3)) & 0xFF;
      offset += sizeof(this->average_count[i]);
      }
      *(outbuffer + offset + 0) = (this->default_average_count >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->default_average_count >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->default_average_count >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->default_average_count >> (8 * 3)) & 0xFF;
      offset += sizeof(this->default_average_count);
      union {
        bool real;
        uint8_t base;
      } u_evaluate_goal_existence_only;
      u_evaluate_goal_existence_only.real = this->evaluate_goal_existence_only;
      *(outbuffer + offset + 0) = (u_evaluate_goal_existence_only.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->evaluate_goal_existence_only);
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
      uint8_t planner_interfaces_lengthT = *(inbuffer + offset++);
      if(planner_interfaces_lengthT > planner_interfaces_length)
        this->planner_interfaces = (moveit_msgs::PlannerInterfaceDescription*)realloc(this->planner_interfaces, planner_interfaces_lengthT * sizeof(moveit_msgs::PlannerInterfaceDescription));
      offset += 3;
      planner_interfaces_length = planner_interfaces_lengthT;
      for( uint8_t i = 0; i < planner_interfaces_length; i++){
      offset += this->st_planner_interfaces.deserialize(inbuffer + offset);
        memcpy( &(this->planner_interfaces[i]), &(this->st_planner_interfaces), sizeof(moveit_msgs::PlannerInterfaceDescription));
      }
      uint8_t average_count_lengthT = *(inbuffer + offset++);
      if(average_count_lengthT > average_count_length)
        this->average_count = (uint32_t*)realloc(this->average_count, average_count_lengthT * sizeof(uint32_t));
      offset += 3;
      average_count_length = average_count_lengthT;
      for( uint8_t i = 0; i < average_count_length; i++){
      this->st_average_count =  ((uint32_t) (*(inbuffer + offset)));
      this->st_average_count |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->st_average_count |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->st_average_count |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->st_average_count);
        memcpy( &(this->average_count[i]), &(this->st_average_count), sizeof(uint32_t));
      }
      this->default_average_count =  ((uint32_t) (*(inbuffer + offset)));
      this->default_average_count |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->default_average_count |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->default_average_count |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->default_average_count);
      union {
        bool real;
        uint8_t base;
      } u_evaluate_goal_existence_only;
      u_evaluate_goal_existence_only.base = 0;
      u_evaluate_goal_existence_only.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->evaluate_goal_existence_only = u_evaluate_goal_existence_only.real;
      offset += sizeof(this->evaluate_goal_existence_only);
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

    const char * getType(){ return "moveit_msgs/BenchmarkPluginRequest"; };
    const char * getMD5(){ return "851d07275bdbb5d30a774644c310e4c9"; };

  };

}
#endif