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


VL53L1_Error VL53L1_WrWord(VL53L1_Dev_t *pdev, uint16_t index, uint16_t data)
{
    (void)pdev;
    (void)index;
    (void)data;

    return VL53L1_ERROR_NONE;
}


VL53L1_Error VL53L1_poll_for_boot_completion(VL53L1_Dev_t *pdev,
        uint32_t timeout_ms)
{
    (void)pdev;
    (void)timeout_ms;

    return VL53L1_ERROR_NONE;
}

VL53L1_Error VL53L1_is_new_data_ready(VL53L1_Dev_t *pdev, uint8_t *pready)
{
    (void)pdev;
    (void)pready;

    return VL53L1_ERROR_NONE;
}

VL53L1_Error VL53L1_poll_for_range_completion(VL53L1_Dev_t *pdev, 
        uint32_t timeout_ms)
{
    (void)pdev;
    (void)timeout_ms;

    return VL53L1_ERROR_NONE;
}

VL53L1_Error VL53L1_wait_for_boot_completion(VL53L1_Dev_t *pdev)
{
    (void)pdev;

    return VL53L1_ERROR_NONE;
}

}
