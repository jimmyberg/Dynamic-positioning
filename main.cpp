#include <iostream>
#include "PhysicalDefinitions.h"
#include "BoatController.h"
#include "Simulate.h"
#include <math.h>

using namespace std;

int i, j;

int main(void){
    Boat boat;
    SimulatedWorld simulation(&boat, 0.001);
    BoatController boatController(&boat);
    boat.currentPosition.x = 0.0;
    boat.currentPosition.y = 0.0;
    boat.currentHeading = 0.0;
    boat.setpointPosition.x = 30.0;
    boat.setpointPosition.y = 0.0;
    boat.setpointHeading = 1.0;
    boat.mass = 10;
    boat.angularMass = 5;
    boat.azimuthThruster[0].localLocation = Vector2<float>(0, 1);
    boat.azimuthThruster[0].maxForce = 10;
    boat.azimuthThruster[0].rotation = 0;
    boat.azimuthThruster[0].normalRotation = M_PI_2;
    boat.azimuthThruster[0].throttle = 0;
    boat.azimuthThruster[1].localLocation = Vector2<float>(0, -1);
    boat.azimuthThruster[1].maxForce = 10;
    boat.azimuthThruster[1].rotation = 0;
    boat.azimuthThruster[1].normalRotation = M_PI_2;
    boat.azimuthThruster[1].throttle = 0;

	cout << "time,thruster0rotation,thrust0,thruster1rotation,thrust1,x,y,heading,errorX,errorY,errorH,xSignal,ySignal,hSignal" << endl;
    for (i = 0; i < 4500; ++i)
    {
		for (j = 0; j < 10; ++j)
		{
			simulation.calculateWorldTick();

            float errorX = boat.setpointPosition.x - boat.currentPosition.x;
            float errorY = boat.setpointPosition.y - boat.currentPosition.y;
            float errorH = boat.setpointHeading - boat.currentHeading;

			cout << ((i * 10) + j) * 0.001 << ","
			<< boat.azimuthThruster[0].rotation + boat.azimuthThruster[0].normalRotation << ","
			<< boat.azimuthThruster[0].throttle << ","
			<< boat.azimuthThruster[1].rotation + boat.azimuthThruster[1].normalRotation << ","
			<< boat.azimuthThruster[1].throttle << ","
			<< boat.currentPosition.x << ","
			<< boat.currentPosition.y << ","
            << boat.currentHeading << ","
            << errorX << ","
            << errorY << ","
            << errorH << ","
            << boatController.xSignal << ","
            << boatController.ySignal << ","
            << boatController.hSignal
			<< endl;
		}
		boatController.singleStep();
    }
    boatController.singleStep();
    return 0;
}
