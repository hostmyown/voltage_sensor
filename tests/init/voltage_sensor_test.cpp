extern "C"
{
#include "voltage_sensor.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(voltage_sensor_init)
{
    void setup()
    {

    }

    void teardown()
    {

    }
};

TEST(voltage_sensor_init, Create)
{
    voltage_sensor_handle_t sensor;
    voltage_sensor_config_t config;

    voltage_sensor_err_t expected_result = VOLTAGE_SENSOR_OK;
    voltage_sensor_err_t result = voltage_sensor_create(&config, &sensor);

    CHECK_EQUAL(expected_result, result);

    voltage_sensor_destroy(sensor);
}

