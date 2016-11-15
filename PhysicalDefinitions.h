
//Al units are in basic SI units. m, kg, s etc. unless other specified

class Vector2{
	float x, y;
};

class BaseThurster{
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
	gotoPosition(Vector2 newPosition, float speed);
	AzimuthThruster azimuthThruster[2];
private:
	//Positional states
	SensorCalculations sensorCalculations;
	Vector2 currentPosition = 0; //Current position of the boat (in X,Y).
	Vector2 currentSpeed = 0; //Current speed of the boat (in X,Y).
	float setpointSpeed = 0; //The maximal speed you want (user input).
	Vector2 setpointPosition = 0; //The position the boat is heading to.
	float currentHeading = 0, setpointHeading = 0; //Heading is the amount of degrees.
	//Physical properies
	float mass;
	float angularMass;
	Vector2 directianalDamping;
	float angularDamping;
};

class controller{
	*Boat boat;
};
