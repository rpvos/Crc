#if !defined(CRC16_HPP_)
#define CRC16_HPP_

#include <stdint.h>
#include <stddef.h>

namespace Crc
{
    uint16_t Crc16Modbus(const uint8_t *data, const size_t size);
    bool ValidateCrc16Modbus(const uint8_t *message, const size_t messageLength, bool most_significant_bit_first = true);

    /**
     * @brief Function used to add crc to a message
     *
     * @param message_without_crc source
     * @param message_with_crc destination array that will be used to store message with crc
     * @param message_length_without_crc
     */
    void AddCrc16Modbus(const uint8_t *message_without_crc, uint8_t *message_with_crc, const size_t message_length_without_crc, bool most_significant_bit_first = true);
} // namespace Crc

#endif // CRC16_HPP_