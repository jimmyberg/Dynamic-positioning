//This file contains the code of the PIDController class
#include "PIDController.h"
#include <chrono>


PIDController::PIDController(){
    init(0.0, 0.0, 0.0, 0.0, 0.0, std::chrono::duration<float>(std::chrono::duration_values<float>::zero()));
}

PIDController::PIDController(float p, float i, float d, float prev, float integral, std::chrono::duration<float> sampleTime){
    init(p, i, d, prev, integral, sampleTime);
}

PIDController::~PIDController(){}

void PIDController::init(float p, float i, float d, float prev, float integral, std::chrono::duration<float> sampleTime){
    //Transfer constants
    Kp = p;
    Ki = i;
    Kd = d;
    //Set initial values
    ePrevious = prev;
    eIntegral = integral;
    //Set sample time
    dT =  sampleTime;
    //Set output
    controlOutput = 0.0;
}

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
    calculateOutput(eInput);
}

inline float PIDController::getOutput() {return controlOutput;};

inline void PIDController::setConstants(float p, float i, float d){
    Kp = p;
    Ki = i;
    Kd = d;
}

inline std::tuple<float, float, float> PIDController::getConstants(){
    return std::tuple<float,float,float>(Kp, Ki, Kd);
}

inline void PIDController::setSampleTime(std::chrono::duration<float> sampleTime) {dT = sampleTime;}
inline std::chrono::duration<float> PIDController::getSampleTime() {return dT;}; 
