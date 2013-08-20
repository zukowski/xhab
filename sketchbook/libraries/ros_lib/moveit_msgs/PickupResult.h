#ifndef _ROS_moveit_msgs_PickupResult_h
#define _ROS_moveit_msgs_PickupResult_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "moveit_msgs/MoveItErrorCodes.h"
#include "moveit_msgs/RobotState.h"
#include "moveit_msgs/RobotTrajectory.h"
#include "manipulation_msgs/Grasp.h"
#include "manipulation_msgs/GraspResult.h"

namespace moveit_msgs
{

  class PickupResult : public ros::Msg
  {
    public:
      moveit_msgs::MoveItErrorCodes error_code;
      moveit_msgs::RobotState trajectory_start;
      uint8_t trajectory_stages_length;
      moveit_msgs::RobotTrajectory st_trajectory_stages;
      moveit_msgs::RobotTrajectory * trajectory_stages;
      uint8_t trajectory_descriptions_length;
      char* st_trajectory_descriptions;
      char* * trajectory_descriptions;
      manipulation_msgs::Grasp grasp;
      uint8_t attempted_grasps_length;
      manipulation_msgs::Grasp st_attempted_grasps;
      manipulation_msgs::Grasp * attempted_grasps;
      uint8_t attempted_grasp_results_length;
      manipulation_msgs::GraspResult st_attempted_grasp_results;
      manipulation_msgs::GraspResult * attempted_grasp_results;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->error_code.serialize(outbuffer + offset);
      offset += this->trajectory_start.serialize(outbuffer + offset);
      *(outbuffer + offset++) = trajectory_stages_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < trajectory_stages_length; i++){
      offset += this->trajectory_stages[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = trajectory_descriptions_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < trajectory_descriptions_length; i++){
      uint32_t * length_trajectory_descriptionsi = (uint32_t *)(outbuffer + offset);
      *length_trajectory_descriptionsi = strlen( (const char*) this->trajectory_descriptions[i]);
      offset += 4;
      memcpy(outbuffer + offset, this->trajectory_descriptions[i], *length_trajectory_descriptionsi);
      offset += *length_trajectory_descriptionsi;
      }
      offset += this->grasp.serialize(outbuffer + offset);
      *(outbuffer + offset++) = attempted_grasps_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < attempted_grasps_length; i++){
      offset += this->attempted_grasps[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = attempted_grasp_results_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < attempted_grasp_results_length; i++){
      offset += this->attempted_grasp_results[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->error_code.deserialize(inbuffer + offset);
      offset += this->trajectory_start.deserialize(inbuffer + offset);
      uint8_t trajectory_stages_lengthT = *(inbuffer + offset++);
      if(trajectory_stages_lengthT > trajectory_stages_length)
        this->trajectory_stages = (moveit_msgs::RobotTrajectory*)realloc(this->trajectory_stages, trajectory_stages_lengthT * sizeof(moveit_msgs::RobotTrajectory));
      offset += 3;
      trajectory_stages_length = trajectory_stages_lengthT;
      for( uint8_t i = 0; i < trajectory_stages_length; i++){
      offset += this->st_trajectory_stages.deserialize(inbuffer + offset);
        memcpy( &(this->trajectory_stages[i]), &(this->st_trajectory_stages), sizeof(moveit_msgs::RobotTrajectory));
      }
      uint8_t trajectory_descriptions_lengthT = *(inbuffer + offset++);
      if(trajectory_descriptions_lengthT > trajectory_descriptions_length)
        this->trajectory_descriptions = (char**)realloc(this->trajectory_descriptions, trajectory_descriptions_lengthT * sizeof(char*));
      offset += 3;
      trajectory_descriptions_length = trajectory_descriptions_lengthT;
      for( uint8_t i = 0; i < trajectory_descriptions_length; i++){
      uint32_t length_st_trajectory_descriptions = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_trajectory_descriptions; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_trajectory_descriptions-1]=0;
      this->st_trajectory_descriptions = (char *)(inbuffer + offset-1);
      offset += length_st_trajectory_descriptions;
        memcpy( &(this->trajectory_descriptions[i]), &(this->st_trajectory_descriptions), sizeof(char*));
      }
      offset += this->grasp.deserialize(inbuffer + offset);
      uint8_t attempted_grasps_lengthT = *(inbuffer + offset++);
      if(attempted_grasps_lengthT > attempted_grasps_length)
        this->attempted_grasps = (manipulation_msgs::Grasp*)realloc(this->attempted_grasps, attempted_grasps_lengthT * sizeof(manipulation_msgs::Grasp));
      offset += 3;
      attempted_grasps_length = attempted_grasps_lengthT;
      for( uint8_t i = 0; i < attempted_grasps_length; i++){
      offset += this->st_attempted_grasps.deserialize(inbuffer + offset);
        memcpy( &(this->attempted_grasps[i]), &(this->st_attempted_grasps), sizeof(manipulation_msgs::Grasp));
      }
      uint8_t attempted_grasp_results_lengthT = *(inbuffer + offset++);
      if(attempted_grasp_results_lengthT > attempted_grasp_results_length)
        this->attempted_grasp_results = (manipulation_msgs::GraspResult*)realloc(this->attempted_grasp_results, attempted_grasp_results_lengthT * sizeof(manipulation_msgs::GraspResult));
      offset += 3;
      attempted_grasp_results_length = attempted_grasp_results_lengthT;
      for( uint8_t i = 0; i < attempted_grasp_results_length; i++){
      offset += this->st_attempted_grasp_results.deserialize(inbuffer + offset);
        memcpy( &(this->attempted_grasp_results[i]), &(this->st_attempted_grasp_results), sizeof(manipulation_msgs::GraspResult));
      }
     return offset;
    }

    const char * getType(){ return "moveit_msgs/PickupResult"; };
    const char * getMD5(){ return "e1883e98c5b057f482ab141c357e6511"; };

  };

}
#endif