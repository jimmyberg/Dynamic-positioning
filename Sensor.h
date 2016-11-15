#ifndef _Sensor_H_ 
#define _Sensor_H_
#define false 0 
#define true 1 
//#define uint unsigned int

class Sensor {
    private:
        uint Value = 0, height = 0;
        //Sensor();
    public:
        Sensor(int height);
        int area ();
};

#endif
