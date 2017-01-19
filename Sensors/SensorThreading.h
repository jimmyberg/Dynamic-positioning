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

/**
 * @brief      Class for sensor threading.
 * @details    From here thread can be started to accuire data.
 */
class SensorThreading
{
public:
	/**
	 * @brief      Starts sensor gps reading.
	 */
	void startSensorGPSReading();
	/**
	 * @brief      Stops sensor gps reading.
	 */
	void stopSensorGPSReading();
	/**
	 * @brief      Determines if gps running.
	 *
	 * @return     True if gps running, False otherwise.
	 */
	bool isGPSRunning() { return GPSRunning; };

	/**
	 * @brief      Starts sensor imu reading.
	 */
	void startSensorIMUReading();
	/**
	 * @brief      Stops sensor imu reading.
	 */
	void stopSensorIMUReading();
	/**
	 * @brief      Determines if imu running.
	 *
	 * @return     True if imu running, False otherwise.
	 */
	bool isIMURunning() { return IMURunning; };
	/**
	 * @brief      Gets the imu from queue.
	 */
	void getIMUFromQueue();

	/**
	 * @brief      Starts sensor acceleration reading.
	 */
	void startSensorAccelerationReading();
	/**
	 * @brief      Stops sensor acceleration reading.
	 */
	void stopSensorAccelerationReading();
	/**
	 * @brief      Determines if acceleration running.
	 *
	 * @return     True if acceleration running, False otherwise.
	 */
	bool isAccelerationRunning() { return AccelerationRunning; };
	/**
	 * @brief      Gets the acceleration from queue.
	 */
	void getAccelerationFromQueue();

	/* ------ Circular buffers ------*/
	Coordinate GPSCoordinates[10] {Coordinate(0, 0, 'A', 'A')};
	int GPSindexR = 0;
	int GPSindexW = 0;

	DataWXYZ IMUValues[10] {DataWXYZ(0,0,0,0)};
	int IMUindexR = 0;
	int IMUindexW = 0;

	std::queue<DataWXYZ> AccelerationPositions;
	/**
	 * @brief      Constructor
	 */
	SensorThreading();
	/**
	 * @brief      Destroys the object.
	 */
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
