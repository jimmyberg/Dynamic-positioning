#include "SensorThreading.h"

SensorThreading::SensorThreading(){}
SensorThreading::~SensorThreading(){}

//GPS module
void SensorThreading::startSensorGPSReading(){
	if (!GPSRunning){
		GPSRunning = true;
		lastTime = std::chrono::high_resolution_clock::now();
		SensorGPSReadingThread = std::thread(&SensorThreading::SensorGPSReadingFunction, this);
	}
}

void SensorThreading::stopSensorGPSReading(){
	if (GPSRunning){
		GPSRunning = false;
		SensorGPSReadingThread.join();
	}
}

void SensorThreading::SensorGPSReadingFunction(){
	SensorGPS sensorGPS;
	sensorGPS.create();
	if (sensorGPS.connect() == 1){
		stopSensorGPSReading();
	}

	while (GPSRunning){
		if (GPSindexW < GPSindexR + 2  ){
			sensorGPS.determineCoordinates();

			GPSCoordinates[GPSindexW % 10] = sensorGPS.getCoordinate();
			//GPSCoordinates[GPSindexW % 10].printLongLat();
			GPSindexW++;
		}
	}
	sensorGPS.destroy();
}

//IMU Module
void SensorThreading::startSensorIMUReading(){
	if (!IMURunning){
		IMURunning = true;
		lastTime = std::chrono::high_resolution_clock::now();
		SensorIMUReadingThread = std::thread(&SensorThreading::SensorIMUReadingFunction, this);
	}
}

void SensorThreading::stopSensorIMUReading(){
	if (IMURunning){
		IMURunning = false;
		SensorIMUReadingThread.join();
	}
}

void SensorThreading::SensorIMUReadingFunction(){
	SensorIMU sensorIMU;
	sensorIMU.create();
	if (sensorIMU.connect() == 1){
		stopSensorIMUReading();
	}

	while (IMURunning){
		if (IMUindexW < IMUindexR + 2  ){

			sensorIMU.determineQuaternion();
			IMUValues[IMUindexW % 10] = sensorIMU.getQuaternion();
			//IMUValues[IMUindexW % 10].printData();
			IMUindexW++;
		}
	}
	sensorIMU.destroy();
}

/*//Acceleration Module
void SensorThreading::startSensorAccelerationReading(){
	if (!AccelerationRunning){
		AccelerationRunning = true;
		lastTime = std::chrono::high_resolution_clock::now();
		SensorAccelerationReadingThread = std::thread(&SensorThreading::SensorAccelerationReadingFunction, this);
	}
}

void SensorThreading::stopSensorAccelerationReading(){
	if (AccelerationRunning){
		AccelerationRunning = false;
		SensorAccelerationReadingThread.join();
	}
}

void SensorThreading::SensorAccelerationReadingFunction(){
	SensorAccelerometer sensorAccelerometer;
	sensorAccelerometer.create();
	if (sensorAccelerometer.connect() == 1){
		stopSensorAccelerationReading();
	}

	while (AccelerationRunning){
		if (AccelerationPositions.size() < 10){
			sensorAccelerometer.determineAcceleration();
			AccelerationPositions.push(sensorAccelerometer.getAcceleration());
		}
	}
	sensorAccelerometer.destroy();
}

void SensorThreading::getAccelerationFromQueue(){
	if (!AccelerationPositions.empty()){
		printf("Acceleration:");
		AccelerationPositions.front().printData();
		AccelerationPositions.pop();	
	}
}*/
