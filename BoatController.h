#ifndef _BOATCONTROLLER_H_
#define _BOATCONTROLLER_H_

#include "PhysicalDefinitions.h"
#include <thread>
#include <chrono>


/**
 * @brief      Class that implements the controller of the boat
 */
class BoatController{
	public:

        /**
         * @brief      Constructor
         *
         * @param      b     Pointer to the boat object to control
         */
        BoatController(Boat *b);
        
        /**
         * @brief      Destroys the object.
         */
        ~BoatController();

        
        /**
         * @brief      Starts the boatController internal thread.
         */
        void startControl();

        /**
         * @brief      Stops the boatController internal thread.
         */
        void stopControl();

        /**
         * @brief      Determines if the boatController thread is running.
         *
         * @return     True if running, False otherwise.
         */
        bool isRunning() {return running;};

        /**
         * @brief      Does a single control step.
         */
        void singleStep();

        float xSignal = 0.0; //!< The current control signal of the x position
        float ySignal = 0.0; //!< The current control signal of the y position
        float hSignal = 0.0; //!< The current control signal of the heading

	private:
        Boat *boat; //!< The pointer to the boat that is controlled by this class
        std::thread controlThread; //!< The internal thread that will control the boat periodically
        std::chrono::duration<float> periodTime; //!< The current periodTime of the thread
        std::chrono::time_point<std::chrono::high_resolution_clock> lastTime, currentTime; //!< Used to determine the periodTime

        bool running = false; //!< Stores if the control thread is running or not

        //Controllers
        PIDController xController; //!< The PIDController of the x position
	PIDController yController; //!< The PIDController of the y position
	PIDController hController; //!< The PIDController of the heading

        /**
         * @brief      The function that runs in the boatController controlThread
         */
        void controlFunction();

        /**
         * @brief      Converts the heading control signal to a vector that can be used to control a thruster
         *
         * @param[in]  hSignal  The heading signal
         * @param[in]  left     The angle if the thruster has to turn the boat to the left
         * @param[in]  right    The angle if the thruster has to turn the boat to the right
         *
         * @return     The vector for the thruster determined by the heading
         */
        Vector2<float> getHeadingVector(float hSignal, float left, float right);

        /**
         * @brief      Used to write left, or right to the output if the input is above or below a threshold
         *
         * @param[in]  error      The error signal
         * @param[in]  threshold  The threshold
         * @param[in]  left       The left angle
         * @param[in]  right      The right angle
         *
         * @return     The angle associated to the input
         */
        float thresholding(float error, float threshold, float left, float right);
};
#endif
