#ifndef _ROS_moveit_msgs_PickupGoal_h
#define _ROS_moveit_msgs_PickupGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "manipulation_msgs/Grasp.h"
#include "moveit_msgs/Constraints.h"
#include "moveit_msgs/PlanningOptions.h"

namespace moveit_msgs
{

  class PickupGoal : public ros::Msg
  {
    public:
      char * target_name;
      char * group_name;
      char * end_effector;
      uint8_t possible_grasps_length;
      manipulation_msgs::Grasp st_possible_grasps;
      manipulation_msgs::Grasp * possible_grasps;
      char * collision_support_surface_name;
      bool allow_gripper_support_collision;
      moveit_msgs::Constraints path_constraints;
      uint8_t allowed_touch_objects_length;
      char* st_allowed_touch_objects;
      char* * allowed_touch_objects;
      float allowed_planning_time;
      moveit_msgs::PlanningOptions planning_options;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t * length_target_name = (uint32_t *)(outbuffer + offset);
      *length_target_name = strlen( (const char*) this->target_name);
      offset += 4;
      memcpy(outbuffer + offset, this->target_name, *length_target_name);
      offset += *length_target_name;
      uint32_t * length_group_name = (uint32_t *)(outbuffer + offset);
      *length_group_name = strlen( (const char*) this->group_name);
      offset += 4;
      memcpy(outbuffer + offset, this->group_name, *length_group_name);
      offset += *length_group_name;
      uint32_t * length_end_effector = (uint32_t *)(outbuffer + offset);
      *length_end_effector = strlen( (const char*) this->end_effector);
      offset += 4;
      memcpy(outbuffer + offset, this->end_effector, *length_end_effector);
      offset += *length_end_effector;
      *(outbuffer + offset++) = possible_grasps_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < possible_grasps_length; i++){
      offset += this->possible_grasps[i].serialize(outbuffer + offset);
      }
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
      offset += this->path_constraints.serialize(outbuffer + offset);
      *(outbuffer + offset++) = allowed_touch_objects_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < allowed_touch_objects_length; i++){
      uint32_t * length_allowed_touch_objectsi = (uint32_t *)(outbuffer + offset);
      *length_allowed_touch_objectsi = strlen( (const char*) this->allowed_touch_objects[i]);
      offset += 4;
      memcpy(outbuffer + offset, this->allowed_touch_objects[i], *length_allowed_touch_objectsi);
      offset += *length_allowed_touch_objectsi;
      }
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
      uint32_t length_target_name = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_target_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_target_name-1]=0;
      this->target_name = (char *)(inbuffer + offset-1);
      offset += length_target_name;
      uint32_t length_group_name = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_group_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_group_name-1]=0;
      this->group_name = (char *)(inbuffer + offset-1);
      offset += length_group_name;
      uint32_t length_end_effector = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_end_effector; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_end_effector-1]=0;
      this->end_effector = (char *)(inbuffer + offset-1);
      offset += length_end_effector;
      uint8_t possible_grasps_lengthT = *(inbuffer + offset++);
      if(possible_grasps_lengthT > possible_grasps_length)
        this->possible_grasps = (manipulation_msgs::Grasp*)realloc(this->possible_grasps, possible_grasps_lengthT * sizeof(manipulation_msgs::Grasp));
      offset += 3;
      possible_grasps_length = possible_grasps_lengthT;
      for( uint8_t i = 0; i < possible_grasps_length; i++){
      offset += this->st_possible_grasps.deserialize(inbuffer + offset);
        memcpy( &(this->possible_grasps[i]), &(this->st_possible_grasps), sizeof(manipulation_msgs::Grasp));
      }
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
      offset += this->path_constraints.deserialize(inbuffer + offset);
      uint8_t allowed_touch_objects_lengthT = *(inbuffer + offset++);
      if(allowed_touch_objects_lengthT > allowed_touch_objects_length)
        this->allowed_touch_objects = (char**)realloc(this->allowed_touch_objects, allowed_touch_objects_lengthT * sizeof(char*));
      offset += 3;
      allowed_touch_objects_length = allowed_touch_objects_lengthT;
      for( uint8_t i = 0; i < allowed_touch_objects_length; i++){
      uint32_t length_st_allowed_touch_objects = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_allowed_touch_objects; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_allowed_touch_objects-1]=0;
      this->st_allowed_touch_objects = (char *)(inbuffer + offset-1);
      offset += length_st_allowed_touch_objects;
        memcpy( &(this->allowed_touch_objects[i]), &(this->st_allowed_touch_objects), sizeof(char*));
      }
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

    const char * getType(){ return "moveit_msgs/PickupGoal"; };
    const char * getMD5(){ return "1cebcb0e37e32df96a3387387cbb3fab"; };

  };

}
#endif