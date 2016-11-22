//This file contains the code of the PIDController class
#include "PIDController.h"
#include <chrono>


PIDController::PIDController():
PIDController(
    0.0,
    0.0,
    0.0,
    0.0,
    0.0){}

PIDController::PIDController(float p, float i, float d, float prev, float integral):
PIDController(p, i, d, prev, integral,
    std::chrono::duration<float>(std::chrono::duration_values<float>::zero())){}

PIDController::PIDController(float p, float i, float d, float prev, float integral, std::chrono::duration<float> sampleTime):
    Kp(p),
    Ki(i),
    Kd(d),
    dT(sampleTime),
    ePrevious(prev),
    eIntegral(integral){}

PIDController::~PIDController(){}

float PIDController::calculateOutput(float eInput){
    //Integrating the error
    eIntegral += eInput * dT.count();
    //Derivative of error
    float eDeriv = (ePrevious - eInput) / dT.count();
    //Store the current error as previous
    ePrevious = eInput;
    //Calculate the control signal
    controlOutput = Kp * eInput + Ki * eIntegral + Kd * eDeriv;

    return controlOutput; 
}

float PIDController::calculateOutput(float eInput, std::chrono::duration<float> sampleTime){
    //Store the new sample time
    dT = sampleTime;
    return calculateOutput(eInput);
}

float PIDController::getOutput() {return controlOutput;}
