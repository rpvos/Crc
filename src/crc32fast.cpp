#include "crc32fast.hpp"

uint32_t crc32_table[256];

void Crc::BuildCrc32BTable(void)
{
    for (uint32_t i = 0; i < 256; i++)
    {
        uint32_t ch = i;
        uint32_t crc = 0;
        for (size_t j = 0; j < 8; j++)
        {
            uint32_t b = (ch ^ crc) & 1;
            crc >>= 1;
            if (b)
                crc = crc ^ 0xEDB88320;
            ch >>= 1;
        }
        crc32_table[i] = crc;
    }
}

uint32_t Crc::Crc32BFast(const uint8_t *data, const size_t size)
{
    uint32_t crc = 0xFFFFFFFF;

    for (size_t i = 0; i < size; i++)
    {
        char ch = data[i];
        uint32_t t = (ch ^ crc) & 0xFF;
        crc = (crc >> 8) ^ crc32_table[t];
    }

    return ~crc;
}