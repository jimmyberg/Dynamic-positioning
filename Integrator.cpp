
#include "Integrator.h"

Integrator::Integrator(float idT):
	dT(idT){}

Integrator::Integrator(float idT, float iy):
	dt(idT),
	y(iy){}

float Integrator::update(float input){
	return y = y + ((input + x_1) / 2);
}
