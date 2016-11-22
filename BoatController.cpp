#include "BoatController.h"
#include <math.h>

#define PI 3.14159265

float BoatController::calculateHeading(Vector2<float> currentPosition, Vector2<float> setpointPosition){
    float x = setpointPosition.x - currentPosition.x;
    float y = setpointPosition.y - currentPosition.y;

    return atan2 (y,x) * 180 / PI;
}

BoatController::BoatController(Boat *b){
    //Store the pointer to the boat object
    boat = b;

    running = false;
}

BoatController::~BoatController(){
    running = false;
    controlThread.join();
}
