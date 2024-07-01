extern "C"
{
#include "voltage_sensor.h"
#include "hmo_voltage_sensor.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(hmo_voltage_sensor_destroy)
{
    voltage_sensor_handle_t sensor; // Default sensor instance
    hmo_voltage_sensor_config_t config;

    void setup()
    {
        // Initialize configuration
        config.r1_value = 1000000;
        config.r2_value = 100000;
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

TEST(hmo_voltage_sensor_destroy, DestroyNullHandle)
{
    CHECK_EQUAL(VOLTAGE_SENSOR_INVALID_ARG, voltage_sensor_destroy(NULL));
}

TEST(hmo_voltage_sensor_destroy, Destroy)
{
    voltage_sensor_handle_t destroy_sensor;
    hmo_voltage_sensor_create(&config, &destroy_sensor);

    CHECK_EQUAL(VOLTAGE_SENSOR_OK, voltage_sensor_destroy(destroy_sensor));
}