#include "SensorIMU.h"

void SensorIMU::create(){
    ipcon_create(&ipcon);
    imu_v2_create(&imu, IMUUID, &ipcon);
}

void SensorIMU::destroy(){
    imu_v2_destroy(&imu);
	ipcon_destroy(&ipcon);
}

float SensorIMU::connect(){
    if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
    return 0;
}

float SensorIMU::determineQuaternion(){    
	if(imu_v2_get_quaternion(&imu, &w, &x, &y, &z) < 0) {
        fprintf(stderr, "Could not get quaternion, probably timeout\n");
        return 1;
    }
    dataWXYZ = DataWXYZ(w / 16383.0, x / 16383.0, y / 16383.0, z / 16383.0);
    return 0;
}

DataWXYZ SensorIMU::getQuaternion(){
    return dataWXYZ;}