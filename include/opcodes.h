#ifndef OWOPCPP_OPCODES_H
#define OWOPCPP_OPCODES_H

namespace OWOP {
enum class OpCodes {
    SetId          = 0,
    WorldUpdate    = 1,
    ChunkLoad      = 2,
    Teleport       = 3,
    SetRank        = 4,
    Captcha        = 5,
    SetPQuota      = 6,
    ChunkProtected = 7,
};
}

#endif // OWOPCPP_OPCODES_H
