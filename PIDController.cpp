//This file contains the code of the PIDController class
#include "PIDController.h"
#include <chrono>


PIDController::PIDController():
PIDController(
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    1.0,
    std::chrono::duration<float>(std::chrono::duration_values<float>::zero())){}

PIDController::PIDController(float p, float i, float d, float prev, float integral, float iGain):
PIDController(p, i, d, prev, integral, iGain, std::chrono::duration<float>(std::chrono::duration_values<float>::zero())){}

PIDController::PIDController(float p, float i, float d, float prev, float integral, float iGain, std::chrono::duration<float> sampleTime):
    Kp(p),
    Ki(i),
    Kd(d),
    inputGain(iGain),
    dT(sampleTime),
    ePrevious(prev),
    eIntegral(integral){}

PIDController::~PIDController(){}

float PIDController::calculateOutput(float eInput){
    float eInputGained = eInput * inputGain; 

    //Integrating the error
    eIntegral += eInputGained * dT.count();
    //Derivative of error
    float eDeriv = (eInputGained - ePrevious) / dT.count();
    //Store the current error as previous
    ePrevious = eInputGained;
    //Calculate the control signal
    controlOutput = Kp * eInputGained + Ki * eIntegral + Kd * eDeriv;

    return controlOutput; 
}

float PIDController::calculateOutput(float eInput, std::chrono::duration<float> sampleTime){
    //Store the new sample time
    dT = sampleTime;
    return calculateOutput(eInput);
}

float PIDController::getOutput() {return controlOutput;}
