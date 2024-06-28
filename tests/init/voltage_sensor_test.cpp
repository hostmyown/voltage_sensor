extern "C"
{
#include "voltage_sensor.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(voltage_sensor_init)
{
    voltage_sensor_handle_t sensor;

    void setup()
    {
        voltage_sensor_config_t config;

        voltage_sensor_create(&config, &sensor);
    }

    void teardown()
    {
        voltage_sensor_destroy(sensor);
    }
};

TEST(voltage_sensor_init, Create)
{
    FAIL("Start here");
}

