#include "BoatController.h"
#include <math.h>
#include "ExtraFunctions.h"

#define PI 3.14159265

float BoatController::calculateHeading(Vector2<float> currentPosition, Vector2<float> setpointPosition){
    float x = boat->setpointPosition.x - boat->currentPosition.x;
    float y = boat->setpointPosition.y - boat->currentPosition.y;

    return atan2 (y,x);
}

BoatController::BoatController(Boat *b){
    //Store the pointer to the boat object
    boat = b;

    //Create the PIDController instances
    //NEED TO ADD A WAY TO SET THE CONSTANTS
    xController = new PIDController(1.0, 0.0, 0.5, 0.0, 0.0, 0.01);
    yController = new PIDController(1.0, 0.0, 0.5, 0.0, 0.0, 0.01);
    hController = new PIDController(2.0, 0.0, 0.5, 0.0, 0.0, 1.0);
}

BoatController::~BoatController(){
    //stopControl();
}

void BoatController::startControl(){
    running = true;
    lastTime = std::chrono::high_resolution_clock::now();
    controlThread = std::thread(&BoatController::controlFunction, this);
}

void BoatController::stopControl(){
    running = false;
    controlThread.join();
}

void BoatController::controlFunction(){
    while (running){
        currentTime = std::chrono::high_resolution_clock::now();
        periodTime = currentTime - lastTime;
        lastTime = currentTime;

        //Calculate the current error in the position data
        float errorX = boat->currentPosition.x - boat->setpointPosition.x;
        float errorY = boat->currentPosition.y - boat->setpointPosition.y;
        float errorH = boat->currentHeading - boat->setpointHeading;

        float xSignal = xController->calculateOutput(errorX, periodTime);
        float ySignal = yController->calculateOutput(errorY, periodTime);
        float hSignal = hController->calculateOutput(errorH, periodTime);

        float anglePosition = atan2(ySignal, xSignal);
        float throttlePosition = sqrt(pow(xSignal, 2) + pow(ySignal, 2));

        float throttleHeading = hSignal;

        float angle1Heading = (hSignal > 0.0) ? M_PI_2 : (M_PI + M_PI_2);
        float angle2Heading = (hSignal > 0.0) ? (M_PI + M_PI_2) : M_PI_2;

        boat->azimuthThruster[0].throttle = limit(throttlePosition + throttleHeading, (float)-1.0, (float)1.0);        
        boat->azimuthThruster[0].rotation = (anglePosition + angle1Heading) / 2.0;
        boat->azimuthThruster[1].throttle = limit(throttlePosition + throttleHeading, (float)-1.0, (float)1.0);
        boat->azimuthThruster[1].rotation = (anglePosition + angle2Heading) / 2.0;

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void BoatController::singleStep(){
    periodTime = std::chrono::duration<float>(std::chrono::milliseconds(10));

    //Calculate the current error in the position data
    float errorX = boat->setpointPosition.x - boat->currentPosition.x;
    float errorY = boat->setpointPosition.y - boat->currentPosition.y;
    float errorH = boat->setpointHeading - boat->currentHeading;

    float xSignal = xController->calculateOutput(errorX, periodTime);
    float ySignal = yController->calculateOutput(errorY, periodTime);
    float hSignal = hController->calculateOutput(errorH, periodTime);

    float anglePosition = - M_PI_2 + atan2(ySignal, xSignal) - boat->currentHeading;
    float throttlePosition = sqrt(pow(xSignal, 2) + pow(ySignal, 2));

    float throttleHeading = hSignal;

    float angle1Heading = 0.0;
    float angle2Heading = 0.0;

    if(hSignal > 0.01){
        angle1Heading = M_PI_2;
        angle2Heading = M_PI_2 + M_PI;
    }else if(hSignal < -0.01){
        angle1Heading = M_PI_2 + M_PI;
        angle2Heading = M_PI_2;
    }

    boat->azimuthThruster[0].throttle = limit(throttlePosition + throttleHeading, (float)-1.0, (float)1.0);        
    boat->azimuthThruster[0].rotation = (anglePosition + angle1Heading);
    boat->azimuthThruster[1].throttle = limit(throttlePosition + throttleHeading, (float)-1.0, (float)1.0);
    boat->azimuthThruster[1].rotation = (anglePosition + angle2Heading);    
}
