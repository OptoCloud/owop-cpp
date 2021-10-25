#ifndef OWOPCPP_PIXEL_H
#define OWOPCPP_PIXEL_H

#ifdef COMPILE_GOAPI
#ifndef __cplusplus
#include <stdint.h>
#else
#include <cstdint>
extern "C" {
#endif // __cplusplus

struct CPixel {
    uint8_t data[3];
};

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // COMPILE_GOAPI

#ifdef __cplusplus

#include "constants.h"

#include <span>
#include <array>

namespace OWOP {
struct Pixel
{
    Pixel() : m_data{std::byte(255)} {}
    Pixel(std::uint8_t r, std::uint8_t g, std::uint8_t b) : m_data{std::byte(r),std::byte(g),std::byte(b)} {}

    std::uint8_t r() const noexcept { return static_cast<std::uint8_t>(m_data[0]); }
    std::uint8_t g() const noexcept { return static_cast<std::uint8_t>(m_data[1]); }
    std::uint8_t b() const noexcept { return static_cast<std::uint8_t>(m_data[2]); }
    void setR(std::uint8_t v) noexcept { m_data[0] = static_cast<std::byte>(v); }
    void setG(std::uint8_t v) noexcept { m_data[1] = static_cast<std::byte>(v); }
    void setB(std::uint8_t v) noexcept { m_data[2] = static_cast<std::byte>(v); }

    constexpr std::span<std::byte, OWOP::Internal::PIXEL_BYTES> data() noexcept { return m_data; };
    constexpr std::span<const std::byte, OWOP::Internal::PIXEL_BYTES> data() const noexcept { return m_data; };

#ifdef COMPILE_GOAPI
    constexpr CPixel cpixel() const noexcept { return CPixel{r(),g(),b()}; }
#endif // COMPILE_GOAPI
private:
    std::array<std::byte, OWOP::Internal::PIXEL_BYTES> m_data;
};
}

#ifdef COMPILE_GOAPI
static_assert (sizeof(CPixel) == sizeof(OWOP::Pixel), "GO API differs in size for Pixel struct!");
#endif // COMPILE_GOAPI

#endif // __cplusplus

#endif // OWOPCPP_PIXEL_H
