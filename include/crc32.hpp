/**
 * @file crc32.hpp
 * @author rpvos (mr.rv.asd@gmail.com)
 * @brief Standard way of calculation crc32
 * @version 0.1
 * @date 2024-02-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#if !defined(CRC32_HPP_)
#define CRC32_HPP_

#include <stdint.h>
#include <stddef.h>

namespace Crc
{
    uint32_t Crc32B(const uint8_t *data, const size_t size);
} // namespace Crc

#endif // CRC32_HPP_
