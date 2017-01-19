#include "SensorAccelerometer.h"

void SensorAccelerometer::create(){    
    ipcon_create(&ipcon);
    accelerometer_create(&a, ACCELEROUID, &ipcon);
}
float SensorAccelerometer::connect(){
    if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
        fprintf(stderr, "Could not connect\n");
        return 1;
    }
    return 0;
}

void SensorAccelerometer::destroy(){
    accelerometer_destroy(&a);
    ipcon_destroy(&ipcon);
} 

float SensorAccelerometer::determineAcceleration(){
    if(accelerometer_get_acceleration(&a, &x, &y, &z) < 0) {
		fprintf(stderr, "Could not get acceleration, probably timeout\n");
		return 1;
	}
    dataWXYZ = DataWXYZ(0, x / 16383.0, y / 16383.0, z / 16383.0);
    return 0;
}
void SensorAccelerometer::printXYZ(){
    printf("Acceleration[X]: %f g\n", x/1000.0);
	printf("Acceleration[Y]: %f g\n", y/1000.0);
	printf("Acceleration[Z]: %f g\n", z/1000.0);
}
DataWXYZ SensorAccelerometer::getAcceleration(){
    return dataWXYZ;
}
