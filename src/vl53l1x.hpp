/*
   Copyright (C) 2023, Simon D. Levy
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.
 * Neither the name of STMicroelectronics nor the
 names of its contributors may be used to endorse or promote products
 derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND
 NON-INFRINGEMENT OF INTELLECTUAL PROPERTY RIGHTS ARE DISCLAIMED.
 IN NO EVENT SHALL STMICROELECTRONICS INTERNATIONAL N.V. BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.#include <Arduino.h>
 */

#pragma once

extern "C" {
#include "st_src/vl53l1_api.h"
#include "st_src/vl53l1_helpers.h"
}


class VL53L1X {

    public:

        typedef enum {

            DISTANCE_MODE_SHORT = 1,
            DISTANCE_MODE_MEDIUM,
            DISTANCE_MODE_LONG

        } distanceMode_t;

         /**
         * Returns true on success, false on failure
         */
        bool setDistanceMode(distanceMode_t distanceMode)
        {
            return VL53L1_SetDistanceMode(&_dev, distanceMode) == VL53L1_ERROR_NONE;
        }

        /**
         * Returns true on success, false on failure
         */
        bool setTimingBudgetMsec(const uint32_t msec)
        {

            return VL53L1_SetMeasurementTimingBudgetMicroSeconds(
                    &_dev, msec*1000) == VL53L1_ERROR_NONE;
        }

        /**
         * Returns true on success, false on failure
         */
        bool begin(void)
        {
            auto status = VL53L1_DataInit(&_dev);

            status |= VL53L1_StaticInit(&_dev);

            return status == VL53L1_ERROR_NONE;
        }

        /**
         * Returns distance in mm on success, -1 on failure
         */
        int16_t readDistance(void)
        {
            auto status = VL53L1_ClearInterruptAndStartMeasurement(&_dev);   

            while (true) {
                uint8_t dataReady=0;
                status |= VL53L1_GetMeasurementDataReady(&_dev, &dataReady);
                if (dataReady) {
                    break;
                }
                VL53L1_WaitUs(&_dev, 2000);
            }

            VL53L1_RangingMeasurementData_t rangingData;

            status |= VL53L1_GetRangingMeasurementData(&_dev, &rangingData);

            status |= VL53L1_StopMeasurement(&_dev);

            return status == VL53L1_ERROR_NONE ? rangingData.RangeMilliMeter : -1;

        }

        /**
         * Returns true on success, false on failure
         */
        bool changeAddress(const uint8_t oldAddress, const uint8_t newAddress)
        {
            _dev.devAddr = oldAddress;

            auto status = VL53L1_SetDeviceAddress(&_dev, newAddress);

            _dev.devAddr = newAddress;

            return status == VL53L1_ERROR_NONE;
        }

    protected:

        VL53L1X( void * i2c_device, const uint8_t devAddr=0x29)
        {
            _dev.I2Cx = i2c_device;
            _dev.devAddr = devAddr;
        }

    private:

        VL53L1_Dev_t _dev;
};
