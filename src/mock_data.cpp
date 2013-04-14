#include "ros/ros.h"
#include "xhab/Temperature.h"
#include <math.h>

#define PI 3.14

int main(int argc, char **argv)
{
  ros::init(argc, argv, "mock_data");
  ros::NodeHandle n;

  ros::Publisher temperature_pub = n.advertise<xhab::Temperature>("data/fluid/temperature", 100);
  ros::Rate loop_rate(10);

  float x = 0;
  int state = 1; // x is increasing
  while (ros::ok())
  {
    xhab::Temperature temperature;
    temperature.value = sin(x);
    ROS_INFO("%f", temperature.value);
    temperature_pub.publish(temperature);
    ros::spinOnce();
    loop_rate.sleep();
    
    // cycle x back to to 0 when x reaches ~PI*2
    if (x > PI)
    {
      state = 0;
    }
    else if (x < -PI)
    {
      state = 1;
    }
    
    if (state == 0)
    {
      x += 0.1;
    }
    else
    {
      x -= 0.1;
    }
  }

}
