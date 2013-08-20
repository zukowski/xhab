#ifndef _ROS_SERVICE_ComputePlanningPipelineBenchmark_h
#define _ROS_SERVICE_ComputePlanningPipelineBenchmark_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "moveit_msgs/BenchmarkPipelineRequest.h"
#include "moveit_msgs/BenchmarkPipelineResponse.h"

namespace moveit_msgs
{

static const char COMPUTEPLANNINGPIPELINEBENCHMARK[] = "moveit_msgs/ComputePlanningPipelineBenchmark";

  class ComputePlanningPipelineBenchmarkRequest : public ros::Msg
  {
    public:
      moveit_msgs::BenchmarkPipelineRequest benchmark_request;

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

    const char * getType(){ return COMPUTEPLANNINGPIPELINEBENCHMARK; };
    const char * getMD5(){ return "57d9f89992d3f1c1d7d3050574d86332"; };

  };

  class ComputePlanningPipelineBenchmarkResponse : public ros::Msg
  {
    public:
      moveit_msgs::BenchmarkPipelineResponse benchmark_response;

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

    const char * getType(){ return COMPUTEPLANNINGPIPELINEBENCHMARK; };
    const char * getMD5(){ return "b584cfa95e289bc75d7c2603535919ae"; };

  };

  class ComputePlanningPipelineBenchmark {
    public:
    typedef ComputePlanningPipelineBenchmarkRequest Request;
    typedef ComputePlanningPipelineBenchmarkResponse Response;
  };

}
#endif
