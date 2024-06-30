extern "C"
{
#include "voltage_sensor.h"
#include "hmo_voltage_sensor.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(hmo_voltage_sensor_raw_to_actual)
{
    voltage_sensor_handle_t sensor;
    hmo_voltage_sensor_config_t config = {1234, 5678};

    void setup()
    {
        hmo_voltage_sensor_create(&config, &sensor);
    }

    void teardown()
    {
        voltage_sensor_destroy(sensor);
    }
};

TEST(hmo_voltage_sensor_raw_to_actual, rawToActualNullHandleNull)
{
    uint32_t actual;
    uint32_t raw = 0;
    voltage_sensor_err_t result = voltage_sensor_raw_to_actual(NULL, raw, &actual);
    CHECK_EQUAL(VOLTAGE_SENSOR_INVALID_ARG, result);
}
