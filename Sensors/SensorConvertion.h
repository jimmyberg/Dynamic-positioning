#ifndef _SensorConvertion_H_
#define _SensorConvertion_H_


#include "SensorThreading.h"
#include "Coordinate.h"
#include "DataWXYZ.h"

#include <thread>
#include <chrono>
#include <queue>
#include <math.h>

/**
 * @brief      Class for sensor convertion.
 */
class SensorConvertion
{
    public:
        /**
         * @brief      Constructor 
         */
        SensorConvertion();
        /**
         * @brief      Destroys the object.
         */
        ~SensorConvertion();

        //Long lat convertion
        
        /**
         * @brief      Long lat convertion
         *
         * @return     Long lat in xyz
         */
	    DataWXYZ longLatToXYZ();
        /**
         * @brief      Rotation convertion
         *
         * @param      location  The location
         *
         * @return     corrected location by using IMU data
         */
        DataWXYZ convertIMUValues(DataWXYZ *location);

    private:        
        // long lat convertion
        float rad = 6378137.0;
        float f = 1.0 / 298.257224;

        DataWXYZ lastCalculation;
        DataWXYZ lastGPSposition;
};

#endif
