#include "ros/ros.h"
#include "xhab/Temperature.h"
#include <math.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "mock_data");
  ros::NodeHandle n;

  ros::Publisher temperature_pub = n.advertise<xhab::Temperature>("data/fluid/temperature", 100);
  ros::Rate loop_rate(1);

  float x = 0;
  while (ros::ok())
  {
    xhab::Temperature temperature;
    temperature.value = sin(x);
    temperature_pub.publish(temperature);
    ros::spinOnce();
    loop_rate.sleep();
    
    // cycle x back to to 0 when x reaches ~PI
    if (x > 3)
    {
      x -= 0.1;
    }
    else
    {
      x += 0.1;
    }
  }

}
