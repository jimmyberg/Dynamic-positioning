//This file contains the definition of the PIDController class
#ifndef _PIDCONTROLLER_H_
#define _PIDCONTROLLER_H_

#include <chrono>

class PIDController{
    public:
        PIDController();
        PIDController(float p, float i, float d, float prev, float integral, float iGain);
        PIDController(float p, float i, float d, float prev, float integral, float iGain, std::chrono::duration<float> sampleTime);
        ~PIDController();
        
        float calculateOutput(float eInput);
        float calculateOutput(float eInput, std::chrono::duration<float> sampleTime);
        float getOutput();
        
        float Kp, Ki, Kd, inputGain; //P, I and D constants
        std::chrono::duration<float> dT; //Sampling time
        
    private:
        float ePrevious, eIntegral, controlOutput; //Error and output signals
};
#endif
