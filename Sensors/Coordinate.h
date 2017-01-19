#ifndef _Coordinate_H_
#define _Coordinate_H_

#include <iostream>

class Coordinate{
    public:
        //constructors
        Coordinate(uint32_t iLatitude, uint32_t iLongitude, char cNs, char cEw);
        Coordinate();
        ~Coordinate();
        
        //functions
        // Get longitude value from class;
        float getLongitude();

        // Gets latitude value from class;
        float getLatitude();

        // gets East or West value from class
        char getEW();

        // gets North or South value from class
        char getNS();

        // Prints the longitude and Latitude;
        void printLongLat();

    private:
        //variables
        uint32_t latitude, longitude;
        char ns, ew;
};
#endif