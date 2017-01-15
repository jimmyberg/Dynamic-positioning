#ifndef _BOATCONTROLLER_H_
#define _BOATCONTROLLER_H_

#include "PhysicalDefinitions.h"
#include <thread>
#include <chrono>

class BoatController{
	public:
        BoatController(Boat *b);
        ~BoatController();

        //Start stop control thread
        void startControl();
        void stopControl();

        bool isRunning() {return running;};

        void singleStep();

        float xSignal = 0.0;
        float ySignal = 0.0;
        float hSignal = 0.0;

	private:
        Boat *boat;
        std::thread controlThread;
        std::chrono::duration<float> periodTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> lastTime, currentTime;

        bool running = false;

        //Controllers
        PIDController xController;
		PIDController yController;
		PIDController hController;

        void controlFunction();
        Vector2<float> getHeadingVector(float hSignal, float left, float right);
        float thresholding(float error, float threshold, float left, float right);
};
#endif
