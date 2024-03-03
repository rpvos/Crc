/**
 * @file crc32fast.hpp
 * @author rpvos (mr.rv.asd@gmail.com)
 * @brief Faster version by usage of lookup table
 * @version 0.1
 * @date 2024-02-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#if !defined(CRC32_FAST_HPP_)
#define CRC32_FAST_HPP_

#include <stdint.h>
#include <stddef.h>

namespace Crc
{
    /**
     * @brief Builds table used to get crc32-b fast
     *
     */
    void BuildCrc32BTable();

    /**
     * @brief Calculate fast crc32-b thanks to lookup table
     *
     * @param data array for crc
     * @param size length of array
     * @return uint32_t crc value
     */
    uint32_t Crc32BFast(const uint8_t *data, const size_t size);
} // namespace Crc

#endif // CRC32_FAST_HPP_
