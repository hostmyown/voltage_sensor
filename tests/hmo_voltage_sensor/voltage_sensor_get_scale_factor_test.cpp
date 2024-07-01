extern "C"
{
#include "voltage_sensor.h"
#include "hmo_voltage_sensor.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(hmo_voltage_sensor_get_scale_factor)
{
    voltage_sensor_handle_t sensor;
    hmo_voltage_sensor_config_t config = {
        .r1_value = 10000000,
        .r2_value = 1000000,
        .scale_factor = 1000,
    };


    void setup()
    {
        hmo_voltage_sensor_create(&config, &sensor);
    }

    void teardown()
    {
        voltage_sensor_destroy(sensor);
    }
};

TEST(hmo_voltage_sensor_get_scale_factor, ScaleFactorInit)
{
    CHECK_EQUAL(config.scale_factor, voltage_sensor_get_scale_factor(sensor));
}

