extern "C"
{
#include "voltage_sensor.h"
#include "hmo_voltage_sensor.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(hmo_voltage_sensor_read)
{
    voltage_sensor_handle_t sensor;
    hmo_voltage_sensor_config_t config = {
        .r1_value = 98765,
        .r2_value = 41873,
        .scale_factor = 10000,
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

TEST(hmo_voltage_sensor_read, readNullHandleNull)
{
    uint32_t value;
    voltage_sensor_err_t result = voltage_sensor_read(NULL, &value);
    CHECK_EQUAL(VOLTAGE_SENSOR_INVALID_ARG, result);
}


TEST(hmo_voltage_sensor_read, readNullValueNull)
{
    voltage_sensor_err_t result = voltage_sensor_read(sensor, NULL);
    CHECK_EQUAL(VOLTAGE_SENSOR_INVALID_ARG, result);
}
