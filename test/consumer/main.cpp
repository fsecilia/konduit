// SPDX-License-Identifier: MIT

#include <konduit/record_encoder.hpp>
#include <array>

int main()
{
    auto bytes = std::array<std::byte, 8>{};
    auto const encoder = konduit::record_encoder_t{};
    auto const encoded = encoder.encode_header(
        konduit::record_header_t{.type = 7, .payload_size = 42},
        bytes);

    return encoded ? 0 : 1;
}
