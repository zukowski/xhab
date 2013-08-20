#ifndef _ROS_SERVICE_GetMotionPlan_h
#define _ROS_SERVICE_GetMotionPlan_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "moveit_msgs/MotionPlanRequest.h"
#include "moveit_msgs/MotionPlanResponse.h"

namespace moveit_msgs
{

static const char GETMOTIONPLAN[] = "moveit_msgs/GetMotionPlan";

  class GetMotionPlanRequest : public ros::Msg
  {
    public:
      moveit_msgs::MotionPlanRequest motion_plan_request;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->motion_plan_request.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->motion_plan_request.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return GETMOTIONPLAN; };
    const char * getMD5(){ return "62592c41ca53b667d81fbeb1e114038b"; };

  };

  class GetMotionPlanResponse : public ros::Msg
  {
    public:
      moveit_msgs::MotionPlanResponse motion_plan_response;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->motion_plan_response.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->motion_plan_response.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return GETMOTIONPLAN; };
    const char * getMD5(){ return "4669c60b708648df3af58f253a43f6f2"; };

  };

  class GetMotionPlan {
    public:
    typedef GetMotionPlanRequest Request;
    typedef GetMotionPlanResponse Response;
  };

}
#endif
