#ifndef OWOPCPP_TOOLTYPE_H
#define OWOPCPP_TOOLTYPE_H

#include <cstdint>

namespace OWOP {
enum class ToolType : std::uint8_t {
    Pencil,
    Move,
    saasf,
    dsf,
};
}

#endif // OWOPCPP_TOOLTYPE_H
