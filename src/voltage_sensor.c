#include "voltage_sensor_priv.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>


voltage_sensor_err_t voltage_sensor_read (voltage_sensor_handle_t handle, uint32_t *value)
{
    if (handle == NULL || value == NULL)
    {
        return VOLTAGE_SENSOR_INVALID_ARG;
    }
    
    return handle->interface->read(handle, value);
}

voltage_sensor_err_t voltage_sensor_raw_to_actual(voltage_sensor_handle_t handle, uint32_t raw, uint32_t *actual)
{
    if (handle == NULL || actual == NULL)
    {
        return VOLTAGE_SENSOR_INVALID_ARG;
    }

    return handle->interface->raw_to_actual(handle, raw, actual);
}

uint32_t voltage_sensor_get_scale_factor(voltage_sensor_handle_t handle)
{
    return handle->interface->get_scale_factor(handle);
}

voltage_sensor_err_t voltage_sensor_destroy(voltage_sensor_handle_t handle)
{
    return handle->interface->destroy(handle);
}


