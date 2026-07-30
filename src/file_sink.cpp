// SPDX-License-Identifier: MIT

#include <konduit/file_sink.hpp>
#include <fstream>

namespace konduit {

auto write_file(std::filesystem::path const& path, byte_view_t const bytes) -> bool
{
    auto output = std::ofstream{path, std::ios::binary | std::ios::trunc};
    if(!output) return false;

    output.write(reinterpret_cast<char const*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
    return output.good();
}

} // namespace konduit
