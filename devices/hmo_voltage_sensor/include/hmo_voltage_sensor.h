#ifndef HMO_VOLTAGE_SENSOR_H__
#define HMO_VOLTAGE_SENSOR_H__

typedef struct hmo_voltage_sensor_config_s {
    uint32_t r1_value;
    uint32_t r2_value;
    uint32_t scale_factor;
} hmo_voltage_sensor_config_t;

voltage_sensor_err_t hmo_voltage_sensor_create(hmo_voltage_sensor_config_t *config ,voltage_sensor_handle_t *handle);

#endif // HMO_VOLTAGE_SENSOR_H__