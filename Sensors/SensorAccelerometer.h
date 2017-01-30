#ifndef _SensorAccelerometer_H_
#define _SensorAccelerometer_H_

#include "../PhysicalDefinitions.h"
#include "ip_connection.h"
#include "bricklet_accelerometer.h"
#include "DataWXYZ.h"

/**
 * define host name
 */
#define HOST "localhost"
/**
 * define used port number
 */
#define PORT 4223
/**
 * Change XYZ to the UID of your Bricklet
 */
#define ACCELEROUID "5VGPJ3"

/**
 * @brief      Class for sensor accelerometer.
 */
class SensorAccelerometer{
public:
  /**
   * @brief      Create IP connection and device object
   */
  void create();

  /**
   * @brief      Calls ipcon_disconnect internally and destroys gps-object
   */
  void destroy();

  /**
   * @brief      Connect to brickd, ipcon
   *
   * @return     0 for success
   */
  float connect();

  /**
   * @brief      !!Don't use device before ipcon is connected!! determines //
   *             current acceleration (unit is g/1000)
   *
   * @return     0 for succes
   */
  float determineAcceleration();

  /**
   * @brief      prints data
   */
  void printXYZ();  
  	/**
  	 * @brief      Gets the acceleration.
  	 *
  	 * @return     The acceleration.
  	 */
    DataWXYZ getAcceleration();
    
private:
  IPConnection ipcon;
  DataWXYZ dataWXYZ;
  Accelerometer a;
  int16_t x, y, z;
};

#endif
