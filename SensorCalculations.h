#ifndef _SensorCalculations_H_
#define _SensorCalculations_H_
#define false 0
#define true 1
#include <string>
//#define uint unsigned int

class SensorCalculations
{
public:
  //Calcualtes currentSpeed.
  //Uses speed, accelerationsensor, Heading.
  calculateSpeed(float speed);
  //calculates the heading,
  //Uses currentSpeed, currentPosition  and setpointPosition.
  calculateHeading(Vector2 currentPosition, Vector2 setpointPosition);

  Vector2 getPosition();
  Vector2 getSpeed();
  float getHeading();

private:
  float heading = 0;
  Vector2 speed = 0;

}

class gps
{
public:
  Sensor(string type);
  setNewValue(int value);

private:
  uint newValue = 0, previousValue = 0;
};

class Accelerometer
{
  int getSensorValue();
}

/*class Sensor
{
public:
    std::string type() const { return _type; } 
    void bar(const std::string& bar) { _type = bar; } 
private:
    std::string _type;
};*/
#endif
