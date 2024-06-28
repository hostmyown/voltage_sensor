#include "voltage_sensor.h"
#include <stdlib.h>
#include <memory.h>

typedef struct voltage_sensor_s
{
    voltage_sensor_config_t config;
} voltage_sensor_t;

voltage_sensor_err_t voltage_sensor_create(voltage_sensor_config_t *config, voltage_sensor_handle_t *handle)
{
     voltage_sensor_handle_t self = calloc(1, sizeof(voltage_sensor_t));

     if (self == NULL)
     {
        return VOLTAGE_SENSOR_OUT_OF_MEMORY;
     }

     self->config = *config;

     *handle = self;

     return VOLTAGE_SENSOR_OK;
}

void voltage_sensor_destroy(voltage_sensor_handle_t handle)
{
    free(handle);
}


