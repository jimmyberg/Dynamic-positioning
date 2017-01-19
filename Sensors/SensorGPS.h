#ifndef _SensorGPS_H_
#define _SensorGPS_H_

#include "../PhysicalDefinitions.h"
#include "Coordinate.h"
#include "ip_connection.h"
#include "bricklet_gps.h"

#define HOST "localhost"
#define PORT 4223
#define GPSUID "svS" // Change XYZ to the UID of your Bricklet


class SensorGPS{
public:
    // Create IP connection and device object
    void create();
    // Calls ipcon_disconnect internally and destroys gps-object
    void destroy();

    // Connect to brickd, ipcon
    float connect();
    
    // !!Don't use device before ipcon is connected!!
    // determines current coordinates
    float determineCoordinates();

    // Get current coordinates
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
