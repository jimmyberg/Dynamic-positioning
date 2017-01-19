#ifndef _SensorIMU_H_
#define _SensorIMU_H_

#include "../PhysicalDefinitions.h"
#include "DataWXYZ.h"
#include "ip_connection.h"
#include "brick_imu_v2.h"

/**
 * Defines hostname
 */
#define HOST "localhost"
/**
 * Defines used port number
 */
#define PORT 4223
/**
 * Defines IMUUID for current sensor
 */
#define IMUUID "5VGPJ3" // Change XYZ to the UID of your Bricklet

/**
 * @brief      Class for sensor imu.
 */
class SensorIMU{
public:
    /**
     * @brief      Create IP connection and device object
     */
    void create();

    /**
     * @brief      Calls ipcon_disconnect internally and destroys IMU-object
     */
    void destroy();

    /**
     * @brief      Connect to brickd, ipcon
     *
     * @return     0 for success
     */
    float connect();
    
    /**
     * @brief      Don't use device before ipcon is connected!! Determine
     *             Quaternion
     *
     * @return     0 for succes
     */
    float determineQuaternion();

    /**
     * @brief      Gets the quaternion.
     *
     * @return     The quaternion.
     */
    DataWXYZ getQuaternion();
    
private:
    IPConnection ipcon;
    IMUV2 imu;  
    DataWXYZ dataWXYZ;
    int16_t w, x, y, z;
};
#endif
