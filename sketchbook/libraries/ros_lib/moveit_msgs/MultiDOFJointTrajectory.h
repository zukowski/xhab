#ifndef _ROS_moveit_msgs_MultiDOFJointTrajectory_h
#define _ROS_moveit_msgs_MultiDOFJointTrajectory_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "moveit_msgs/MultiDOFJointTrajectoryPoint.h"

namespace moveit_msgs
{

  class MultiDOFJointTrajectory : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t joint_names_length;
      char* st_joint_names;
      char* * joint_names;
      uint8_t points_length;
      moveit_msgs::MultiDOFJointTrajectoryPoint st_points;
      moveit_msgs::MultiDOFJointTrajectoryPoint * points;

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
      *(outbuffer + offset++) = points_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < points_length; i++){
      offset += this->points[i].serialize(outbuffer + offset);
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
      uint8_t points_lengthT = *(inbuffer + offset++);
      if(points_lengthT > points_length)
        this->points = (moveit_msgs::MultiDOFJointTrajectoryPoint*)realloc(this->points, points_lengthT * sizeof(moveit_msgs::MultiDOFJointTrajectoryPoint));
      offset += 3;
      points_length = points_lengthT;
      for( uint8_t i = 0; i < points_length; i++){
      offset += this->st_points.deserialize(inbuffer + offset);
        memcpy( &(this->points[i]), &(this->st_points), sizeof(moveit_msgs::MultiDOFJointTrajectoryPoint));
      }
     return offset;
    }

    const char * getType(){ return "moveit_msgs/MultiDOFJointTrajectory"; };
    const char * getMD5(){ return "3a92fec1ca0ae4d02f82ec55371e1ff9"; };

  };

}
#endif