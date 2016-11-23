#include <iostream>
#include "PhysicalDefinitions.h"
#include "BoatController.h"
#include "Simulate.h"

using namespace std;

int main(void){
	Boat boat;
	SimulatedWorld simulation(&boat, 0.001);
	BoatController boatController(&boat);
	boat.mass = 10;
	boat.angularMass = 5;

	cout << boat.currentPosition << endl;
	cout << boat.azimuthThruster[0].throttle << endl;
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			simulation.calculateWorldTick();
			//cout << boat.currentPosition << endl;
		}
		boatController.singleStep();
	}
    return 0;
}
