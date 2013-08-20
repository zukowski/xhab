#ifndef _ROS_moveit_msgs_ConstraintEvalResults_h
#define _ROS_moveit_msgs_ConstraintEvalResults_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "moveit_msgs/ConstraintEvalResult.h"

namespace moveit_msgs
{

  class ConstraintEvalResults : public ros::Msg
  {
    public:
      bool overall_result;
      uint8_t joint_constraints_length;
      moveit_msgs::ConstraintEvalResult st_joint_constraints;
      moveit_msgs::ConstraintEvalResult * joint_constraints;
      uint8_t position_constraints_length;
      moveit_msgs::ConstraintEvalResult st_position_constraints;
      moveit_msgs::ConstraintEvalResult * position_constraints;
      uint8_t orientation_constraints_length;
      moveit_msgs::ConstraintEvalResult st_orientation_constraints;
      moveit_msgs::ConstraintEvalResult * orientation_constraints;
      uint8_t visibility_constraints_length;
      moveit_msgs::ConstraintEvalResult st_visibility_constraints;
      moveit_msgs::ConstraintEvalResult * visibility_constraints;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_overall_result;
      u_overall_result.real = this->overall_result;
      *(outbuffer + offset + 0) = (u_overall_result.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->overall_result);
      *(outbuffer + offset++) = joint_constraints_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < joint_constraints_length; i++){
      offset += this->joint_constraints[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = position_constraints_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < position_constraints_length; i++){
      offset += this->position_constraints[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = orientation_constraints_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < orientation_constraints_length; i++){
      offset += this->orientation_constraints[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = visibility_constraints_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < visibility_constraints_length; i++){
      offset += this->visibility_constraints[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_overall_result;
      u_overall_result.base = 0;
      u_overall_result.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->overall_result = u_overall_result.real;
      offset += sizeof(this->overall_result);
      uint8_t joint_constraints_lengthT = *(inbuffer + offset++);
      if(joint_constraints_lengthT > joint_constraints_length)
        this->joint_constraints = (moveit_msgs::ConstraintEvalResult*)realloc(this->joint_constraints, joint_constraints_lengthT * sizeof(moveit_msgs::ConstraintEvalResult));
      offset += 3;
      joint_constraints_length = joint_constraints_lengthT;
      for( uint8_t i = 0; i < joint_constraints_length; i++){
      offset += this->st_joint_constraints.deserialize(inbuffer + offset);
        memcpy( &(this->joint_constraints[i]), &(this->st_joint_constraints), sizeof(moveit_msgs::ConstraintEvalResult));
      }
      uint8_t position_constraints_lengthT = *(inbuffer + offset++);
      if(position_constraints_lengthT > position_constraints_length)
        this->position_constraints = (moveit_msgs::ConstraintEvalResult*)realloc(this->position_constraints, position_constraints_lengthT * sizeof(moveit_msgs::ConstraintEvalResult));
      offset += 3;
      position_constraints_length = position_constraints_lengthT;
      for( uint8_t i = 0; i < position_constraints_length; i++){
      offset += this->st_position_constraints.deserialize(inbuffer + offset);
        memcpy( &(this->position_constraints[i]), &(this->st_position_constraints), sizeof(moveit_msgs::ConstraintEvalResult));
      }
      uint8_t orientation_constraints_lengthT = *(inbuffer + offset++);
      if(orientation_constraints_lengthT > orientation_constraints_length)
        this->orientation_constraints = (moveit_msgs::ConstraintEvalResult*)realloc(this->orientation_constraints, orientation_constraints_lengthT * sizeof(moveit_msgs::ConstraintEvalResult));
      offset += 3;
      orientation_constraints_length = orientation_constraints_lengthT;
      for( uint8_t i = 0; i < orientation_constraints_length; i++){
      offset += this->st_orientation_constraints.deserialize(inbuffer + offset);
        memcpy( &(this->orientation_constraints[i]), &(this->st_orientation_constraints), sizeof(moveit_msgs::ConstraintEvalResult));
      }
      uint8_t visibility_constraints_lengthT = *(inbuffer + offset++);
      if(visibility_constraints_lengthT > visibility_constraints_length)
        this->visibility_constraints = (moveit_msgs::ConstraintEvalResult*)realloc(this->visibility_constraints, visibility_constraints_lengthT * sizeof(moveit_msgs::ConstraintEvalResult));
      offset += 3;
      visibility_constraints_length = visibility_constraints_lengthT;
      for( uint8_t i = 0; i < visibility_constraints_length; i++){
      offset += this->st_visibility_constraints.deserialize(inbuffer + offset);
        memcpy( &(this->visibility_constraints[i]), &(this->st_visibility_constraints), sizeof(moveit_msgs::ConstraintEvalResult));
      }
     return offset;
    }

    const char * getType(){ return "moveit_msgs/ConstraintEvalResults"; };
    const char * getMD5(){ return "6fb3fc94fc0379fa6eee79f54eb0d5b8"; };

  };

}
#endif