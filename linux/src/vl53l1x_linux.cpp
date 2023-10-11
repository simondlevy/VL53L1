extern "C" {
#include "st_src/vl53l1_api.h"

VL53L1_Error VL53L1_ReadMulti(VL53L1_Dev_t *pdev, uint16_t index, 
        uint8_t * pdata, uint32_t   count)
{
    return VL53L1_ERROR_NONE;
}

VL53L1_Error VL53L1_WriteMulti(VL53L1_Dev_t *pdev, uint16_t index, 
        uint8_t * pdata, uint32_t count)
{
    return VL53L1_ERROR_NONE;
}

VL53L1_Error VL53L1_WaitUs(VL53L1_Dev_t *pdev, int32_t usec)
{
    return VL53L1_ERROR_NONE;
}

}
