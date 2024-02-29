#include "crc32.hpp"

uint32_t Crc::Crc32B(const uint8_t *data, const size_t size)
{

    uint32_t crc = 0xFFFFFFFF;

    for (size_t i = 0; i < size; i++)
    {
        char ch = data[i];
        for (size_t j = 0; j < 8; j++)
        {
            uint32_t b = (ch ^ crc) & 1;
            crc >>= 1;
            if (b)
            {
                // Reversed representation (LSB first implementation)
                crc = crc ^ 0xEDB88320;
                // Normal representation (MSB first implementation)
                // crc = crc ^ 0x04C11DB7;
            }
            ch >>= 1;
        }
    }

    return ~crc;
}