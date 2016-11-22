
#include "Simulate.h"
#include "Integrator.h"
#include <cmath>

SimulatedWorld::SimulatedWorld(Boat* iboat, float idT):
	boat(iboat),
	dT(idT){}

void SimulatedWorld::calculateWorldTick(){
	//A integrator will be used to translate acceleration to velocity.
	static Integrator velocityX(dT);
	static Integrator velocityY(dT);
	//A integrator will be used to translate velocity to position.
	static Integrator positionX(dT);
	static Integrator positionY(dT);
	//A integrator will be used to translate torque / angular mass to radians per second.
	static Integrator radiansPerSecond(dT);
	//A integrator will be used to translate radians per second to radians.
	static Integrator radians(dT);
	//Defining to-be-calculated forces on boat
	float currentTorque = 0;
	Vector2<float> localForce = 0;
	//Calculate each force from every thruster.
	for (int i = 0; i < 2; ++i){
		//First calculate the force the is acting on the motor
		Vector2<float> localForceOnMotor(
			sin(boat->azimuthThruster->normalRotation + boat->azimuthThruster[i].currentRotation),
			cos(boat->azimuthThruster->normalRotation + boat->azimuthThruster[i].currentRotation));
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
		localForce += 
			Vector2<float>(
				Vector2<float>::dotProduct(localForceOnMotor, boat->azimuthThruster[i].localLocation)
			) * 
			boat->azimuthThruster[i].localLocation.normalized();
	}
	//Add damping to the torque
	currentTorque -= boat->currentBoatAngularSpeed * boat->angularDamping;
	//Translate the localForce to global force.
	Vector2<float> globalForce = localForce.rotated(boat->currentHeading);
	//Add damping to the global force
	globalForce -= (boat->currentSpeed * boat->directionalDamping.rotated(boat->currentHeading));
	//Integrate acceleration to velocity
	boat->currentSpeed.x = velocityX.update(globalForce.x / boat->mass);
	boat->currentSpeed.y = velocityY.update(globalForce.y / boat->mass);
	//Integrate vellocity to accleration
	boat->currentPosition = positionX.update(velocityX.getCurrentOutput());
	boat->currentPosition = positionY.update(velocityY.getCurrentOutput());
	//integrate angular acceleration to angular velocity
	boat->currentBoatAngularSpeed = radiansPerSecond.update(currentTorque / boat->angularMass);
	//integrate angular velocity to angle
	boat->currentHeading = radians.update(radiansPerSecond.getCurrentOutput());
}
