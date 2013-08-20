#ifndef _ROS_moveit_msgs_PlaceResult_h
#define _ROS_moveit_msgs_PlaceResult_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "moveit_msgs/MoveItErrorCodes.h"
#include "geometry_msgs/PoseStamped.h"
#include "manipulation_msgs/PlaceLocationResult.h"

namespace moveit_msgs
{

  class PlaceResult : public ros::Msg
  {
    public:
      moveit_msgs::MoveItErrorCodes manipulation_result;
      geometry_msgs::PoseStamped place_location;
      uint8_t attempted_locations_length;
      geometry_msgs::PoseStamped st_attempted_locations;
      geometry_msgs::PoseStamped * attempted_locations;
      uint8_t attempted_location_results_length;
      manipulation_msgs::PlaceLocationResult st_attempted_location_results;
      manipulation_msgs::PlaceLocationResult * attempted_location_results;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->manipulation_result.serialize(outbuffer + offset);
      offset += this->place_location.serialize(outbuffer + offset);
      *(outbuffer + offset++) = attempted_locations_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < attempted_locations_length; i++){
      offset += this->attempted_locations[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = attempted_location_results_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < attempted_location_results_length; i++){
      offset += this->attempted_location_results[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->manipulation_result.deserialize(inbuffer + offset);
      offset += this->place_location.deserialize(inbuffer + offset);
      uint8_t attempted_locations_lengthT = *(inbuffer + offset++);
      if(attempted_locations_lengthT > attempted_locations_length)
        this->attempted_locations = (geometry_msgs::PoseStamped*)realloc(this->attempted_locations, attempted_locations_lengthT * sizeof(geometry_msgs::PoseStamped));
      offset += 3;
      attempted_locations_length = attempted_locations_lengthT;
      for( uint8_t i = 0; i < attempted_locations_length; i++){
      offset += this->st_attempted_locations.deserialize(inbuffer + offset);
        memcpy( &(this->attempted_locations[i]), &(this->st_attempted_locations), sizeof(geometry_msgs::PoseStamped));
      }
      uint8_t attempted_location_results_lengthT = *(inbuffer + offset++);
      if(attempted_location_results_lengthT > attempted_location_results_length)
        this->attempted_location_results = (manipulation_msgs::PlaceLocationResult*)realloc(this->attempted_location_results, attempted_location_results_lengthT * sizeof(manipulation_msgs::PlaceLocationResult));
      offset += 3;
      attempted_location_results_length = attempted_location_results_lengthT;
      for( uint8_t i = 0; i < attempted_location_results_length; i++){
      offset += this->st_attempted_location_results.deserialize(inbuffer + offset);
        memcpy( &(this->attempted_location_results[i]), &(this->st_attempted_location_results), sizeof(manipulation_msgs::PlaceLocationResult));
      }
     return offset;
    }

    const char * getType(){ return "moveit_msgs/PlaceResult"; };
    const char * getMD5(){ return "4f8f51c922fa536cee3ff0bcce217581"; };

  };

}
#endif