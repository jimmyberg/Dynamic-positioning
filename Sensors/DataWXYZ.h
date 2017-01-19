#ifndef _DataWXYZ_H_
#define _DataWXYZ_H_

#include <iostream>

/**
 * @brief      Class for data wxyz. These are quaternion numbers for the Gyro data.
 */
class DataWXYZ{
    public:
        /**
         * @brief      Constructor
         *
         * @param[in]  wVal  The w value
         * @param[in]  xVal  The x value
         * @param[in]  yVal  The y value
         * @param[in]  zVal  The z value
         */
        DataWXYZ(float wVal, float xVal, float yVal, float zVal);
        /**
         * @brief      Empty constructor
         */
        DataWXYZ();
        /**
         * @brief      Destroys the object.
         */
        ~DataWXYZ();
        
        //functions


        /**
         * @brief      Gets the w.
         *
         * @return     The w.
         */
        float getW();

        /**
         * @brief      Gets the x.
         *
         * @return     The x.
         */
        float getX();

        /**
         * @brief      Gets the y.
         *
         * @return     The y.
         */
        float getY();

        /**
         * @brief      Gets the z.
         *
         * @return     The z.
         */
        float getZ();

        /**
         * @brief      Prints the data to the terminal
         */
        void printData();

    private:
        //variables
        float w, x, y, z;
};
#endif
