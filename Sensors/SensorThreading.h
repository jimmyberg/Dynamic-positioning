#ifndef _SensorThreading_H_
#define _SensorThreading_H_

#include "../Vector2/Vector2.hpp"
#include "../PhysicalDefinitions.h"

#include "Coordinate.h"
#include "DataWXYZ.h"
#include "SensorGPS.h"
#include "SensorIMU.h"
#include "SensorAccelerometer.h"

#include <thread>
#include <chrono>
#include <queue>
#include <math.h>

class SensorThreading
{
public:
	//Start stop control thread
	//GPS
	void startSensorGPSReading();
	void stopSensorGPSReading();

	bool isGPSRunning() { return GPSRunning; };

	//IMU
	void startSensorIMUReading();
	void stopSensorIMUReading();

	bool isIMURunning() { return IMURunning; };
	void getIMUFromQueue();

	//Acceleration
	void startSensorAccelerationReading();
	void stopSensorAccelerationReading();

	bool isAccelerationRunning() { return AccelerationRunning; };
	void getAccelerationFromQueue();

	/* ------ Circular buffers ------*/
	Coordinate GPSCoordinates[10] {Coordinate(0, 0, 'A', 'A')};
	int GPSindexR = 0;
	int GPSindexW = 0;

	DataWXYZ IMUValues[10] {DataWXYZ(0,0,0,0)};
	int IMUindexR = 0;
	int IMUindexW = 0;

	//std::queue<Coordinate> GPSCoordinates;
	//std::queue<DataWXYZ> IMUPositions;
	std::queue<DataWXYZ> AccelerationPositions;

	SensorThreading();
	~SensorThreading();

private:	
	std::chrono::duration<float> periodTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> lastTime, currentTime;

	// GPS
	std::thread SensorGPSReadingThread;
	void SensorGPSReadingFunction();
	bool GPSRunning = false;


	// IMU
	std::thread SensorIMUReadingThread;
	void SensorIMUReadingFunction();
	bool IMURunning = false;

	// IMU
	std::thread SensorAccelerationReadingThread;
	void SensorAccelerationReadingFunction();
	bool AccelerationRunning = false;
};

#endif
