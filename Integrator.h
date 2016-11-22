
#ifndef _INTEGRATOR_H_
#define _INTEGRATOR_H_

class Integrator
{
public:
	Integrator(float idT);
	Integrator(float idT, float iy);
	/**
	 * @brief Update funtion to insert new value.
	 * @details This functionality was discovered using the 
	 * billiniear transform on H(s)=1/s.
	 * 
	 * @param input Input value used to integrate.
	 * @return Newly calculated output value.
	 */
	float update(float input);
	/**
	 * @return Current output value of the integrator.
	 */
	float getCurrentOutput(){return y;}
	const float dT;
private:
	Integrator();
	float y = 0; /**< current output value. Also used as previous output value */
	float x_1 = 0; /**< Previous input value */
};

#endif //_INTEGRATOR_H_
