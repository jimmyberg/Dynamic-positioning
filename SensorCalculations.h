#ifndef _SensorCalculations_H_
#define _SensorCalculations_H_
#define false 0
#define true 1
#include <string>
#include "Vector2/Vector2.hpp"

class SensorCalculations
{
public:
  //Calcualtes currentSpeed.
  //Uses speed, accelerationsensor, Heading.
  void calculateSpeed(float speed);

  Vector2<float> getPosition();
  Vector2<float> getSpeed();
  float getHeading();

private:
  float heading = 0;
  Vector2<float >speed;
};

class gps
{
public:
  void Sensor(std::string type);
  void setNewValue(int value);

private:
  unsigned int newValue = 0, previousValue = 0;
};

class Accelerometer
{
  int getSensorValue();
};

/*class Sensor
{
public:
    std::string type() const { return _type; } 
    void bar(const std::string& bar) { _type = bar; } 
private:
    std::string _type;
};*/
#endif
