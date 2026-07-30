// SPDX-License-Identifier: MIT

#pragma once

#include <konduit/byte_view.hpp>
#include <cstdint>

namespace konduit {

struct record_header_t
{
    std::uint32_t type;
    std::uint32_t payload_size;
};

class record_encoder_t
{
public:
    [[nodiscard]] auto encode_header(record_header_t header, mutable_byte_view_t output) const noexcept -> bool;
};

} // namespace konduit
