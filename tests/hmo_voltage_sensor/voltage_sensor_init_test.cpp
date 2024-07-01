extern "C"
{
#include "voltage_sensor.h"
#include "hmo_voltage_sensor.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(hmo_voltage_sensor_init)
{
    voltage_sensor_handle_t sensor; // Default sensor instance
    hmo_voltage_sensor_config_t config;

    void setup()
    {
        // Initialize configuration
        config.r1_value = 4321;
        config.r2_value = 8765;
        config.scale_factor = 100;

        // Create the default sensor with the configured values
        hmo_voltage_sensor_create(&config, &sensor);
    }

    void teardown()
    {
        // Destroy the sensor after each test case
        voltage_sensor_destroy(sensor);
    }
};

TEST(hmo_voltage_sensor_init, Create)
{
    voltage_sensor_handle_t sensor_create;
 
    voltage_sensor_err_t result = hmo_voltage_sensor_create(&config, &sensor_create);

    CHECK_EQUAL(VOLTAGE_SENSOR_OK, result);

    voltage_sensor_destroy(sensor_create);
}