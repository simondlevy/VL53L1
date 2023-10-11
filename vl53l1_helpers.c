#include "vl53l1_ll_def.h"
#include "vl53l1_platform_user_data.h"
#include "vl53l1_api.h"

VL53L1_Error VL53L1_WrByte(VL53L1_Dev_t *pdev, uint16_t index, uint8_t data)
{
    return VL53L1_WriteMulti(pdev, index, &data, 1);
}

VL53L1_Error VL53L1_RdByte(VL53L1_Dev_t *pdev, uint16_t index, uint8_t *pdata)
{
    return VL53L1_ReadMulti(pdev, index, pdata, 1);
}

