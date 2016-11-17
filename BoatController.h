#ifndef _BOATCONTROLLER_H_
#define _BOATCONTROLLER_H_

#include "PhysicalDefinitions.h"
#include <thread>

class BoatController{
	public:
        BoatController(Boat *b);
        ~BoatController();
	private:
        std::thread controlThread;
        Boat *boat;

        bool running;
        
        //Controllers
        PIDController xController;
		PIDController yController;
		PIDController hController;

        //Start stop control thread
        void startControl();
        void stopControl();

        void controlFunction();
		float calculateHeading(Vector2<float> currentPosition, Vector2<float> setpointPosition);
};
#endif
