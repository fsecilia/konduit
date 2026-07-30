// SPDX-License-Identifier: MIT

#pragma once

#include <cstddef>
#include <span>

namespace konduit {

using byte_view_t = std::span<std::byte const>;
using mutable_byte_view_t = std::span<std::byte>;

} // namespace konduit
