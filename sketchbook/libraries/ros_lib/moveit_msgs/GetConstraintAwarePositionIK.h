#ifndef _ROS_SERVICE_GetConstraintAwarePositionIK_h
#define _ROS_SERVICE_GetConstraintAwarePositionIK_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ros/duration.h"
#include "moveit_msgs/ContactInformation.h"
#include "moveit_msgs/RobotState.h"
#include "moveit_msgs/MoveItErrorCodes.h"
#include "moveit_msgs/ConstraintEvalResults.h"
#include "moveit_msgs/Constraints.h"
#include "moveit_msgs/PositionIKRequest.h"

namespace moveit_msgs
{

static const char GETCONSTRAINTAWAREPOSITIONIK[] = "moveit_msgs/GetConstraintAwarePositionIK";

  class GetConstraintAwarePositionIKRequest : public ros::Msg
  {
    public:
      moveit_msgs::PositionIKRequest ik_request;
      moveit_msgs::Constraints constraints;
      ros::Duration timeout;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->ik_request.serialize(outbuffer + offset);
      offset += this->constraints.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->timeout.sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->timeout.sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->timeout.sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->timeout.sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->timeout.sec);
      *(outbuffer + offset + 0) = (this->timeout.nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->timeout.nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->timeout.nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->timeout.nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->timeout.nsec);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->ik_request.deserialize(inbuffer + offset);
      offset += this->constraints.deserialize(inbuffer + offset);
      this->timeout.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->timeout.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->timeout.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->timeout.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->timeout.sec);
      this->timeout.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->timeout.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->timeout.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->timeout.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->timeout.nsec);
     return offset;
    }

    const char * getType(){ return GETCONSTRAINTAWAREPOSITIONIK; };
    const char * getMD5(){ return "f0f70d18c2ee81b6510a8eec4448a3b3"; };

  };

  class GetConstraintAwarePositionIKResponse : public ros::Msg
  {
    public:
      moveit_msgs::RobotState solution;
      moveit_msgs::MoveItErrorCodes error_code;
      moveit_msgs::ConstraintEvalResults constraint_eval_results;
      uint8_t contact_information_length;
      moveit_msgs::ContactInformation st_contact_information;
      moveit_msgs::ContactInformation * contact_information;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->solution.serialize(outbuffer + offset);
      offset += this->error_code.serialize(outbuffer + offset);
      offset += this->constraint_eval_results.serialize(outbuffer + offset);
      *(outbuffer + offset++) = contact_information_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < contact_information_length; i++){
      offset += this->contact_information[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->solution.deserialize(inbuffer + offset);
      offset += this->error_code.deserialize(inbuffer + offset);
      offset += this->constraint_eval_results.deserialize(inbuffer + offset);
      uint8_t contact_information_lengthT = *(inbuffer + offset++);
      if(contact_information_lengthT > contact_information_length)
        this->contact_information = (moveit_msgs::ContactInformation*)realloc(this->contact_information, contact_information_lengthT * sizeof(moveit_msgs::ContactInformation));
      offset += 3;
      contact_information_length = contact_information_lengthT;
      for( uint8_t i = 0; i < contact_information_length; i++){
      offset += this->st_contact_information.deserialize(inbuffer + offset);
        memcpy( &(this->contact_information[i]), &(this->st_contact_information), sizeof(moveit_msgs::ContactInformation));
      }
     return offset;
    }

    const char * getType(){ return GETCONSTRAINTAWAREPOSITIONIK; };
    const char * getMD5(){ return "bb96cb9709825b9531ac097446ac1de9"; };

  };

  class GetConstraintAwarePositionIK {
    public:
    typedef GetConstraintAwarePositionIKRequest Request;
    typedef GetConstraintAwarePositionIKResponse Response;
  };

}
#endif
