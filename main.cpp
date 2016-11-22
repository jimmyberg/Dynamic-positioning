#include <iostream>
#include "PhysicalDefinitions.h"
#include "BoatController.h"
#include "Simulate.h"

using namespace std;

int main(void){
	Boat boat;
	SimulatedWorld simulation(&boat, 0.001);
	BoatController boatController(&boat);
	cout << boat.currentPosition << endl;
	cout << boat.azimuthThruster[0].throttle << endl;
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			simulation.calculateWorldTick();
			cout << boat.currentPosition << endl;
		}
		boatController.singleStep();
	}
    return 0;
}
