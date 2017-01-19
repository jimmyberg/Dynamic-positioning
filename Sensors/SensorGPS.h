#ifndef _SensorGPS_H_
#define _SensorGPS_H_

#include "../PhysicalDefinitions.h"
#include "Coordinate.h"
#include "ip_connection.h"
#include "bricklet_gps.h"

/**
 * Defines hostname
 */
#define HOST "localhost"
/**
 * Defines used port
 */
#define PORT 4223
/**
 * Define GPSUID for current GPS sensor
 */
#define GPSUID "svS" // Change XYZ to the UID of your Bricklet

/**
 * @brief      Class for sensor gps.
 */
class SensorGPS{
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
     * @return     0 for succes
     */
    float connect();
    
    /**
     * @brief      !!Don't use device before ipcon is connected!! determines
     *             current coordinates
     *
     * @return     0 for succes
     */
    float determineCoordinates();

    /**
     * @brief      Gets the coordinate.
     *
     * @return     The coordinate.
     */
    Coordinate getCoordinate();
    
private:
  IPConnection ipcon;
  Coordinate coordinate;
  GPS gps;
  uint32_t latitude, longitude;
  uint16_t pdop, hdop, vdop, epe;
  char ns, ew;
};

#endif
