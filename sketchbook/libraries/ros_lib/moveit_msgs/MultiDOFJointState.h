#ifndef _ROS_moveit_msgs_MultiDOFJointState_h
#define _ROS_moveit_msgs_MultiDOFJointState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Transform.h"

namespace moveit_msgs
{

  class MultiDOFJointState : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t joint_names_length;
      char* st_joint_names;
      char* * joint_names;
      uint8_t joint_transforms_length;
      geometry_msgs::Transform st_joint_transforms;
      geometry_msgs::Transform * joint_transforms;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = joint_names_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < joint_names_length; i++){
      uint32_t * length_joint_namesi = (uint32_t *)(outbuffer + offset);
      *length_joint_namesi = strlen( (const char*) this->joint_names[i]);
      offset += 4;
      memcpy(outbuffer + offset, this->joint_names[i], *length_joint_namesi);
      offset += *length_joint_namesi;
      }
      *(outbuffer + offset++) = joint_transforms_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < joint_transforms_length; i++){
      offset += this->joint_transforms[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t joint_names_lengthT = *(inbuffer + offset++);
      if(joint_names_lengthT > joint_names_length)
        this->joint_names = (char**)realloc(this->joint_names, joint_names_lengthT * sizeof(char*));
      offset += 3;
      joint_names_length = joint_names_lengthT;
      for( uint8_t i = 0; i < joint_names_length; i++){
      uint32_t length_st_joint_names = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_joint_names; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_joint_names-1]=0;
      this->st_joint_names = (char *)(inbuffer + offset-1);
      offset += length_st_joint_names;
        memcpy( &(this->joint_names[i]), &(this->st_joint_names), sizeof(char*));
      }
      uint8_t joint_transforms_lengthT = *(inbuffer + offset++);
      if(joint_transforms_lengthT > joint_transforms_length)
        this->joint_transforms = (geometry_msgs::Transform*)realloc(this->joint_transforms, joint_transforms_lengthT * sizeof(geometry_msgs::Transform));
      offset += 3;
      joint_transforms_length = joint_transforms_lengthT;
      for( uint8_t i = 0; i < joint_transforms_length; i++){
      offset += this->st_joint_transforms.deserialize(inbuffer + offset);
        memcpy( &(this->joint_transforms[i]), &(this->st_joint_transforms), sizeof(geometry_msgs::Transform));
      }
     return offset;
    }

    const char * getType(){ return "moveit_msgs/MultiDOFJointState"; };
    const char * getMD5(){ return "e0c2a2499024d75440a4676b47b7e2ac"; };

  };

}
#endif