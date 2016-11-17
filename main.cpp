#include <iostream>
#include "PhysicalDefinitions.h"
#include "PIDController.h"
#include "Simulate.h"

using namespace std;

int main(void){
	DoubleIntegral test(0.01);
	for (int t = 0; t < 1.0; t += 0.01){
		cout << t << ',' << test.inputVal(1) << endl; 
	}    
    return 0;
}
