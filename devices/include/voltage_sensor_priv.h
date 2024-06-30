#ifndef VOLTAGE_SENSOR_PRIV_H__
#define VOLTAGE_SENSOR_PRIV_H__

#include "voltage_sensor.h"

typedef struct voltage_sensor_interface_s {
    voltage_sensor_err_t (* read)(voltage_sensor_handle_t handle, uint32_t *value);
    voltage_sensor_err_t (* raw_to_actual)(voltage_sensor_handle_t handle, uint32_t raw, uint32_t *actual);
    voltage_sensor_err_t (* destroy)(voltage_sensor_handle_t handle);
} voltage_sensor_interface_t;

typedef struct voltage_sensor_s {
    const char *name;
    voltage_sensor_interface_handle_t interface;
} voltage_sensor_t;

#endif // VOLTAGE_SENSOR_PRIV_H__