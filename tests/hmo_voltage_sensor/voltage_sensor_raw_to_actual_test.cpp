extern "C"
{
#include "voltage_sensor.h"
#include "hmo_voltage_sensor.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(hmo_voltage_sensor_raw_to_actual)
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

TEST(hmo_voltage_sensor_raw_to_actual, rawToActualNullHandle)
{
    uint32_t actual;
    uint32_t raw = 0;
    voltage_sensor_err_t result = voltage_sensor_raw_to_actual(NULL, raw, &actual);
    CHECK_EQUAL(VOLTAGE_SENSOR_INVALID_ARG, result);
}

TEST(hmo_voltage_sensor_raw_to_actual, rawToActualNullActual)
{
    uint32_t raw = 0;
    voltage_sensor_err_t result = voltage_sensor_raw_to_actual(sensor, raw, NULL);
    CHECK_EQUAL(VOLTAGE_SENSOR_INVALID_ARG, result);
}

TEST(hmo_voltage_sensor_raw_to_actual, rawToActualZeroInput)
{
    uint32_t actual;
    uint32_t actual_expected = 0;
    uint32_t raw = 0;
    voltage_sensor_err_t result = voltage_sensor_raw_to_actual(sensor, raw, &actual);
    CHECK_EQUAL(VOLTAGE_SENSOR_OK, result);
    CHECK_EQUAL(actual_expected, actual);
}

TEST(hmo_voltage_sensor_raw_to_actual, rawToActualTypicalInput)
{
    uint32_t actual;
    uint32_t scale_factor = voltage_sensor_get_scale_factor(sensor);
    uint32_t actual_expected = 16.5 * scale_factor;
    uint32_t raw = 1.5 * scale_factor;
    voltage_sensor_err_t result = voltage_sensor_raw_to_actual(sensor, raw, &actual);
    CHECK_EQUAL(VOLTAGE_SENSOR_OK, result);
    CHECK_EQUAL(actual_expected, actual);
}

TEST(hmo_voltage_sensor_raw_to_actual, rawToActualMaxInput)
{
    uint32_t actual;
    uint32_t scale_factor = voltage_sensor_get_scale_factor(sensor);
    uint32_t actual_expected = 60.5 * scale_factor;
    uint32_t raw = 5.5 * scale_factor;
    voltage_sensor_err_t result = voltage_sensor_raw_to_actual(sensor, raw, &actual);
    CHECK_EQUAL(VOLTAGE_SENSOR_OK, result);
    CHECK_EQUAL(actual_expected, actual);
}