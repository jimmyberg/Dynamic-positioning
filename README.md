# Dynamic-positioning
Build for RH marine. The students of the Hague university made a dynamic positioning system that can be implemented an a Raspberry Pi or any other Linux based computer
## Type of boat
This software currently only works with a boat with two azimuth thruster in the front and back. 
If you want to use this software on other types of boats you must change the boatController.cpp and .h files.
## Dependicies
Note that this software works in combination with a Arduino board with motors installed on them. 
The software for the arduino can be found [here](https://github.com/overlord1123/Dynamic-positioning-arduino/). 
Also the Arduino itself uses the FlowSerial library. This can be found [here](https://github.com/overlord1123/FlowSerialArduino)
