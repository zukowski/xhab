#ifndef _ROS_moveit_msgs_PlaceGoal_h
#define _ROS_moveit_msgs_PlaceGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/PoseStamped.h"
#include "manipulation_msgs/Grasp.h"
#include "manipulation_msgs/GripperTranslation.h"
#include "moveit_msgs/Constraints.h"
#include "moveit_msgs/PlanningOptions.h"

namespace moveit_msgs
{

  class PlaceGoal : public ros::Msg
  {
    public:
      char * group_name;
      char * attached_object_name;
      uint8_t place_locations_length;
      geometry_msgs::PoseStamped st_place_locations;
      geometry_msgs::PoseStamped * place_locations;
      manipulation_msgs::Grasp grasp;
      float desired_retreat_distance;
      float min_retreat_distance;
      manipulation_msgs::GripperTranslation approach;
      char * collision_support_surface_name;
      bool allow_gripper_support_collision;
      float place_padding;
      moveit_msgs::Constraints path_constraints;
      float allowed_planning_time;
      moveit_msgs::PlanningOptions planning_options;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t * length_group_name = (uint32_t *)(outbuffer + offset);
      *length_group_name = strlen( (const char*) this->group_name);
      offset += 4;
      memcpy(outbuffer + offset, this->group_name, *length_group_name);
      offset += *length_group_name;
      uint32_t * length_attached_object_name = (uint32_t *)(outbuffer + offset);
      *length_attached_object_name = strlen( (const char*) this->attached_object_name);
      offset += 4;
      memcpy(outbuffer + offset, this->attached_object_name, *length_attached_object_name);
      offset += *length_attached_object_name;
      *(outbuffer + offset++) = place_locations_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < place_locations_length; i++){
      offset += this->place_locations[i].serialize(outbuffer + offset);
      }
      offset += this->grasp.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_desired_retreat_distance;
      u_desired_retreat_distance.real = this->desired_retreat_distance;
      *(outbuffer + offset + 0) = (u_desired_retreat_distance.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_desired_retreat_distance.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_desired_retreat_distance.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_desired_retreat_distance.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->desired_retreat_distance);
      union {
        float real;
        uint32_t base;
      } u_min_retreat_distance;
      u_min_retreat_distance.real = this->min_retreat_distance;
      *(outbuffer + offset + 0) = (u_min_retreat_distance.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_min_retreat_distance.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_min_retreat_distance.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_min_retreat_distance.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->min_retreat_distance);
      offset += this->approach.serialize(outbuffer + offset);
      uint32_t * length_collision_support_surface_name = (uint32_t *)(outbuffer + offset);
      *length_collision_support_surface_name = strlen( (const char*) this->collision_support_surface_name);
      offset += 4;
      memcpy(outbuffer + offset, this->collision_support_surface_name, *length_collision_support_surface_name);
      offset += *length_collision_support_surface_name;
      union {
        bool real;
        uint8_t base;
      } u_allow_gripper_support_collision;
      u_allow_gripper_support_collision.real = this->allow_gripper_support_collision;
      *(outbuffer + offset + 0) = (u_allow_gripper_support_collision.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->allow_gripper_support_collision);
      int32_t * val_place_padding = (int32_t *) &(this->place_padding);
      int32_t exp_place_padding = (((*val_place_padding)>>23)&255);
      if(exp_place_padding != 0)
        exp_place_padding += 1023-127;
      int32_t sig_place_padding = *val_place_padding;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_place_padding<<5) & 0xff;
      *(outbuffer + offset++) = (sig_place_padding>>3) & 0xff;
      *(outbuffer + offset++) = (sig_place_padding>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_place_padding<<4) & 0xF0) | ((sig_place_padding>>19)&0x0F);
      *(outbuffer + offset++) = (exp_place_padding>>4) & 0x7F;
      if(this->place_padding < 0) *(outbuffer + offset -1) |= 0x80;
      offset += this->path_constraints.serialize(outbuffer + offset);
      int32_t * val_allowed_planning_time = (int32_t *) &(this->allowed_planning_time);
      int32_t exp_allowed_planning_time = (((*val_allowed_planning_time)>>23)&255);
      if(exp_allowed_planning_time != 0)
        exp_allowed_planning_time += 1023-127;
      int32_t sig_allowed_planning_time = *val_allowed_planning_time;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_allowed_planning_time<<5) & 0xff;
      *(outbuffer + offset++) = (sig_allowed_planning_time>>3) & 0xff;
      *(outbuffer + offset++) = (sig_allowed_planning_time>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_allowed_planning_time<<4) & 0xF0) | ((sig_allowed_planning_time>>19)&0x0F);
      *(outbuffer + offset++) = (exp_allowed_planning_time>>4) & 0x7F;
      if(this->allowed_planning_time < 0) *(outbuffer + offset -1) |= 0x80;
      offset += this->planning_options.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_group_name = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_group_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_group_name-1]=0;
      this->group_name = (char *)(inbuffer + offset-1);
      offset += length_group_name;
      uint32_t length_attached_object_name = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_attached_object_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_attached_object_name-1]=0;
      this->attached_object_name = (char *)(inbuffer + offset-1);
      offset += length_attached_object_name;
      uint8_t place_locations_lengthT = *(inbuffer + offset++);
      if(place_locations_lengthT > place_locations_length)
        this->place_locations = (geometry_msgs::PoseStamped*)realloc(this->place_locations, place_locations_lengthT * sizeof(geometry_msgs::PoseStamped));
      offset += 3;
      place_locations_length = place_locations_lengthT;
      for( uint8_t i = 0; i < place_locations_length; i++){
      offset += this->st_place_locations.deserialize(inbuffer + offset);
        memcpy( &(this->place_locations[i]), &(this->st_place_locations), sizeof(geometry_msgs::PoseStamped));
      }
      offset += this->grasp.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_desired_retreat_distance;
      u_desired_retreat_distance.base = 0;
      u_desired_retreat_distance.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_desired_retreat_distance.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_desired_retreat_distance.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_desired_retreat_distance.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->desired_retreat_distance = u_desired_retreat_distance.real;
      offset += sizeof(this->desired_retreat_distance);
      union {
        float real;
        uint32_t base;
      } u_min_retreat_distance;
      u_min_retreat_distance.base = 0;
      u_min_retreat_distance.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_min_retreat_distance.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_min_retreat_distance.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_min_retreat_distance.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->min_retreat_distance = u_min_retreat_distance.real;
      offset += sizeof(this->min_retreat_distance);
      offset += this->approach.deserialize(inbuffer + offset);
      uint32_t length_collision_support_surface_name = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_collision_support_surface_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_collision_support_surface_name-1]=0;
      this->collision_support_surface_name = (char *)(inbuffer + offset-1);
      offset += length_collision_support_surface_name;
      union {
        bool real;
        uint8_t base;
      } u_allow_gripper_support_collision;
      u_allow_gripper_support_collision.base = 0;
      u_allow_gripper_support_collision.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->allow_gripper_support_collision = u_allow_gripper_support_collision.real;
      offset += sizeof(this->allow_gripper_support_collision);
      uint32_t * val_place_padding = (uint32_t*) &(this->place_padding);
      offset += 3;
      *val_place_padding = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_place_padding |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_place_padding |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_place_padding |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_place_padding = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_place_padding |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_place_padding !=0)
        *val_place_padding |= ((exp_place_padding)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->place_padding = -this->place_padding;
      offset += this->path_constraints.deserialize(inbuffer + offset);
      uint32_t * val_allowed_planning_time = (uint32_t*) &(this->allowed_planning_time);
      offset += 3;
      *val_allowed_planning_time = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_allowed_planning_time |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_allowed_planning_time |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_allowed_planning_time |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_allowed_planning_time = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_allowed_planning_time |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_allowed_planning_time !=0)
        *val_allowed_planning_time |= ((exp_allowed_planning_time)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->allowed_planning_time = -this->allowed_planning_time;
      offset += this->planning_options.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "moveit_msgs/PlaceGoal"; };
    const char * getMD5(){ return "e176065a3b0f5e3b1cc91c02100a964a"; };

  };

}
#endif