#include <iostream>
#include "Sensors/SensorConvertion.h"
#include "Sensors/DataWXYZ.h"
#include <chrono>
#include <thread>

using namespace std;

int main(void){
    SensorConvertion sensor;

    DataWXYZ position;
    DataWXYZ fixedPosition;

    while(1){
        position = sensor.longLatToXYZ();
        fixedPosition = sensor.convertIMUValues(&position);
        fixedPosition.printData();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
