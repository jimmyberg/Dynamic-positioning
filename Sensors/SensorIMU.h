#ifndef _SensorIMU_H_
#define _SensorIMU_H_

#include "../PhysicalDefinitions.h"
#include "DataWXYZ.h"
#include "ip_connection.h"
#include "brick_imu_v2.h"

#define HOST "localhost"
#define PORT 4223
#define IMUUID "5VGPJ3" // Change XYZ to the UID of your Bricklet


class SensorIMU{
public:
    // Create IP connection and device object
    void create();

    // Calls ipcon_disconnect internally and destroys IMU-object
    void destroy();

    // Connect to brickd, ipcon
    float connect();
    
    // !!Don't use device before ipcon is connected!!
    // Determine Quaternion
    float determineQuaternion();

    // Get current Quaternion
    DataWXYZ getQuaternion();
    
private:
    IPConnection ipcon;
    IMUV2 imu;  
    DataWXYZ dataWXYZ;
    int16_t w, x, y, z;
};
#endif
