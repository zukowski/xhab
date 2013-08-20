#ifndef _ROS_SERVICE_StartController_h
#define _ROS_SERVICE_StartController_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace dynamixel_controllers
{

static const char STARTCONTROLLER[] = "dynamixel_controllers/StartController";

  class StartControllerRequest : public ros::Msg
  {
    public:
      char * port_name;
      char * package_path;
      char * module_name;
      char * class_name;
      char * controller_name;
      uint8_t dependencies_length;
      char* st_dependencies;
      char* * dependencies;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t * length_port_name = (uint32_t *)(outbuffer + offset);
      *length_port_name = strlen( (const char*) this->port_name);
      offset += 4;
      memcpy(outbuffer + offset, this->port_name, *length_port_name);
      offset += *length_port_name;
      uint32_t * length_package_path = (uint32_t *)(outbuffer + offset);
      *length_package_path = strlen( (const char*) this->package_path);
      offset += 4;
      memcpy(outbuffer + offset, this->package_path, *length_package_path);
      offset += *length_package_path;
      uint32_t * length_module_name = (uint32_t *)(outbuffer + offset);
      *length_module_name = strlen( (const char*) this->module_name);
      offset += 4;
      memcpy(outbuffer + offset, this->module_name, *length_module_name);
      offset += *length_module_name;
      uint32_t * length_class_name = (uint32_t *)(outbuffer + offset);
      *length_class_name = strlen( (const char*) this->class_name);
      offset += 4;
      memcpy(outbuffer + offset, this->class_name, *length_class_name);
      offset += *length_class_name;
      uint32_t * length_controller_name = (uint32_t *)(outbuffer + offset);
      *length_controller_name = strlen( (const char*) this->controller_name);
      offset += 4;
      memcpy(outbuffer + offset, this->controller_name, *length_controller_name);
      offset += *length_controller_name;
      *(outbuffer + offset++) = dependencies_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < dependencies_length; i++){
      uint32_t * length_dependenciesi = (uint32_t *)(outbuffer + offset);
      *length_dependenciesi = strlen( (const char*) this->dependencies[i]);
      offset += 4;
      memcpy(outbuffer + offset, this->dependencies[i], *length_dependenciesi);
      offset += *length_dependenciesi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_port_name = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_port_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_port_name-1]=0;
      this->port_name = (char *)(inbuffer + offset-1);
      offset += length_port_name;
      uint32_t length_package_path = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_package_path; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_package_path-1]=0;
      this->package_path = (char *)(inbuffer + offset-1);
      offset += length_package_path;
      uint32_t length_module_name = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_module_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_module_name-1]=0;
      this->module_name = (char *)(inbuffer + offset-1);
      offset += length_module_name;
      uint32_t length_class_name = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_class_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_class_name-1]=0;
      this->class_name = (char *)(inbuffer + offset-1);
      offset += length_class_name;
      uint32_t length_controller_name = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_controller_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_controller_name-1]=0;
      this->controller_name = (char *)(inbuffer + offset-1);
      offset += length_controller_name;
      uint8_t dependencies_lengthT = *(inbuffer + offset++);
      if(dependencies_lengthT > dependencies_length)
        this->dependencies = (char**)realloc(this->dependencies, dependencies_lengthT * sizeof(char*));
      offset += 3;
      dependencies_length = dependencies_lengthT;
      for( uint8_t i = 0; i < dependencies_length; i++){
      uint32_t length_st_dependencies = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_dependencies; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_dependencies-1]=0;
      this->st_dependencies = (char *)(inbuffer + offset-1);
      offset += length_st_dependencies;
        memcpy( &(this->dependencies[i]), &(this->st_dependencies), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return STARTCONTROLLER; };
    const char * getMD5(){ return "7785d708c83a180befd2fe3450dd9d41"; };

  };

  class StartControllerResponse : public ros::Msg
  {
    public:
      bool success;
      char * reason;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->success);
      uint32_t * length_reason = (uint32_t *)(outbuffer + offset);
      *length_reason = strlen( (const char*) this->reason);
      offset += 4;
      memcpy(outbuffer + offset, this->reason, *length_reason);
      offset += *length_reason;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
      uint32_t length_reason = *(uint32_t *)(inbuffer + offset);
      offset += 4;
      for(unsigned int k= offset; k< offset+length_reason; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_reason-1]=0;
      this->reason = (char *)(inbuffer + offset-1);
      offset += length_reason;
     return offset;
    }

    const char * getType(){ return STARTCONTROLLER; };
    const char * getMD5(){ return "a4d50a34d34f18de48e2436ff1472594"; };

  };

  class StartController {
    public:
    typedef StartControllerRequest Request;
    typedef StartControllerResponse Response;
  };

}
#endif
