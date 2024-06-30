#ifndef VOLTAGE_SENSOR_H__
#define VOLTAGE_SENSOR_H__

#include <stdint.h>

/**********************************************************************
 *
 * voltage_sensor is responsible for ...
 *
 **********************************************************************/

typedef struct voltage_sensor_s * voltage_sensor_handle_t;
typedef struct voltage_sensor_interface_s * voltage_sensor_interface_handle_t;

typedef enum {
    VOLTAGE_SENSOR_OK,
    VOLTAGE_SENSOR_ERR,
    VOLTAGE_SENSOR_NOT_IMPLEMENTED,
    VOLTAGE_SENSOR_INVALID_ARG,
    VOLTAGE_SENSOR_OUT_OF_MEMORY,
    // Add more error codes as needed
} voltage_sensor_err_t;

voltage_sensor_err_t voltage_sensor_read(voltage_sensor_handle_t handle, uint32_t *value);
voltage_sensor_err_t voltage_sensor_raw_to_actual(voltage_sensor_handle_t handle, uint32_t raw, uint32_t *actual);
voltage_sensor_err_t voltage_sensor_destroy(voltage_sensor_handle_t handle);

#endif  /* VOLTAGE_SENSOR_H__ */