#ifndef VOLTAGE_SENSOR_H__
#define VOLTAGE_SENSOR_H__

/**********************************************************************
 *
 * voltage_sensor is responsible for ...
 *
 **********************************************************************/

typedef struct voltage_sensor_s * voltage_sensor_handle_t;

typedef struct voltage_sensor_config_s {

} voltage_sensor_config_t;

typedef enum {
    VOLTAGE_SENSOR_OK,
    VOLTAGE_SENSOR_INVALID_CONFIG,
    VOLTAGE_SENSOR_OUT_OF_MEMORY,
    // Add more error codes as needed
} voltage_sensor_err_t;

voltage_sensor_err_t voltage_sensor_create(voltage_sensor_config_t *config, voltage_sensor_handle_t *handle);
void voltage_sensor_destroy(voltage_sensor_handle_t handle);

#endif  /* VOLTAGE_SENSOR_H__ */
