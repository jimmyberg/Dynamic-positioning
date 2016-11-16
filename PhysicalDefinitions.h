
//Al units are in basic SI units. m, kg, s etc. unless other specified

#include "Vector2/Vector2.hpp"

class BaseThurster{
	Vector2<float> localLocation;
	float normalRotation;
	float throttle;
};

class AzimuthThruster: public BaseThurster{
	float rotation;
	float currentRotation;
};

class Boat{
public:
	Vector2<float> getPosition();
	void gotoPosition(Vector2<float> newPosition, float speed);
	AzimuthThruster azimuthThruster[2];
private:
	//Positional states
	//SensorCalculations sensorCalculations;
	Vector2<float> currentPosition = 0; //Current position of the boat (in X,Y).
	Vector2<float> currentSpeed = 0; //Current speed of the boat (in X,Y).
	float setpointSpeed = 0; //The maximal speed you want (user input).
	Vector2<float> setpointPosition = 0; //The position the boat is heading to.
	float currentHeading = 0, setpointHeading = 0; //Heading is the amount of degrees.
	//Physical properies
	float mass;
	float angularMass;
	Vector2<float> directianalDamping;
	float angularDamping;
};

class controller{
	Boat* boat;
};
