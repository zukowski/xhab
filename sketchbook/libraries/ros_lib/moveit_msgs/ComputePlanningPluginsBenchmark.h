#ifndef _ROS_SERVICE_ComputePlanningPluginsBenchmark_h
#define _ROS_SERVICE_ComputePlanningPluginsBenchmark_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "moveit_msgs/BenchmarkPluginRequest.h"
#include "moveit_msgs/BenchmarkPluginResponse.h"

namespace moveit_msgs
{

static const char COMPUTEPLANNINGPLUGINSBENCHMARK[] = "moveit_msgs/ComputePlanningPluginsBenchmark";

  class ComputePlanningPluginsBenchmarkRequest : public ros::Msg
  {
    public:
      moveit_msgs::BenchmarkPluginRequest benchmark_request;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->benchmark_request.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->benchmark_request.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return COMPUTEPLANNINGPLUGINSBENCHMARK; };
    const char * getMD5(){ return "574fd3a72c4b93c7336c5131b9b75b8c"; };

  };

  class ComputePlanningPluginsBenchmarkResponse : public ros::Msg
  {
    public:
      moveit_msgs::BenchmarkPluginResponse benchmark_response;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->benchmark_response.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->benchmark_response.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return COMPUTEPLANNINGPLUGINSBENCHMARK; };
    const char * getMD5(){ return "25ebdbd01d6015bcb459a5d0a761d8a0"; };

  };

  class ComputePlanningPluginsBenchmark {
    public:
    typedef ComputePlanningPluginsBenchmarkRequest Request;
    typedef ComputePlanningPluginsBenchmarkResponse Response;
  };

}
#endif
