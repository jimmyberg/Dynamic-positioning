
#include "Integrator.h"

Integrator::Integrator(float idT):
	dT(idT){}

Integrator::Integrator(float idT, float iy):
	dT(idT),
	y(iy){}

float Integrator::update(float input){
	return y = y + ((input + x_1) * dT / 2);
}
