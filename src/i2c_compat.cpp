#include <Arduino.h>
#include <Wire.h>

extern "C" {
#include "vl53l1_api.h"

VL53L1_Error VL53L1_ReadMulti(VL53L1_Dev_t *pdev, uint16_t index, 
        uint8_t * pdata, uint32_t   count)
{
    int status = 0;
    //Loop until the port is transmitted correctly
    do
    {
        Wire.beginTransmission(pdev->devAddr);
        uint8_t buffer[2];
        buffer[0]=(uint8_t) (index>>8);
        buffer[1]=(uint8_t) (index&0xFF);
        Wire.write(buffer, 2);
        status = Wire.endTransmission(false);
        //Fix for some STM32 boards
        //Reinitialize th i2c bus with the default parameters
#ifdef ARDUINO_ARCH_STM32
        if (status)
        {
            Wire.end();
            Wire.begin();
        }
#endif
        //End of fix
    }
    while(status != 0);

    Wire.requestFrom((int)pdev->devAddr, (int) count);

    int i=0;
    while (Wire.available()) {
        pdata[i] = Wire.read();
        i++;
    }


    return VL53L1_ERROR_NONE;
}

VL53L1_Error VL53L1_WriteMulti(VL53L1_Dev_t *pdev, uint16_t index, 
        uint8_t * pdata, uint32_t count)
{
    Wire.beginTransmission(pdev->devAddr);
    uint8_t buffer[2];
    buffer[0]=(uint8_t) (index>>8);
    buffer[1]=(uint8_t) (index&0xFF);
    Wire.write(buffer, 2);
    for (uint16_t i = 0 ; i < count ; i++)
        Wire.write(pdata[i]);

    Wire.endTransmission(true);
    return VL53L1_ERROR_NONE;
}

VL53L1_Error VL53L1_WaitUs(VL53L1_Dev_t *pdev, int32_t usec)
{
    delayMicroseconds(usec);
    return 0;
}

}
