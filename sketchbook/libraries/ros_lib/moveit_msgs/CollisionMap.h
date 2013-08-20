#ifndef _ROS_moveit_msgs_CollisionMap_h
#define _ROS_moveit_msgs_CollisionMap_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "moveit_msgs/OrientedBoundingBox.h"

namespace moveit_msgs
{

  class CollisionMap : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t boxes_length;
      moveit_msgs::OrientedBoundingBox st_boxes;
      moveit_msgs::OrientedBoundingBox * boxes;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = boxes_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < boxes_length; i++){
      offset += this->boxes[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t boxes_lengthT = *(inbuffer + offset++);
      if(boxes_lengthT > boxes_length)
        this->boxes = (moveit_msgs::OrientedBoundingBox*)realloc(this->boxes, boxes_lengthT * sizeof(moveit_msgs::OrientedBoundingBox));
      offset += 3;
      boxes_length = boxes_lengthT;
      for( uint8_t i = 0; i < boxes_length; i++){
      offset += this->st_boxes.deserialize(inbuffer + offset);
        memcpy( &(this->boxes[i]), &(this->st_boxes), sizeof(moveit_msgs::OrientedBoundingBox));
      }
     return offset;
    }

    const char * getType(){ return "moveit_msgs/CollisionMap"; };
    const char * getMD5(){ return "ba8b828774cfbf26889eb3454fc94005"; };

  };

}
#endif