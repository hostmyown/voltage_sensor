extern "C"
{
#include "voltage_sensor.h"
#include "hmo_voltage_sensor.h"
#include "adc.h" // Include the ADC header
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

TEST_GROUP(hmo_voltage_sensor_integration)
{
    void setup() {

    }

    void teardown() {
        mock().clear(); // Clear the mock expectations
    }
};

TEST(hmo_voltage_sensor_integration, CompleteWorkFlow)
{
    // Set expectation for adc_read to return a specific value
    mock().expectOneCall("adc_read").andReturnValue(1500);

    // Create a sensor
    voltage_sensor_handle_t sensor;
    hmo_voltage_sensor_config_t config = {
        .r1_value = 1000000,
        .r2_value = 100000,
        .scale_factor = 1000,
    };

    voltage_sensor_err_t result = hmo_voltage_sensor_create(&config, &sensor);
    CHECK_EQUAL(VOLTAGE_SENSOR_OK, result);

    // Get the scale factor
    uint32_t scale_factor = voltage_sensor_get_scale_factor(sensor);
    CHECK_EQUAL(config.scale_factor, scale_factor);

    // Read the ADC
    uint32_t expected_raw_value = 1500;
    uint32_t raw_value;
    result = voltage_sensor_read(sensor, &raw_value);
    CHECK_EQUAL(VOLTAGE_SENSOR_OK, result);
    CHECK_EQUAL(expected_raw_value, raw_value);

    // Convert raw to actual
    uint32_t expected_actual_value = 16500;
    uint32_t actual_value;
    result = voltage_sensor_raw_to_actual(sensor, raw_value, &actual_value);
    CHECK_EQUAL(VOLTAGE_SENSOR_OK, result);
    CHECK_EQUAL(expected_actual_value, actual_value);

    // Destroy the sensor
    result = voltage_sensor_destroy(sensor);
    sensor = NULL;
    CHECK_EQUAL(VOLTAGE_SENSOR_OK, result);
};

TEST(hmo_voltage_sensor_integration, CompleteWorkFlowMultipleSensors)
{
    // Create a sensor
    voltage_sensor_handle_t sensor1;
    voltage_sensor_handle_t sensor2;
    hmo_voltage_sensor_config_t config = {
        .r1_value = 1000000,
        .r2_value = 100000,
        .scale_factor = 1000,
    };

    voltage_sensor_err_t result;

    result = hmo_voltage_sensor_create(&config, &sensor1);
    CHECK_EQUAL(VOLTAGE_SENSOR_OK, result);

    result = hmo_voltage_sensor_create(&config, &sensor2);
    CHECK_EQUAL(VOLTAGE_SENSOR_OK, result);

    // Get the scale factor
    uint32_t scale_factor = voltage_sensor_get_scale_factor(sensor1);
    CHECK_EQUAL(config.scale_factor, scale_factor);

    // Read the ADC for sensor 1
    uint32_t expected_raw_value1 = 1500;
    mock().expectOneCall("adc_read").andReturnValue(expected_raw_value1);
    uint32_t raw_value1;
    result = voltage_sensor_read(sensor1, &raw_value1);
    CHECK_EQUAL(VOLTAGE_SENSOR_OK, result);
    CHECK_EQUAL(expected_raw_value1, raw_value1);

    // Read the ADC for sensor 1
    uint32_t expected_raw_value2 = 1000;
    mock().expectOneCall("adc_read").andReturnValue(expected_raw_value2);
    uint32_t raw_value2;
    result = voltage_sensor_read(sensor1, &raw_value2);
    CHECK_EQUAL(VOLTAGE_SENSOR_OK, result);
    CHECK_EQUAL(expected_raw_value2, raw_value2);

    // Convert raw to actual for sensor 1
    uint32_t expected_actual_value1 = 16500;
    uint32_t actual_value1;
    result = voltage_sensor_raw_to_actual(sensor1, raw_value1, &actual_value1);
    CHECK_EQUAL(VOLTAGE_SENSOR_OK, result);
    CHECK_EQUAL(expected_actual_value1, actual_value1);

    // Convert raw to actual for sensor 2
    uint32_t expected_actual_value2 = 11000;
    uint32_t actual_value2;
    result = voltage_sensor_raw_to_actual(sensor2, raw_value2, &actual_value2);
    CHECK_EQUAL(VOLTAGE_SENSOR_OK, result);
    CHECK_EQUAL(expected_actual_value2, actual_value2);

    // Destroy the sensor
    result = voltage_sensor_destroy(sensor1);
    sensor1 = NULL;
    CHECK_EQUAL(VOLTAGE_SENSOR_OK, result);

    result = voltage_sensor_destroy(sensor2);
    sensor2 = NULL;
    CHECK_EQUAL(VOLTAGE_SENSOR_OK, result);
}