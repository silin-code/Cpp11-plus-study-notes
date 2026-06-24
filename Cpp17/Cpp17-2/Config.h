#pragma once
// config.h
#pragma once
#include <string_view>

namespace mylib {
    inline constexpr size_t MAX_BUFFER_SIZE = 4096;
    inline constexpr std::string_view DEFAULT_NAME = "default";
    inline const Version CURRENT_VERSION{ 1, 0, 0 };
}