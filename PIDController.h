//This file contains the definition of the PIDController class
#ifndef _PIDCONTROLLER_H_
#define _PIDCONTROLLER_H_

#include <chrono>
#include <tuple>

class PIDController{
    public:
        PIDController();
        PIDController(float, float, float, float, float, std::chrono::duration<float>);
        ~PIDController();
        
        float calculateOutput(float);
        float calculateOutput(float, std::chrono::duration<float>);
        float getOutput();
        
        void setConstants(float,float,float);
        std::tuple<float, float, float> getConstants();

        void setSampleTime(std::chrono::duration<float>);
        std::chrono::duration<float> getSampleTime();
        
    private:
        void init(float, float, float, float, float, std::chrono::duration<float>);
        float Kp, Ki, Kd; //P, I and D constants
        std::chrono::duration<float> dT; //Sampling time
        float ePrevious, eIntegral, controlOutput; //Error and output signals
};
#endif
