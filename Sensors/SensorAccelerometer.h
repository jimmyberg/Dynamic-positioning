#ifndef _SensorAccelerometer_H_
#define _SensorAccelerometer_H_

#include "../PhysicalDefinitions.h"
#include "ip_connection.h"
#include "bricklet_accelerometer.h"

#define HOST "localhost"
#define PORT 4223
#define ACCELEROUID "5VGPJ3" // Change XYZ to the UID of your Bricklet


class SensorAccelerometer{
public:
  // Create IP connection and device object
  void create();

  // Calls ipcon_disconnect internally and destroys gps-object
  void destroy();

  // Connect to brickd, ipcon
  float connect();

  // !!Don't use device before ipcon is connected!!
  // determines // current acceleration (unit is g/1000)
  float determineAcceleration();

  // prints data
  void printXYZ();

  // Get current Acceleration
    DataWXYZ getAcceleration();
    
private:
  IPConnection ipcon;
  DataWXYZ dataWXYZ;
  Accelerometer a;
  int16_t x, y, z;
};

#endif
