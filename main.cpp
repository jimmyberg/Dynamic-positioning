#include <iostream>
#include "PhysicalDefinitions.h"
#include "BoatController.h"
#include "Simulate.h"
#include <math.h>

using namespace std;

int main(void){
	Boat boat;
	SimulatedWorld simulation(&boat, 0.001);
	BoatController boatController(&boat);
	boat.setpointPosition.x = 1.0;
	boat.setpointPosition.y = 2.0;
	boat.mass = 10;
	boat.angularMass = 5;
	boat.azimuthThruster[0].localLocation = Vector2<float>(0, 1);
	boat.azimuthThruster[0].maxForce = 10;
	boat.azimuthThruster[0].currentRotation = M_PI / 2;
	boat.azimuthThruster[0].normalRotation = 0;
	boat.azimuthThruster[1].localLocation = Vector2<float>(0, -1);
	boat.azimuthThruster[1].maxForce = 10;
	boat.azimuthThruster[1].currentRotation = M_PI / 2;
	boat.azimuthThruster[1].normalRotation = 0;
	boat.currentHeading = 0;
	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			simulation.calculateWorldTick();
			cout.width(10);
			cout << ((i * 10) + j) * 0.001 << ",";
			cout.width(10);
			cout << boat.azimuthThruster[0].rotation + boat.azimuthThruster[0].normalRotation << ",";
			cout.width(10);
			cout << boat.azimuthThruster[1].rotation + boat.azimuthThruster[1].normalRotation << ",";
			cout.width(10);
			cout << boat.currentPosition.x << ",";
			cout.width(10);
			cout << boat.currentPosition.y;
			cout << endl;
		}
		boat.azimuthThruster[0].throttle = 1;
		boat.azimuthThruster[1].throttle = 1;
		boat.azimuthThruster[0].currentRotation = 0;
		boat.azimuthThruster[1].currentRotation = 0;
		//boatController.singleStep();
	}
	boatController.singleStep();
    return 0;
}
