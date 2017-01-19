#ifndef _SensorConvertion_H_
#define _SensorConvertion_H_


#include "SensorThreading.h"
#include "Coordinate.h"
#include "DataWXYZ.h"

#include <thread>
#include <chrono>
#include <queue>
#include <math.h>

#define TRANSLATION 16383
class SensorConvertion
{
    public:
        SensorConvertion();
        ~SensorConvertion();

        //Long lat convertion
	    DataWXYZ longLatToXYZ();
        //Rotation convertion
        DataWXYZ convertIMUValues(DataWXYZ *location);

    private:        
        // long lat convertion
        float rad = 6378137.0;
        float f = 1.0 / 298.257224;

        DataWXYZ lastCalculation;
        DataWXYZ lastGPSposition;
};

#endif