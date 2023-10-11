#include <Arduino.h>
#include <Wire.h>

extern "C" {
#include "vl53l1_api.h"
#include "vl53l1_core.h"
#include "vl53l1_helpers.h"
}


class VL53L1X {

    public:

        bool begin(void)
        {
            _dev.devAddr = 0x29;

            auto status = VL53L1_DataInit(&_dev);
            status = VL53L1_StaticInit(&_dev);

            status = VL53L1_SetDistanceMode(&_dev, 2); 
            status = VL53L1_SetDistanceMode(&_dev, VL53L1_DISTANCEMODE_MEDIUM);
            status = VL53L1_SetMeasurementTimingBudgetMicroSeconds(&_dev, 25000);

            return status == VL53L1_ERROR_NONE;
        }


        int16_t readDistance(void)
        {
            auto status = VL53L1_ClearInterruptAndStartMeasurement(&_dev);   

            while (true) {
                uint8_t dataReady=0;
                status = VL53L1_GetMeasurementDataReady(&_dev, &dataReady);
                if (dataReady) {
                    break;
                }
                delay(2);
            }

            VL53L1_RangingMeasurementData_t rangingData;

            status = VL53L1_GetRangingMeasurementData(&_dev, &rangingData);

            status = VL53L1_StopMeasurement(&_dev);

            return status == VL53L1_ERROR_NONE ? rangingData.RangeMilliMeter : -1;

        }

    private:

        VL53L1_Dev_t _dev;
};
