#include "SensorGPS.h"

void SensorGPS::create(){    
    ipcon_create(&ipcon);
    gps_create(&gps, GPSUID, &ipcon);
}
float SensorGPS::connect(){
    if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
        fprintf(stderr, "Could not connect\n");
        return 1;
    }
    return 0;
}

void SensorGPS::destroy(){
    gps_destroy(&gps);
    ipcon_destroy(&ipcon);
}

float SensorGPS::determineCoordinates(){
    if(gps_get_coordinates(&gps, &latitude, &ns, &longitude, &ew, &pdop, &hdop, &vdop,
                           &epe) < 0) {
        fprintf(stderr, "Could not get coordinates, probably timeout\n");
        return 1;
    }
    coordinate = Coordinate(latitude, longitude, ns, ew);
    return 0;
}
Coordinate SensorGPS::getCoordinate(){
    return coordinate;
}
