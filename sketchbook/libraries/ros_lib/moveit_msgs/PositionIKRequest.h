#ifndef _ROS_moveit_msgs_PositionIKRequest_h
#define _ROS_moveit_msgs_PositionIKRequest_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "moveit_msgs/RobotState.h"
#include "geometry_msgs/PoseStamped.h"

namespace moveit_msgs
{

  class PositionIKRequest : public ros::Msg
  {
    public:
      char * group_name;
      moveit_msgs::RobotState robot_state;
      char * ik_link_name;
      geometry_msgs::PoseStamped pose_stamped;
      uint8_t ik_link_names_length;
      char* st_ik_link_names;
      char* * ik_link_names;
      uint8_t pose_stamped_vector_length;
      geometry_msgs::PoseStamped st_pose_stamped_vector;
      geometry_msgs::PoseStamped * pose_stamped_vector;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t * length_group_name = (uint32_t *)(outbuffer + offset);
      *length_group_name = strlen( (const char*) this->group_name);
      offset += 4;
      memcpy(outbuffer + offset, this->group_name, *length_group_name);
      offset += *length_group_name;
      offset += this->robot_state.serialize(outbuffer + offset);
      uint32_t * length_ik_link_name = (uint32_t *)(outbuffer + offset);
      *length_ik_link_name = strlen( (const char*) this->ik_link_name);
      offset += 4;
      memcpy(outbuffer + offset, this->ik_link_name, *length_ik_link_name);
      offset += *length_ik_link_name;
      offset += this->pose_stamped.serialize(outbuffer + offset);
      *(outbuffer + offset++) = ik_link_names_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < ik_link_names_length; i++){
      uint32_t * length_ik_link_namesi = (uint32_t *)(outbuffer + offset);
      *length_ik_link_namesi = strlen( (const char*) this->ik_link_names[i]);
      offset += 4;
      memcpy(outbuffer + offset, this->ik_link_names[i], *length_ik_link_namesi);
      offset += *length_ik_link_namesi;
      }
      *(outbuffer + offset++) = pose_stamped_vector_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < pose_stamped_vector_length; i++){
      offset += this->pose_stamped_vector[i].serialize(outbuffer + offset);
      }
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
      offset += this->robot_state.deserialize(inbuffer + offset);
      uint32_t length_ik_link_name = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_ik_link_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_ik_link_name-1]=0;
      this->ik_link_name = (char *)(inbuffer + offset-1);
      offset += length_ik_link_name;
      offset += this->pose_stamped.deserialize(inbuffer + offset);
      uint8_t ik_link_names_lengthT = *(inbuffer + offset++);
      if(ik_link_names_lengthT > ik_link_names_length)
        this->ik_link_names = (char**)realloc(this->ik_link_names, ik_link_names_lengthT * sizeof(char*));
      offset += 3;
      ik_link_names_length = ik_link_names_lengthT;
      for( uint8_t i = 0; i < ik_link_names_length; i++){
      uint32_t length_st_ik_link_names = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_ik_link_names; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_ik_link_names-1]=0;
      this->st_ik_link_names = (char *)(inbuffer + offset-1);
      offset += length_st_ik_link_names;
        memcpy( &(this->ik_link_names[i]), &(this->st_ik_link_names), sizeof(char*));
      }
      uint8_t pose_stamped_vector_lengthT = *(inbuffer + offset++);
      if(pose_stamped_vector_lengthT > pose_stamped_vector_length)
        this->pose_stamped_vector = (geometry_msgs::PoseStamped*)realloc(this->pose_stamped_vector, pose_stamped_vector_lengthT * sizeof(geometry_msgs::PoseStamped));
      offset += 3;
      pose_stamped_vector_length = pose_stamped_vector_lengthT;
      for( uint8_t i = 0; i < pose_stamped_vector_length; i++){
      offset += this->st_pose_stamped_vector.deserialize(inbuffer + offset);
        memcpy( &(this->pose_stamped_vector[i]), &(this->st_pose_stamped_vector), sizeof(geometry_msgs::PoseStamped));
      }
     return offset;
    }

    const char * getType(){ return "moveit_msgs/PositionIKRequest"; };
    const char * getMD5(){ return "060d389f06292f720a91613cdf4495e1"; };

  };

}
#endif