#ifndef _SensorCalculations_H_
#define _SensorCalculations_H_
#define false 0
#define true 1
#include <string>
#include "PhysicalDefinitions.h"
//#define uint unsigned int

class Vector2;

class SensorCalculations
{
public:
  //Calcualtes currentSpeed.
  //Uses speed, accelerationsensor, Heading.
  void calculateSpeed(float speed);

  Vector2 getPosition();
  Vector2 getSpeed();
  float getHeading();

private:
  float heading = 0;
  Vector2 speed;
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
