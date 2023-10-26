#include <Arduino.h>
#include <Wire.h>

extern "C" {
#include "vendor/vl53l1_api.h"

VL53L1_Error VL53L1_ReadMulti(VL53L1_Dev_t *pdev, uint16_t rgstr, 
        uint8_t * pdata, uint32_t   count)
{
    TwoWire * twoWire = (TwoWire *)pdev->I2Cx;

    int status = 0;

    //Loop until the port is transmitted correctly
    do
    {
        twoWire->beginTransmission(pdev->devAddr);
        uint8_t buffer[2];
        buffer[0]=(uint8_t) (rgstr>>8);
        buffer[1]=(uint8_t) (rgstr&0xFF);
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

VL53L1_Error VL53L1_WriteMulti(VL53L1_Dev_t *pdev, uint16_t rgstr, 
        uint8_t * data, uint32_t count)
{
    TwoWire * twoWire = (TwoWire *)pdev->I2Cx;

    twoWire->beginTransmission(pdev->devAddr);

    static uint8_t buffer[256];
    buffer[0]=(uint8_t) (rgstr>>8);
    buffer[1]=(uint8_t) (rgstr&0xFF);
    memcpy(&buffer[2], data, count);

    twoWire->write(buffer, count+2);

    twoWire->endTransmission(true);
    
    return VL53L1_ERROR_NONE;
}

}
