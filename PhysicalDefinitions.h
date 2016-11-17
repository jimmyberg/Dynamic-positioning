#ifndef _PHYSICALDEFINITIONS_H_
#define _PHYSICALDEFINITIONS_H_

#include "PIDController.h"
#include "SensorCalculations.h"

//Al units are in basic SI units. m, kg, s etc. unless other specified

class SensorCalculations;

class Vector2{
	public:
		float x = 0;
		float y = 0;
};

class BaseThurster{
	public:
		Vector2 localLocation;
		float normalRotation;
		float throttle;
};

class AzimuthThruster: public BaseThurster{
	float rotation;
	float currentRotation;
};

class Boat{
public:
	Vector2 getPosition();
	void setSetpointPosition(Vector2 position);

	float getHeading();
	void setSetpointHeading(float heading);

	AzimuthThruster azimuthThruster[2];
private:
	//Positional states
	SensorCalculations sensorCalculations;
	Vector2 currentPosition; //Current position of the boat (in X,Y).
	Vector2 currentSpeed; //Current speed of the boat (in X,Y).
	float setpointSpeed = 0; //The maximal speed you want (user input).
	Vector2 setpointPosition; //The position the boat is heading to.
	float currentHeading = 0, setpointHeading = 0; //Heading is the amount of degrees.
	//Physical properies
	float mass;
	float angularMass;
	Vector2 directianalDamping;
	float angularDamping;
};

class BoatController{
	public:
		Boat *boat;
	private:
		float calculateHeading(Vector2 currentPosition, Vector2 setpointPosition);
		PIDController xController;
		PIDController yController;
		PIDController hController;
};
#endif
