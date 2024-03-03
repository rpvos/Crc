#include "crc32.hpp"
#include <unity.h>
#include <string.h>

const uint32_t kTestset1[] = {0x01, 2583214201};
// const uint32_t kTestset2[] = {0x1, 2212294583};
// const uint8_t kTestset3[] = {0x01, 0x03, 0x00, 0x0C, 0x00, 0x01, 0x44, 0x09};
// const uint8_t kTestset4[] = {0x01, 0x03, 0x02, 0x00, 0x00, 0xB8, 0x44};
// const uint8_t kTestset5[] = {0x01, 0x03, 0x02, 0x00, 0x01, 0x79, 0x84};
const uint32_t kTestset6Incorrect[] = {1, 2, 3, 4, 5, 0xcbf53a1d};

const size_t kTestset1Size = sizeof(kTestset1) / sizeof(kTestset1[0]);
// const size_t kTestset2Size = sizeof(kTestset2) / sizeof(kTestset2[0]);
// const size_t kTestset3Size = sizeof(kTestset3) / sizeof(kTestset3[0]);
// const size_t kTestset4Size = sizeof(kTestset4) / sizeof(kTestset4[0]);
// const size_t kTestset5Size = sizeof(kTestset5) / sizeof(kTestset5[0]);
const size_t kTestset6Size = sizeof(kTestset6Incorrect) / sizeof(kTestset6Incorrect[0]);

void test_Crc32PerTestset(const uint32_t *testset, const size_t testset_size, bool outcome)
{
    size_t new_size = (testset_size - 1) * sizeof(uint32_t);
    uint8_t testset_with_modifications[new_size];
    memcpy(testset_with_modifications, testset, new_size);

    // uint32_t TestsetCrc = Crc::Crc32B(testset_with_modifications, new_size);
    uint32_t TestsetCrc = Crc::Crc32B(testset_with_modifications, new_size);
    // It is calculated with upper byte then lower byte
    // And in the dataset it is lower byte then upper byte
    uint32_t RealCrc = testset[testset_size - 1];

    if (outcome)
    {
        TEST_ASSERT_EQUAL_INT_MESSAGE(RealCrc, TestsetCrc, "Crc of testset do not match");
    }
    else
    {
        TEST_ASSERT_NOT_EQUAL_INT_MESSAGE(RealCrc, TestsetCrc, "Crc of testset do match when it should not");
    }
}

void test_Crc32(void)
{
    test_Crc32PerTestset(kTestset1, kTestset1Size, true);
    // test_Crc32PerTestset(kTestset2, kTestset2Size, true);
    // test_Crc32PerTestset(kTestset3, kTestset3Size, true);
    // test_Crc32PerTestset(kTestset4, kTestset4Size, true);
    // test_Crc32PerTestset(kTestset5, kTestset5Size, true);
    test_Crc32PerTestset(kTestset6Incorrect, kTestset6Size, false);
}
