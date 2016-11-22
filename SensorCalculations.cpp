#include "SensorCalculations.h"

//Predictment Position X,Y
//LastMesurement + (Speed * time) * lastspeed + 0.5 * acceleration * speed * (time* time)

void SensorCalculations::predictSpeed(Vector2<float> speed, float timePeriod, float acceleration)
{
    predictedSpeed[0] = speed;

    for (int i = 1; i < 10; i++)
    {
        predictedSpeed[i].x = predictedSpeed[i - 1].x + (timePeriod * acceleration);
        predictedSpeed[i].y = predictedSpeed[i - 1].y + (timePeriod * acceleration);
    }
}
//Predictment Position X,Y
//LastMesurement + (Speed * time) * lastspeed + 0.5 * acceleration * speed * (time* time)
void SensorCalculations::predictNextLocation(Vector2<float> setpointPosition, Vector2<float> speed, float timePeriod, float acceleration)
{
    predictedLocation[0] = setpointPosition;

    for (int i = 1; i < 10; i++)
    {
        predictedLocation[i].x = predictedLocation[i - 1].x + (predictedSpeed[i].x * timePeriod) * predictedSpeed[i - 1].x +
                                 0.5 * acceleration * predictedSpeed[i].x * (timePeriod * timePeriod);
        predictedLocation[i].y = predictedLocation[i - 1].y + (predictedSpeed[i].y * timePeriod) * predictedSpeed[i - 1].y +
                                 0.5 * acceleration * predictedSpeed[i].y * (timePeriod * timePeriod);
    }
}