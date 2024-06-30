#include "voltage_sensor_priv.h"
#include "hmo_voltage_sensor.h"

#include <stddef.h>
#include <stdlib.h>

typedef struct hmo_voltage_sensor_s
{
    voltage_sensor_t base;
    hmo_voltage_sensor_config_t config;
} hmo_voltage_sensor_t;

static voltage_sensor_err_t read(voltage_sensor_handle_t handle, uint32_t *value);
static voltage_sensor_err_t raw_to_actual(voltage_sensor_handle_t handle, uint32_t raw, uint32_t *actual);
static voltage_sensor_err_t destroy(voltage_sensor_handle_t handle);

static voltage_sensor_interface_t interface = {
    read,
    raw_to_actual,
    destroy
};

voltage_sensor_err_t hmo_voltage_sensor_create(hmo_voltage_sensor_config_t *config ,voltage_sensor_handle_t *handle)
{
     hmo_voltage_sensor_t *self = (hmo_voltage_sensor_t *) calloc(1, sizeof(hmo_voltage_sensor_t));

     if (self == NULL)
     {
        return VOLTAGE_SENSOR_OUT_OF_MEMORY;
     }

    self->base.name = "hmo voltage sensor";
    self->base.interface = &interface;
    self->config = *config;
     *handle = (voltage_sensor_handle_t) self;

     return VOLTAGE_SENSOR_OK;
}

static voltage_sensor_err_t read(voltage_sensor_handle_t handle, uint32_t *value)
{
    hmo_voltage_sensor_t *self = (hmo_voltage_sensor_t *) handle;

    if (self == NULL)
    {
        return VOLTAGE_SENSOR_INVALID_ARG;
    }

    *value = 1234;

    return VOLTAGE_SENSOR_NOT_IMPLEMENTED;
}

static voltage_sensor_err_t raw_to_actual(voltage_sensor_handle_t handle, uint32_t raw, uint32_t *actual)
{
    hmo_voltage_sensor_t *self = (hmo_voltage_sensor_t *) handle;

    if (self == NULL)
    {
        return VOLTAGE_SENSOR_INVALID_ARG;
    }

    *actual = raw + 12345;

    return VOLTAGE_SENSOR_NOT_IMPLEMENTED;
}

static voltage_sensor_err_t destroy(voltage_sensor_handle_t handle)
{
    hmo_voltage_sensor_t *self = (hmo_voltage_sensor_t *) handle;

    if (self == NULL)
    {
        return VOLTAGE_SENSOR_INVALID_ARG;
    }

    return VOLTAGE_SENSOR_NOT_IMPLEMENTED;
}