#ifndef _DataWXYZ_H_
#define _DataWXYZ_H_

#include <iostream>

class DataWXYZ{
    public:
        //constructors
        DataWXYZ(float wVal, float xVal, float yVal, float zVal);
        DataWXYZ();
        ~DataWXYZ();
        
        //functions


        // gets W
        float getW();

        // gets X
        float getX();

        // gets Y
        float getY();

        // gets Z
        float getZ();

        void printData();

    private:
        //variables
        float w, x, y, z;
};
#endif