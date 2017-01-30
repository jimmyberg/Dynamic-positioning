#include "BoatController.h"
#include <math.h>
#include "ExtraFunctions.h"
#include "Vector2/Vector2.hpp"

#define PI 3.14159265

/*
float BoatController::calculateHeading(Vector2<float> currentPosition, Vector2<float> setpointPosition){
    float x = boat->setpointPosition.x - boat->currentPosition.x;
    float y = boat->setpointPosition.y - boat->currentPosition.y;

    return atan2 (y,x);
}
*/

BoatController::BoatController(Boat *b) : boat(b)
{
    //Create the PIDController instances
    //NEED TO ADD A WAY TO SET THE CONSTANTS
    xController = PIDController(0.3, 0.0, 1.8, 0.0, 0.0, 1.0);
    yController = PIDController(0.3, 0.0, 1.8, 0.0, 0.0, 1.0);
    hController = PIDController(2.0, 0.0, 5.0, 0.0, 0.0, (1.0 / M_PI));
}

BoatController::~BoatController()
{
    //stopControl();
}

void BoatController::startControl()
{
    running = true;
    lastTime = std::chrono::high_resolution_clock::now();
    controlThread = std::thread(&BoatController::controlFunction, this);
}

void BoatController::stopControl()
{
    running = false;
    controlThread.join();
}

void BoatController::controlFunction()
{
    while (running)
    {
        currentTime = std::chrono::high_resolution_clock::now();
        periodTime = currentTime - lastTime;
        lastTime = currentTime;

        //Calculate the current error in the position data
        float errorX = boat->setpointPosition.x - boat->currentPosition.x;
        float errorY = boat->setpointPosition.y - boat->currentPosition.y;
        float errorH = boat->setpointHeading - boat->currentHeading;

        xSignal = xController.calculateOutput(errorX, periodTime);
        ySignal = yController.calculateOutput(errorY, periodTime);
        hSignal = hController.calculateOutput(errorH, periodTime);

        Vector2<float> positionVector(xSignal, ySignal);
        positionVector.rotate(-M_PI_2);

        Vector2<float> heading1Vector = BoatController::getHeadingVector(hSignal, M_PI_2, M_PI + M_PI_2);
        Vector2<float> heading2Vector = BoatController::getHeadingVector(hSignal, M_PI + M_PI_2, M_PI_2);
        ;

        Vector2<float> thruster1Vector = positionVector + heading1Vector;
        Vector2<float> thruster2Vector = positionVector + heading2Vector;

        if (thruster1Vector.absolute() > 0.01)
        {
            boat->azimuthThruster[0].throttle = limit(thruster1Vector.absolute(), (float)-1.0, (float)1.0);
            boat->azimuthThruster[0].rotation = atan2(thruster1Vector.y, thruster1Vector.x);
        }
        else
        {
            boat->azimuthThruster[0].throttle = 0.0;
            boat->azimuthThruster[0].rotation = 0.0;
        }

        if (thruster2Vector.absolute() > 0.01)
        {
            boat->azimuthThruster[1].throttle = limit(thruster2Vector.absolute(), (float)-1.0, (float)1.0);
            boat->azimuthThruster[1].rotation = atan2(thruster2Vector.y, thruster2Vector.x);
        }
        else
        {
            boat->azimuthThruster[1].throttle = 0.0;
            boat->azimuthThruster[1].rotation = 0.0;
        }

        //Pause this thread
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void BoatController::singleStep()
{
    periodTime = std::chrono::duration<float>(std::chrono::milliseconds(10));

    //Calculate the current error in the position data
    float errorX = boat->setpointPosition.x - boat->currentPosition.x;
    float errorY = boat->setpointPosition.y - boat->currentPosition.y;
    float errorH = boat->setpointHeading - boat->currentHeading;

    xSignal = xController.calculateOutput(errorX, periodTime);
    ySignal = yController.calculateOutput(errorY, periodTime);
    hSignal = hController.calculateOutput(errorH, periodTime);

    Vector2<float> positionVector(xSignal, ySignal);
    positionVector.rotate(-M_PI_2);

    Vector2<float> heading1Vector = BoatController::getHeadingVector(hSignal, M_PI_2, M_PI + M_PI_2);
    Vector2<float> heading2Vector = BoatController::getHeadingVector(hSignal, M_PI + M_PI_2, M_PI_2);
    ;

    Vector2<float> thruster1Vector = positionVector + heading1Vector;
    Vector2<float> thruster2Vector = positionVector + heading2Vector;

    boat->azimuthThruster[0].throttle = limit(thruster1Vector.absolute(), (float)-1.0, (float)1.0);
    boat->azimuthThruster[0].rotation = atan2(thruster1Vector.y, thruster1Vector.x);

    boat->azimuthThruster[1].throttle = limit(thruster2Vector.absolute(), (float)-1.0, (float)1.0);
    boat->azimuthThruster[1].rotation = atan2(thruster2Vector.y, thruster2Vector.x);
}

Vector2<float> BoatController::getHeadingVector(float hSignal, float left, float right)
{
    Vector2<float> out = {0.0, 0.0};

    float throttle = (fabs(hSignal) > 0.01) ? fabs(hSignal) : 0.0;
    float angle = BoatController::thresholding(hSignal, 0.01, left, right);

    out.x = throttle * cos(angle);
    out.y = throttle * sin(angle);

    return out;
}

float BoatController::thresholding(float error, float threshold, float left, float right)
{
    if (error > threshold)
    {
        return left;
    }
    else if (error < -threshold)
    {
        return right;
    }
    else
    {
        return 0.0;
    }
}
