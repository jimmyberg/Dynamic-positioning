#ifndef _Coordinate_H_
#define _Coordinate_H_

#include <iostream>

/**
 * @brief      Class for coordinate.
 */
class Coordinate{
    public:
        /**
         * @brief      Constructor to assign this class with data
         *
         * @param[in]  iLatitude   The latitude
         * @param[in]  iLongitude  The longitude
         * @param[in]  cNs         North south indicator. It is either n or s
         * @param[in]  cEw         East west indicator. It is either e or w
         */
        Coordinate(uint32_t iLatitude, uint32_t iLongitude, char cNs, char cEw);
        /**
         * @brief      Empty constructor
         */
        Coordinate();
        /**
         * @brief      Destroys the object.
         */
        ~Coordinate();
        /**
         * @brief      Gets the longitude.
         *
         * @return     The longitude.
         */
        float getLongitude();

        /**
         * @brief      Gets the latitude.
         *
         * @return     The latitude.
         */
        float getLatitude();

        /**
         * @brief      Gets the east west indicator.
         *
         * @return     The east west indicator.
         */
        char getEW();

        /**
         * @brief      Gets the noth south indicator.
         *
         * @return     The noth south indicator.
         */
        char getNS();

        /**
         * @brief      print function
         */
        void printLongLat();

    private:
        //variables
        uint32_t latitude, longitude;
        char ns, ew;
};
#endif
