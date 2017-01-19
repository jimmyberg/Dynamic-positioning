#include "Coordinate.h"

Coordinate::Coordinate(uint32_t iLatitude, uint32_t iLongitude, char cNs, char cEw){
    longitude = iLongitude;
    latitude = iLatitude;
    ns = cNs;
    ew = cEw;
}
Coordinate::~Coordinate(){}
Coordinate::Coordinate(){}
float Coordinate::getLongitude(){
    return longitude;
}
float Coordinate::getLatitude(){
    return latitude;
}
char Coordinate::getEW(){
    return ew;
}
char Coordinate::getNS(){
    return ns;
}
void Coordinate::printLongLat(){
    printf("Latitude: %f° %c\n", latitude/1000000.0, ns);
    printf("Longitude: %f° %c\n", longitude/1000000.0, ew);
}