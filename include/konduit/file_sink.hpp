// SPDX-License-Identifier: MIT

#pragma once

#include <konduit/byte_view.hpp>
#include <filesystem>

namespace konduit {

[[nodiscard]] auto write_file(std::filesystem::path const& path, byte_view_t bytes) -> bool;

} // namespace konduit
