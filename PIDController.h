//This file contains the definition of the PIDController class
#ifndef _PIDCONTROLLER_H_
#define _PIDCONTROLLER_H_

#include <chrono>


/**
 * @brief      Class implemention a PID controller
 */
class PIDController{
    public:
        /**
         * @brief      Default constructor
         */
        PIDController();
        /**
         * @brief      Constructor without sampleTime
         *
         * @param[in]  p         Gain of the P controller
         * @param[in]  i         Gain of the I controller
         * @param[in]  d         Gain of the D controller
         * @param[in]  prev      The previous value of the error signal
         * @param[in]  integral  The starting integrated value
         * @param[in]  iGain     The input gain
         */
        PIDController(float p, float i, float d, float prev, float integral, float iGain);
        
        /**
         * @brief      Constructor with sampleTime
         *
         * @param[in]  p           Gain of the P controller
         * @param[in]  i           Gain of the I controller
         * @param[in]  d           Gain of the D controller
         * @param[in]  prev        The previous value of the error signal
         * @param[in]  integral    The starting integrated value
         * @param[in]  iGain       The input gain
         * @param[in]  sampleTime  The sample time
         */
        PIDController(float p, float i, float d, float prev, float integral, float iGain, std::chrono::duration<float> sampleTime);
        
        /**
         * @brief      Destroys the object.
         */
        ~PIDController();
        

        /**
         * @brief      Calculates the output.
         *
         * @param[in]  eInput  The error input
         *
         * @return     The output control signal.
         */
        float calculateOutput(float eInput);
        
        /**
         * @brief      Calculates the output.
         *
         * @param[in]  eInput      The error input
         * @param[in]  sampleTime  The sample time
         *
         * @return     The output.
         */
        float calculateOutput(float eInput, std::chrono::duration<float> sampleTime);
        
        /**
         * @brief      Gets the last control signal output.
         *
         * @return     The output control signal.
         */
        float getOutput();
        
        float Kp, Ki, Kd, inputGain; //!<P, I and D constants, and the input gain
        std::chrono::duration<float> dT; //!<Sampling time
        
    private:
        float ePrevious, eIntegral, controlOutput; //!<Previous error, integral error and output signals
};
#endif
