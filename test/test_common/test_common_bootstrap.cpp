#include <unity.h>
#include "test_common_crc16.hpp"

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void RUN_UNITY_TESTS()
{
    UNITY_BEGIN();
    RUN_TEST(test_Crc16);
    RUN_TEST(test_AddCrc);
    RUN_TEST(test_ValidateCrc);
    UNITY_END();
}

#ifdef ARDUINO

#include <Arduino.h>
void setup()
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    RUN_UNITY_TESTS();
}

void loop()
{
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);
}

#else

int main(int argc, char **argv)
{
    RUN_UNITY_TESTS();
    return 0;
}

#endif
