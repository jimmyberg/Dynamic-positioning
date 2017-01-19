#include "DataWXYZ.h"

DataWXYZ::DataWXYZ(float wVal, float xVal, float yVal, float zVal){
    w = wVal;
    x = xVal;
    y = yVal;
    z = zVal;
}
DataWXYZ::DataWXYZ(){}
DataWXYZ::~DataWXYZ(){}

float DataWXYZ::getW(){return w;}

float DataWXYZ::getX(){return x;}

float DataWXYZ::getY(){return y;}

float DataWXYZ::getZ() {return z;}

void DataWXYZ::printData(){
    printf("w: %.2f, x: %.2f, y: %.2f, z: %.2f\n",
           w, x, y, z);
}