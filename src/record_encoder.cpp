// SPDX-License-Identifier: MIT

#include <konduit/record_encoder.hpp>

namespace konduit {

namespace {

auto write_u32_le(std::uint32_t value, mutable_byte_view_t output) noexcept -> void
{
    output[0] = static_cast<std::byte>(value >> 0U);
    output[1] = static_cast<std::byte>(value >> 8U);
    output[2] = static_cast<std::byte>(value >> 16U);
    output[3] = static_cast<std::byte>(value >> 24U);
}

} // namespace

auto record_encoder_t::encode_header(record_header_t const header, mutable_byte_view_t const output) const noexcept
    -> bool
{
    constexpr auto encoded_size = std::size_t{8};
    if(output.size() < encoded_size) return false;

    write_u32_le(header.type, output.subspan(0, 4));
    write_u32_le(header.payload_size, output.subspan(4, 4));
    return true;
}

} // namespace konduit
