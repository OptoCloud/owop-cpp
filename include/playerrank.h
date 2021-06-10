#ifndef OWOPCPP_PLAYERRANK_H
#define OWOPCPP_PLAYERRANK_H

#include <cstdint>

namespace OWOP {
enum class PlayerRank : std::uint8_t {
    None      = 0,
    User      = 1,
    Moderator = 2,
    Admin     = 3,
    ENUM_LEN  = 4,
};
}

#endif // OWOPCPP_PLAYERRANK_H
