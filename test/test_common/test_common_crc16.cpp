#include "crc16.hpp"
#include <unity.h>
#include <string.h>

const size_t kTestset1Size = 11;
const size_t kTestset2Size = 8;
const size_t kTestset3Size = 8;
const size_t kTestset4Size = 7;
const size_t kTestset5Size = 7;
const size_t kTestset6Size = 7;
const uint8_t kTestset1[kTestset1Size] = {0x01, 0x10, 0x00, 0x0A, 0x00, 0x01, 0x02, 0x00, 0x01, 0x67, 0x3A};
const uint8_t kTestset2[kTestset2Size] = {0x01, 0x10, 0x00, 0x0A, 0x00, 0x01, 0x21, 0xCB};
const uint8_t kTestset3[kTestset3Size] = {0x01, 0x03, 0x00, 0x0C, 0x00, 0x01, 0x44, 0x09};
const uint8_t kTestset4[kTestset4Size] = {0x01, 0x03, 0x02, 0x00, 0x00, 0xB8, 0x44};
const uint8_t kTestset5[kTestset5Size] = {0x01, 0x03, 0x02, 0x00, 0x01, 0x79, 0x84};
const uint8_t kTestset6Incorrect[kTestset6Size] = {0x01, 0x03, 0x02, 0x00, 0x01, 0x79, 0x85};

void test_Crc16PerTestset(const uint8_t *testset, const size_t testset_size, bool outcome)
{
    uint8_t testset_with_modifications[testset_size - 2];
    memcpy(testset_with_modifications, testset, testset_size - 2);

    uint16_t TestsetCrc = Crc::Crc16Modbus(testset_with_modifications, testset_size - 2);
    // It is calculated with upper byte then lower byte
    // And in the dataset it is lower byte then upper byte
    uint16_t RealCrc = testset[testset_size - 1] << 8 | testset[testset_size - 2];

    if (outcome)
    {
        TEST_ASSERT_EQUAL_INT_MESSAGE(RealCrc, TestsetCrc, "Crc of testset do not match");
    }
    else
    {
        TEST_ASSERT_NOT_EQUAL_INT_MESSAGE(RealCrc, TestsetCrc, "Crc of testset do match when it should not");
    }
}

void test_Crc16(void)
{
    test_Crc16PerTestset(kTestset1, kTestset1Size, true);
    test_Crc16PerTestset(kTestset2, kTestset2Size, true);
    test_Crc16PerTestset(kTestset3, kTestset3Size, true);
    test_Crc16PerTestset(kTestset4, kTestset4Size, true);
    test_Crc16PerTestset(kTestset5, kTestset5Size, true);
    test_Crc16PerTestset(kTestset6Incorrect, kTestset6Size, false);
}

void test_ValidateCrcPerTestset(const uint8_t *testset, const size_t testset_size, bool outcome)
{
    if (outcome)
    {
        TEST_ASSERT_TRUE_MESSAGE(Crc::ValidateCrc16Modbus(testset, testset_size, false), "Validate did not return true");
    }
    else
    {
        TEST_ASSERT_FALSE_MESSAGE(Crc::ValidateCrc16Modbus(testset, testset_size, false), "Validate did not return false");
    }
}

void test_ValidateCrc(void)
{
    test_ValidateCrcPerTestset(kTestset1, kTestset1Size, true);
    test_ValidateCrcPerTestset(kTestset2, kTestset2Size, true);
    test_ValidateCrcPerTestset(kTestset3, kTestset3Size, true);
    test_ValidateCrcPerTestset(kTestset4, kTestset4Size, true);
    test_ValidateCrcPerTestset(kTestset5, kTestset5Size, true);
    test_ValidateCrcPerTestset(kTestset6Incorrect, kTestset6Size, false);
}

void test_AddCrcPerTestset(const uint8_t *testset, const size_t testset_size, bool outcome)
{
    uint8_t testset_without_crc[testset_size - 2];
    memcpy(testset_without_crc, testset, testset_size - 2);

    uint8_t testset_with_crc[testset_size];
    Crc::AddCrc16Modbus(testset_without_crc, testset_with_crc, testset_size - 2, false);

    if (outcome)
    {
        TEST_ASSERT_EQUAL_CHAR_ARRAY_MESSAGE(testset, testset_with_crc, testset_size, "Crc not added correctly");
    }
    else
    {
        // Test if set is correct
        size_t amount_correct = testset_size;
        for (size_t i = 0; i < testset_size; i++)
        {
            if (testset[i] == testset_with_crc[i])
            {
                amount_correct--;
            }
        }

        if (amount_correct == 0)
        {
            TEST_FAIL_MESSAGE("Crc not added correctly");
        }
    }
}

void test_AddCrc(void)
{
    test_AddCrcPerTestset(kTestset1, kTestset1Size, true);
    test_AddCrcPerTestset(kTestset2, kTestset2Size, true);
    test_AddCrcPerTestset(kTestset3, kTestset3Size, true);
    test_AddCrcPerTestset(kTestset4, kTestset4Size, true);
    test_AddCrcPerTestset(kTestset5, kTestset5Size, true);
    test_AddCrcPerTestset(kTestset6Incorrect, kTestset6Size, false);
}
