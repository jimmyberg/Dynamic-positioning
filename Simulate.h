
#ifndef _SIMULATE_H_
#define _SIMULATE_H_

#include "Vector2/Vector2.hpp"
#include "PhysicalDefinitions.h"

class SimulatedWorld{
public:
	/**
	 * @brief Constructor to set the pointer to boat and configuring delta time of the simulation.
	 * @details [long description]
	 * 
	 * @param iboat pointer to phisical boat object. Here data will be overwritten about its current location and speed.
	 * Throttle data is used to simulate the acceleration
	 * @param idT Delta time for every simulation cycle.
	 */
	SimulatedWorld(Boat* iboat, float idT);
	/**
	 * @brief Do a calulation cyle on the boat
	 * @details Every time this function is called the boat will be simulated by dT time forward.
	 */
	void calculateWorldTick();
private:
	Boat* boat; /**< pointer to boat. The truster data will be read and the postion and heading data will be writen by this class */
	const float dT; /**< period time for each calculation cycle */
};

#endif //_SIMULATE_H_
