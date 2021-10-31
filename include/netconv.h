#ifndef NETCONV_H
#define NETCONV_H

#include <bit>
#include <utility>
#include <climits>
#include <cstdint>

#define BEAUTIFUL_BSWAP(intrin_f, int_t)                             \
    template<typename T>                                             \
    requires (std::is_arithmetic_v<T> && sizeof(T) == sizeof(int_t)) \
    [[nodiscard]] inline constexpr T constexpr_bswap(T v) {          \
        return std::bit_cast<T>(intrin_f(std::bit_cast<int_t>(v)));  \
    }

#if defined(__GNUC__) or defined(__clang__)

BEAUTIFUL_BSWAP(__builtin_bswap16, std::uint16_t)
BEAUTIFUL_BSWAP(__builtin_bswap32, std::uint32_t)
BEAUTIFUL_BSWAP(__builtin_bswap64, std::uint64_t)

#elif defined(_MSC_VER)

BEAUTIFUL_BSWAP(_byteswap_ushort, std::uint16_t)
BEAUTIFUL_BSWAP(_byteswap_ulong,  std::uint32_t)
BEAUTIFUL_BSWAP(_byteswap_uint64, std::uint64_t)

#else

#include <array>
#include <algorithm>

template<typename T>
requires std::is_arithmetic_v<T>
[[nodiscard]] inline constexpr T constexpr_bswap(T v) {
    auto bytes = std::bit_cast<std::array<unsigned char, sizeof(T)>>(v);
    std::reverse(bytes.data(), bytes.data() + bytes.size());
    return std::bit_cast<T>(bytes);
}

#endif

template <typename T>
requires std::is_arithmetic_v<T>
constexpr T netconv(T v) {
    if constexpr (std::endian::native == std::endian::big || sizeof(T) == 1) {
        return v;
    } else {
        return constexpr_bswap(v);
    }
}

#endif // NETCONV_H
