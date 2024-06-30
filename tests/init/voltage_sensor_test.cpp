extern "C"
{
#include "voltage_sensor.h"
#include "hmo_voltage_sensor.h"
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

    voltage_sensor_err_t result = hmo_voltage_sensor_create(&sensor);

    CHECK_EQUAL(VOLTAGE_SENSOR_OK, result);

    voltage_sensor_destroy(sensor);
}

