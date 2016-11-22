#ifndef _SensorCalculations_H_
#define _SensorCalculations_H_
#define false 0
#define true 1
#include <string>
#include "Vector2/Vector2.hpp"

//kalman
//Prediction Speed,
//Lastspeed + time * Acceleration
//
//Predictment Position X,Y
//LastMesurement + (Speed * time) * lastspeed + 0.5 * acceleration * speed * (time* time) 
class SensorCalculations
{
public:
  //Calcualtes currentSpeed.
  //Uses speed, accelerationsensor, Heading.
  void predictSpeed(Vector2<float> speed, float time, float acceleration);

  void predictNextLocation(Vector2<float> setpointPosition, Vector2<float> speed, float timePeriod, float acceleration);
  
  Vector2<float> getSpeed();
  float getHeading();

private:
  Vector2<float> predictedLocation[10];
  Vector2<float> predictedSpeed[10];
  float heading = 0;
  Vector2<float> speed = 0;
  Vector2<float> currentPosition = 0;
};

#endif
