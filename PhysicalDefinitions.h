#ifndef _PHYSICALDEFINITIONS_H_
#define _PHYSICALDEFINITIONS_H_

#include "PIDController.h"
#include "SensorCalculations.h"

//Al units are in basic SI units. m, kg, s etc. unless other specified

#include "Vector2/Vector2.hpp"

class BaseThurster{
public:
	Vector2<float> localLocation;
	float normalRotation = 0;
	float throttle = 0;
	float maxForce = 0;
};

class AzimuthThruster: public BaseThurster{
public:
	float rotation = 0;
	float currentRotation = 0;
};

class Boat{
public:
	Vector2<float> getPosition();
	void setSetpointPosition(Vector2<float> position);

	float getHeading();
	void setSetpointHeading(float heading);

	AzimuthThruster azimuthThruster[2];
	//Positional states
	//SensorCalculations sensorCalculations;
	Vector2<float> currentPosition = 0;            //Current position of the boat (in X,Y).
	Vector2<float> currentSpeed = 0;               //Current speed of the boat (in X,Y).
	float setpointSpeed = 0;                       //The maximal speed you want (user input).
	Vector2<float> setpointPosition = 0;           //The position the boat is heading to.
	float currentHeading = 0, setpointHeading = 0; //Heading is the amount of radians.
	float currentBoatAngularSpeed = 0;             //How fast the ship is turning is radians per second = 2 * pi * f
	//Physical properies
	float mass;
	float angularMass;
	Vector2<float> directionalDamping = 0;
	float angularDamping = 0;
};
#endif
