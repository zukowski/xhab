#ifndef _ROS_SERVICE_ConstructConstraintApproximation_h
#define _ROS_SERVICE_ConstructConstraintApproximation_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "moveit_msgs/RobotState.h"
#include "moveit_msgs/Constraints.h"

namespace moveit_msgs
{

static const char CONSTRUCTCONSTRAINTAPPROXIMATION[] = "moveit_msgs/ConstructConstraintApproximation";

  class ConstructConstraintApproximationRequest : public ros::Msg
  {
    public:
      moveit_msgs::RobotState start_state;
      char * group;
      char * state_space_parameterization;
      uint32_t samples;
      uint32_t edges_per_sample;
      moveit_msgs::Constraints constraint;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->start_state.serialize(outbuffer + offset);
      uint32_t * length_group = (uint32_t *)(outbuffer + offset);
      *length_group = strlen( (const char*) this->group);
      offset += 4;
      memcpy(outbuffer + offset, this->group, *length_group);
      offset += *length_group;
      uint32_t * length_state_space_parameterization = (uint32_t *)(outbuffer + offset);
      *length_state_space_parameterization = strlen( (const char*) this->state_space_parameterization);
      offset += 4;
      memcpy(outbuffer + offset, this->state_space_parameterization, *length_state_space_parameterization);
      offset += *length_state_space_parameterization;
      *(outbuffer + offset + 0) = (this->samples >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->samples >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->samples >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->samples >> (8 * 3)) & 0xFF;
      offset += sizeof(this->samples);
      *(outbuffer + offset + 0) = (this->edges_per_sample >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->edges_per_sample >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->edges_per_sample >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->edges_per_sample >> (8 * 3)) & 0xFF;
      offset += sizeof(this->edges_per_sample);
      offset += this->constraint.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->start_state.deserialize(inbuffer + offset);
      uint32_t length_group = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_group; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_group-1]=0;
      this->group = (char *)(inbuffer + offset-1);
      offset += length_group;
      uint32_t length_state_space_parameterization = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_state_space_parameterization; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_state_space_parameterization-1]=0;
      this->state_space_parameterization = (char *)(inbuffer + offset-1);
      offset += length_state_space_parameterization;
      this->samples =  ((uint32_t) (*(inbuffer + offset)));
      this->samples |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->samples |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->samples |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->samples);
      this->edges_per_sample =  ((uint32_t) (*(inbuffer + offset)));
      this->edges_per_sample |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->edges_per_sample |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->edges_per_sample |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->edges_per_sample);
      offset += this->constraint.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return CONSTRUCTCONSTRAINTAPPROXIMATION; };
    const char * getMD5(){ return "cc393e49554e8f9462a1b299eebfc5ca"; };

  };

  class ConstructConstraintApproximationResponse : public ros::Msg
  {
    public:
      float sampling_success_rate;
      float state_sampling_time;
      float state_connection_time;
      char * filename;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      int32_t * val_sampling_success_rate = (int32_t *) &(this->sampling_success_rate);
      int32_t exp_sampling_success_rate = (((*val_sampling_success_rate)>>23)&255);
      if(exp_sampling_success_rate != 0)
        exp_sampling_success_rate += 1023-127;
      int32_t sig_sampling_success_rate = *val_sampling_success_rate;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_sampling_success_rate<<5) & 0xff;
      *(outbuffer + offset++) = (sig_sampling_success_rate>>3) & 0xff;
      *(outbuffer + offset++) = (sig_sampling_success_rate>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_sampling_success_rate<<4) & 0xF0) | ((sig_sampling_success_rate>>19)&0x0F);
      *(outbuffer + offset++) = (exp_sampling_success_rate>>4) & 0x7F;
      if(this->sampling_success_rate < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_state_sampling_time = (int32_t *) &(this->state_sampling_time);
      int32_t exp_state_sampling_time = (((*val_state_sampling_time)>>23)&255);
      if(exp_state_sampling_time != 0)
        exp_state_sampling_time += 1023-127;
      int32_t sig_state_sampling_time = *val_state_sampling_time;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_state_sampling_time<<5) & 0xff;
      *(outbuffer + offset++) = (sig_state_sampling_time>>3) & 0xff;
      *(outbuffer + offset++) = (sig_state_sampling_time>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_state_sampling_time<<4) & 0xF0) | ((sig_state_sampling_time>>19)&0x0F);
      *(outbuffer + offset++) = (exp_state_sampling_time>>4) & 0x7F;
      if(this->state_sampling_time < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_state_connection_time = (int32_t *) &(this->state_connection_time);
      int32_t exp_state_connection_time = (((*val_state_connection_time)>>23)&255);
      if(exp_state_connection_time != 0)
        exp_state_connection_time += 1023-127;
      int32_t sig_state_connection_time = *val_state_connection_time;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_state_connection_time<<5) & 0xff;
      *(outbuffer + offset++) = (sig_state_connection_time>>3) & 0xff;
      *(outbuffer + offset++) = (sig_state_connection_time>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_state_connection_time<<4) & 0xF0) | ((sig_state_connection_time>>19)&0x0F);
      *(outbuffer + offset++) = (exp_state_connection_time>>4) & 0x7F;
      if(this->state_connection_time < 0) *(outbuffer + offset -1) |= 0x80;
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
      uint32_t * val_sampling_success_rate = (uint32_t*) &(this->sampling_success_rate);
      offset += 3;
      *val_sampling_success_rate = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_sampling_success_rate |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_sampling_success_rate |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_sampling_success_rate |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_sampling_success_rate = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_sampling_success_rate |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_sampling_success_rate !=0)
        *val_sampling_success_rate |= ((exp_sampling_success_rate)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->sampling_success_rate = -this->sampling_success_rate;
      uint32_t * val_state_sampling_time = (uint32_t*) &(this->state_sampling_time);
      offset += 3;
      *val_state_sampling_time = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_state_sampling_time |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_state_sampling_time |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_state_sampling_time |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_state_sampling_time = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_state_sampling_time |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_state_sampling_time !=0)
        *val_state_sampling_time |= ((exp_state_sampling_time)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->state_sampling_time = -this->state_sampling_time;
      uint32_t * val_state_connection_time = (uint32_t*) &(this->state_connection_time);
      offset += 3;
      *val_state_connection_time = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_state_connection_time |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_state_connection_time |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_state_connection_time |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_state_connection_time = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_state_connection_time |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_state_connection_time !=0)
        *val_state_connection_time |= ((exp_state_connection_time)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->state_connection_time = -this->state_connection_time;
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

    const char * getType(){ return CONSTRUCTCONSTRAINTAPPROXIMATION; };
    const char * getMD5(){ return "96dfd55e2e587f8023100076cc3e31c9"; };

  };

  class ConstructConstraintApproximation {
    public:
    typedef ConstructConstraintApproximationRequest Request;
    typedef ConstructConstraintApproximationResponse Response;
  };

}
#endif
