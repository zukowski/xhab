#ifndef _ROS_listener_JointState_h
#define _ROS_listener_JointState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace listener
{

  class JointState : public ros::Msg
  {
    public:
      float shoulder1_angle;
      float shoulder2_angle;
      float elbow1_angle;
      float elbow2_angle;
      float wrist_angle;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_shoulder1_angle;
      u_shoulder1_angle.real = this->shoulder1_angle;
      *(outbuffer + offset + 0) = (u_shoulder1_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_shoulder1_angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_shoulder1_angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_shoulder1_angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->shoulder1_angle);
      union {
        float real;
        uint32_t base;
      } u_shoulder2_angle;
      u_shoulder2_angle.real = this->shoulder2_angle;
      *(outbuffer + offset + 0) = (u_shoulder2_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_shoulder2_angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_shoulder2_angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_shoulder2_angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->shoulder2_angle);
      union {
        float real;
        uint32_t base;
      } u_elbow1_angle;
      u_elbow1_angle.real = this->elbow1_angle;
      *(outbuffer + offset + 0) = (u_elbow1_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_elbow1_angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_elbow1_angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_elbow1_angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->elbow1_angle);
      union {
        float real;
        uint32_t base;
      } u_elbow2_angle;
      u_elbow2_angle.real = this->elbow2_angle;
      *(outbuffer + offset + 0) = (u_elbow2_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_elbow2_angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_elbow2_angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_elbow2_angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->elbow2_angle);
      union {
        float real;
        uint32_t base;
      } u_wrist_angle;
      u_wrist_angle.real = this->wrist_angle;
      *(outbuffer + offset + 0) = (u_wrist_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_wrist_angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_wrist_angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_wrist_angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->wrist_angle);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_shoulder1_angle;
      u_shoulder1_angle.base = 0;
      u_shoulder1_angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_shoulder1_angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_shoulder1_angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_shoulder1_angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->shoulder1_angle = u_shoulder1_angle.real;
      offset += sizeof(this->shoulder1_angle);
      union {
        float real;
        uint32_t base;
      } u_shoulder2_angle;
      u_shoulder2_angle.base = 0;
      u_shoulder2_angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_shoulder2_angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_shoulder2_angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_shoulder2_angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->shoulder2_angle = u_shoulder2_angle.real;
      offset += sizeof(this->shoulder2_angle);
      union {
        float real;
        uint32_t base;
      } u_elbow1_angle;
      u_elbow1_angle.base = 0;
      u_elbow1_angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_elbow1_angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_elbow1_angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_elbow1_angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->elbow1_angle = u_elbow1_angle.real;
      offset += sizeof(this->elbow1_angle);
      union {
        float real;
        uint32_t base;
      } u_elbow2_angle;
      u_elbow2_angle.base = 0;
      u_elbow2_angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_elbow2_angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_elbow2_angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_elbow2_angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->elbow2_angle = u_elbow2_angle.real;
      offset += sizeof(this->elbow2_angle);
      union {
        float real;
        uint32_t base;
      } u_wrist_angle;
      u_wrist_angle.base = 0;
      u_wrist_angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_wrist_angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_wrist_angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_wrist_angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->wrist_angle = u_wrist_angle.real;
      offset += sizeof(this->wrist_angle);
     return offset;
    }

    const char * getType(){ return "listener/JointState"; };
    const char * getMD5(){ return "76e1993cb9e441ed3622b50f65c206da"; };

  };

}
#endif