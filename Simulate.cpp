
#include "Simulate.h"
#include "Integrator.h"
#include <cmath>

//#define DEBUG_SIMULATE_DYNPOS
#ifdef DEBUG_SIMULATE_DYNPOS
	#include <iostream>
#endif //DEBUG_SIMULATE_DYNPOS


SimulatedWorld::SimulatedWorld(Boat* iboat, float idT):
	boat(iboat),
	dT(idT){}

void SimulatedWorld::calculateWorldTick(){
	//A integrator will be used to translate acceleration to velocity.
	static Integrator velocityX(dT, boat->currentSpeed.x);
	static Integrator velocityY(dT, boat->currentSpeed.y);
	//A integrator will be used to translate velocity to position.
	static Integrator positionX(dT, boat->currentPosition.x);
	static Integrator positionY(dT, boat->currentPosition.y);
	//A integrator will be used to translate torque / angular mass to radians per second.
	static Integrator radiansPerSecond(dT, boat->currentBoatAngularSpeed);
	//A integrator will be used to translate radians per second to radians.
	static Integrator radians(dT, boat->currentHeading);
	//Defining to-be-calculated forces on boat
	float currentTorque = 0;
	Vector2<float> localForce = 0;
	//Calculate each force from every thruster.
	#ifdef DEBUG_SIMULATE_DYNPOS
	std::cout << "*\tDebug data for void SimulatedWorld::calculateWorldTick()" << std::endl;
	#endif
	for (int i = 0; i < 2; ++i){
		//First calculate the force the is acting on the motor
		float angle = boat->azimuthThruster[i].normalRotation + boat->azimuthThruster[i].currentRotation;
		Vector2<float> localForceOnMotor(
			cos(angle),
			sin(angle));
		localForceOnMotor *= boat->azimuthThruster[i].throttle * boat->azimuthThruster[i].maxForce;
		/**
		 * Caclulate the torque due to the forces from the motors.
		 * Torque van be calculated by the cross product of the location and the force vector.
		 */
		currentTorque += 
			(boat->azimuthThruster[i].localLocation.x * localForceOnMotor.y) - 
			(boat->azimuthThruster[i].localLocation.y * localForceOnMotor.x);
		/**
		 * Calculate the Force acting the same line of the position vector. 
		 * This will give the accelerating force on the boat.
		 * This can be done by using the dot procuct of the two vectors and 
		 * point it in the direction of its local rotation
		 */
		localForce += localForceOnMotor;
		#ifdef DEBUG_SIMULATE_DYNPOS
		std::cout << "Results for motor[" << i << ']' << std::endl;
		std::cout << "motor position = " << boat->azimuthThruster[i].localLocation << std::endl;
		std::cout << "localForceOnMotor = " << localForceOnMotor << std::endl;
		std::cout << "currentTorque now = " << currentTorque << std::endl;
		std::cout << "localForce now = " << localForce << '\n' << std::endl;
		#endif
	}
	//Add damping to the torque
	currentTorque -= boat->currentBoatAngularSpeed * boat->angularDamping;
	//Translate the localForce to global force.
	Vector2<float> globalForce = localForce.rotated(boat->currentHeading);
	//Add damping to the global force
	#ifdef DEBUG_SIMULATE_DYNPOS
	std::cout << "*************************************" << std::endl;
	std::cout << "localForce total = " << localForce << std::endl;
	std::cout << "currentHeading = " << boat->currentHeading << std::endl;
	std::cout << "globalForce = " << globalForce << std::endl;
	std::cout << "currentTorque total = " << currentTorque << std::endl;
	std::cout << "*************************************" << std::endl;
	#endif
	globalForce -= (boat->currentSpeed * boat->directionalDamping.rotated(boat->currentHeading));
	//Integrate acceleration to velocity
	boat->currentSpeed.x = velocityX.update(globalForce.x / boat->mass);
	boat->currentSpeed.y = velocityY.update(globalForce.y / boat->mass);
	//Integrate vellocity to accleration
	boat->currentPosition.x = positionX.update(velocityX.getCurrentOutput());
	boat->currentPosition.y = positionY.update(velocityY.getCurrentOutput());
	//integrate angular acceleration to angular velocity
	boat->currentBoatAngularSpeed = radiansPerSecond.update(currentTorque / boat->angularMass);
	//integrate angular velocity to angle
	boat->currentHeading = radians.update(radiansPerSecond.getCurrentOutput());
}
