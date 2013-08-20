#ifndef _ROS_SERVICE_GetStateValidity_h
#define _ROS_SERVICE_GetStateValidity_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "moveit_msgs/CostSource.h"
#include "moveit_msgs/ContactInformation.h"
#include "moveit_msgs/RobotState.h"
#include "moveit_msgs/Constraints.h"

namespace moveit_msgs
{

static const char GETSTATEVALIDITY[] = "moveit_msgs/GetStateValidity";

  class GetStateValidityRequest : public ros::Msg
  {
    public:
      moveit_msgs::RobotState robot_state;
      char * group_name;
      uint8_t constraints_length;
      moveit_msgs::Constraints st_constraints;
      moveit_msgs::Constraints * constraints;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->robot_state.serialize(outbuffer + offset);
      uint32_t * length_group_name = (uint32_t *)(outbuffer + offset);
      *length_group_name = strlen( (const char*) this->group_name);
      offset += 4;
      memcpy(outbuffer + offset, this->group_name, *length_group_name);
      offset += *length_group_name;
      *(outbuffer + offset++) = constraints_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < constraints_length; i++){
      offset += this->constraints[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->robot_state.deserialize(inbuffer + offset);
      uint32_t length_group_name = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_group_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_group_name-1]=0;
      this->group_name = (char *)(inbuffer + offset-1);
      offset += length_group_name;
      uint8_t constraints_lengthT = *(inbuffer + offset++);
      if(constraints_lengthT > constraints_length)
        this->constraints = (moveit_msgs::Constraints*)realloc(this->constraints, constraints_lengthT * sizeof(moveit_msgs::Constraints));
      offset += 3;
      constraints_length = constraints_lengthT;
      for( uint8_t i = 0; i < constraints_length; i++){
      offset += this->st_constraints.deserialize(inbuffer + offset);
        memcpy( &(this->constraints[i]), &(this->st_constraints), sizeof(moveit_msgs::Constraints));
      }
     return offset;
    }

    const char * getType(){ return GETSTATEVALIDITY; };
    const char * getMD5(){ return "41237348c29a287b371f3255e8c30bce"; };

  };

  class GetStateValidityResponse : public ros::Msg
  {
    public:
      bool valid;
      uint8_t contacts_length;
      moveit_msgs::ContactInformation st_contacts;
      moveit_msgs::ContactInformation * contacts;
      uint8_t cost_sources_length;
      moveit_msgs::CostSource st_cost_sources;
      moveit_msgs::CostSource * cost_sources;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_valid;
      u_valid.real = this->valid;
      *(outbuffer + offset + 0) = (u_valid.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->valid);
      *(outbuffer + offset++) = contacts_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < contacts_length; i++){
      offset += this->contacts[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = cost_sources_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < cost_sources_length; i++){
      offset += this->cost_sources[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_valid;
      u_valid.base = 0;
      u_valid.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->valid = u_valid.real;
      offset += sizeof(this->valid);
      uint8_t contacts_lengthT = *(inbuffer + offset++);
      if(contacts_lengthT > contacts_length)
        this->contacts = (moveit_msgs::ContactInformation*)realloc(this->contacts, contacts_lengthT * sizeof(moveit_msgs::ContactInformation));
      offset += 3;
      contacts_length = contacts_lengthT;
      for( uint8_t i = 0; i < contacts_length; i++){
      offset += this->st_contacts.deserialize(inbuffer + offset);
        memcpy( &(this->contacts[i]), &(this->st_contacts), sizeof(moveit_msgs::ContactInformation));
      }
      uint8_t cost_sources_lengthT = *(inbuffer + offset++);
      if(cost_sources_lengthT > cost_sources_length)
        this->cost_sources = (moveit_msgs::CostSource*)realloc(this->cost_sources, cost_sources_lengthT * sizeof(moveit_msgs::CostSource));
      offset += 3;
      cost_sources_length = cost_sources_lengthT;
      for( uint8_t i = 0; i < cost_sources_length; i++){
      offset += this->st_cost_sources.deserialize(inbuffer + offset);
        memcpy( &(this->cost_sources[i]), &(this->st_cost_sources), sizeof(moveit_msgs::CostSource));
      }
     return offset;
    }

    const char * getType(){ return GETSTATEVALIDITY; };
    const char * getMD5(){ return "89f7b71316facd828319b962f3d380b0"; };

  };

  class GetStateValidity {
    public:
    typedef GetStateValidityRequest Request;
    typedef GetStateValidityResponse Response;
  };

}
#endif
