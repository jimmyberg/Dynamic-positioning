#include <iostream>
#include <unistd.h>
#include "PhysicalDefinitions.h"
#include "BoatController.h"
#include "Simulate.h"
#include "MotorController.h"
#include <math.h>

using namespace std;

#define _INTERACTIVE_TERMINAL_DYNPOS_

int i, j;

int main(void){
    Boat boat;
    SimulatedWorld simulation(&boat, 0.001);
    BoatController boatController(&boat);
    boat.currentPosition.x = 0.0;
    boat.currentPosition.y = 0.0;
    boat.currentHeading = 0.0;
    boat.setpointPosition.x = 30.0;
    boat.setpointPosition.y = 0.0;
    boat.setpointHeading = 1.0;
    boat.mass = 10;
    boat.angularMass = 5;
    boat.azimuthThruster[0].localLocation = Vector2<float>(0, 1);
    boat.azimuthThruster[0].maxForce = 10;
    boat.azimuthThruster[0].rotation = 0;
    boat.azimuthThruster[0].normalRotation = M_PI_2;
    boat.azimuthThruster[0].throttle = 0;
    boat.azimuthThruster[1].localLocation = Vector2<float>(0, -1);
    boat.azimuthThruster[1].maxForce = 10;
    boat.azimuthThruster[1].rotation = 0;
    boat.azimuthThruster[1].normalRotation = M_PI_2;
    boat.azimuthThruster[1].throttle = 0;

    //Array used to let the Arduino communicate with us. Not used right now
    uint8_t flowRegister[32];
    //Construct a UsbSocket object to communicate with the arduino/motorController
    FlowSerial::UsbSocket arduino(flowRegister, sizeof(flowRegister) / sizeof(flowRegister[0]));
    //Connect to the serial device. Useally /dev/ttyACM0 for Arduino's
    arduino.connectToDevice("/dev/ttyACM0", 115200);
    //Sleep to let the Arduino start up(get out of it's boatloader state)
    #ifdef _INTERACTIVE_TERMINAL_DYNPOS_
    cout << "Starting Arduino" << endl;
    #endif
    usleep(2000000);

    //A class to simplify the handling of the boat
    static MotorController motorController(arduino);
    #ifdef _INTERACTIVE_TERMINAL_DYNPOS_
    cout << "Starting engines" << endl;
    #endif
    motorController.startMotors();
    #ifdef _INTERACTIVE_TERMINAL_DYNPOS_
    cout << "Ready. Press enter to start" << endl;
    cin.get();
    #endif
    cout << "time,thruster0rotation,thrust0,thruster1rotation,thrust1,x,y,heading,errorX,errorY,errorH,xSignal,ySignal,hSignal" << endl;
    for (i = 0; i < 45000; ++i)
    {
		for (j = 0; j < 10; ++j)
		{
			simulation.calculateWorldTick();
        }

        boatController.singleStep();

        if(i % 50 == 0){
            float errorX = boat.setpointPosition.x - boat.currentPosition.x;
            float errorY = boat.setpointPosition.y - boat.currentPosition.y;
            float errorH = boat.setpointHeading - boat.currentHeading;

            cout.width(12);
            cout << ((i * 10) + j) * 0.001 << ",";
            cout.width(12);
            cout << boat.azimuthThruster[0].rotation + boat.azimuthThruster[0].normalRotation << ",";
            cout.width(12);
            cout << boat.azimuthThruster[0].throttle << ",";
            cout.width(12);
            cout << boat.azimuthThruster[1].rotation + boat.azimuthThruster[1].normalRotation << ",";
            cout.width(12);
            cout << boat.azimuthThruster[1].throttle << ",";
            cout.width(12);
            cout << boat.currentPosition.x << ",";
            cout.width(12);
            cout << boat.currentPosition.y << ",";
            cout.width(12);
            cout << boat.currentHeading << ",";
            cout.width(12);
            cout << errorX << ",";
            cout.width(12);
            cout << errorY << ",";
            cout.width(12);
            cout << errorH << ",";
            cout.width(12);
            cout << boatController.xSignal << ",";
            cout.width(12);
            cout << boatController.ySignal << ",";
            cout.width(12);
            cout << boatController.hSignal
            << endl;
        }

        motorController.setMotorFront(uint8_t(boat.azimuthThruster[0].throttle * 180));
        motorController.setRotationFront(uint8_t(boat.azimuthThruster[0].rotation * 180 / (2*M_PI)));
        motorController.syncRegisters();
        usleep(10000);
    }
    return 0;
}
