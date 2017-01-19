#include "SensorThreading.h"

#define TRANSLATION 16383

static SensorThreading sensorThreading;

SensorConvertion::SensorConvertion(){
    sensorThreading.startSensorGPSReading();
    sensorThreading.startSensorIMUReading();
}
SensorConvertion::~SensorConvertion(){
    sensorThreading.stopSensorGPSReading();
    sensorThreading.stopSensorIMUReading();
}

DataWXYZ SensorConvertion::longLatToXYZ(){
	if (sensorThreading.GPSindexR < sensorThreading.GPSindexW){
		Coordinate coord = sensorThreading.GPSCoordinates[sensorThreading.GPSindexR % 10];

		float cosLat = cos(coord.getLatitude() * M_PI / 180.0);
		float sinLat = sin(coord.getLatitude() * M_PI / 180.0);
		float cosLon = cos(coord.getLongitude() * M_PI / 180.0);
		float sinLon = sin(coord.getLongitude() * M_PI / 180.0);
		float C = 1.0 / sqrt(cosLat * cosLat + (1.0 - f) * (1.0 - f) * sinLat * sinLat);
		float S = (1.0 - f) * (1.0 - f) * C;
		float h = 0.0;
			
		DataWXYZ GPSposition = DataWXYZ(
			0,
			(rad * C + h) * cosLat * cosLon / TRANSLATION,
			(rad * C + h) * cosLat * sinLon / TRANSLATION,
			(rad * S + h) * sinLat / TRANSLATION
		);
		
		//printf("GPS: ");
		//GPSposition.printData();

		sensorThreading.GPSindexR++;

		return GPSposition;
	}
	
	printf("GPS Reading waiting!\r\n");
	return DataWXYZ(0, 0, 0, 0);
}

DataWXYZ SensorConvertion::convertIMUValues(DataWXYZ *location){
    if (sensorThreading.IMUindexR < sensorThreading.IMUindexW){
		DataWXYZ data = sensorThreading.IMUValues[sensorThreading.IMUindexR % 10];

		
		float w = data.getW() * 360;
		float x = (data.getX() + location->getX());
		float y = (data.getY() + location->getY());
		float z = (data.getZ() + location->getZ());

		lastCalculation = DataWXYZ(w,x,y,z);
		
		//printf("IMU: ");
		//lastCalculation.printData();

		sensorThreading.IMUindexR++;

		return lastCalculation;
	}

	printf("IMU Reading waiting!\r\n");
	return DataWXYZ(0, 0, 0, 0);
}
