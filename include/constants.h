#ifndef OWOPCPP_CONSTANTS_H
#define OWOPCPP_CONSTANTS_H

#include "constexpr_math.h"

#include <cstdlib>
#include <cstdint>

namespace OWOP {
constexpr std::uint16_t CHUNK_SIZE = 16;
namespace Internal {
constexpr std::size_t PIXEL_BYTES  = 3; // RGB
constexpr std::size_t CHUNK_PIXELS = OWOP::Internal::Math::Pow(OWOP::CHUNK_SIZE, 2);
constexpr std::size_t CHUNK_BYTES  = OWOP::Internal::CHUNK_PIXELS * OWOP::Internal::PIXEL_BYTES;
}
}

#endif // OWOPCPP_CONSTANTS_H
