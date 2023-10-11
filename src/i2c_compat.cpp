#include <Arduino.h>
#include <Wire.h>

extern "C" {
#include "st_src/vl53l1_api.h"

VL53L1_Error VL53L1_ReadMulti(VL53L1_Dev_t *pdev, uint16_t index, 
        uint8_t * pdata, uint32_t   count)
{
    TwoWire * twoWire = (TwoWire *)pdev->I2Cx;

    int status = 0;

    //Loop until the port is transmitted correctly
    do
    {
        twoWire->beginTransmission(pdev->devAddr);
        uint8_t buffer[2];
        buffer[0]=(uint8_t) (index>>8);
        buffer[1]=(uint8_t) (index&0xFF);
        twoWire->write(buffer, 2);
        status = twoWire->endTransmission(false);
        //Fix for some STM32 boards
        //Reinitialize th i2c bus with the default parameters
#ifdef ARDUINO_ARCH_STM32
        if (status)
        {
            twoWire->end();
            twoWire->begin();
        }
#endif
        //End of fix
    }
    while(status != 0);

    twoWire->requestFrom((int)pdev->devAddr, (int) count);

    int i=0;
    while (twoWire->available()) {
        pdata[i] = twoWire->read();
        i++;
    }


    return VL53L1_ERROR_NONE;
}

VL53L1_Error VL53L1_WriteMulti(VL53L1_Dev_t *pdev, uint16_t index, 
        uint8_t * pdata, uint32_t count)
{
    TwoWire * twoWire = (TwoWire *)pdev->I2Cx;

    twoWire->beginTransmission(pdev->devAddr);
    uint8_t buffer[2];
    buffer[0]=(uint8_t) (index>>8);
    buffer[1]=(uint8_t) (index&0xFF);
    twoWire->write(buffer, 2);
    for (uint16_t i = 0 ; i < count ; i++)
        twoWire->write(pdata[i]);

    twoWire->endTransmission(true);
    return VL53L1_ERROR_NONE;
}

VL53L1_Error VL53L1_WaitUs(VL53L1_Dev_t *pdev, int32_t usec)
{
    delayMicroseconds(usec);
    return 0;
}

}
