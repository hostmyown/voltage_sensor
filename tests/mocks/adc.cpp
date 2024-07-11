#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "adc.h"

uint32_t adc_read() {
    return mock().actualCall("adc_read").returnUnsignedIntValue();
}