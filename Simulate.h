
#ifndef _SIMULATE_H_
#define _SIMULATE_H_

#include "Vector2/Vector2.hpp"
#include "PhysicalDefinitions.h"

class SimulatedWorld{
public:
	SimulatedWorld(Boat* iboat, float idT);
	void calculateWorldTick();
private:
	Boat* boat;
	const float dT;
};

#endif //_SIMULATE_H_
