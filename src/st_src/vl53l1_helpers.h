#include "vl53l1_ll_def.h"
#include "vl53l1_platform_user_data.h"
#include "vl53l1_api.h"

VL53L1_Error VL53L1_RdByte(VL53L1_Dev_t *pdev, uint16_t index, uint8_t *pdata);

VL53L1_Error VL53L1_WrByte(VL53L1_Dev_t *pdev, uint16_t index, uint8_t data); 

VL53L1_Error VL53L1_WrWord(VL53L1_Dev_t *pdev, uint16_t index, uint16_t data);

VL53L1_Error VL53L1_WaitUs(VL53L1_Dev_t *pdev, int32_t wait_us);

VL53L1_Error VL53L1_WaitMs(VL53L1_Dev_t *pdev, int32_t wait_ms);

VL53L1_Error VL53L1_GetTickCount(uint32_t *ptime_ms);

VL53L1_Error VL53L1_WaitValueMaskEx(VL53L1_Dev_t *pdev, uint32_t timeout_ms,
        uint16_t index, uint8_t value, uint8_t mask, uint32_t poll_delay_ms);



