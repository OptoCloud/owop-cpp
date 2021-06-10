#ifndef OWOPCPP_PIXEL_H
#define OWOPCPP_PIXEL_H

#include "constants.h"

#include <span>
#include <array>
#include <cstdint>

namespace OWOP {
struct Color
{
public:
    typedef std::array<std::uint8_t, OWOP::Internal::PIXEL_BYTES> PixelData;

    Color();
    Color(const OWOP::Color& other);
    Color(std::uint8_t r, std::uint8_t g, std::uint8_t b);
    Color(std::span<const std::uint8_t, OWOP::Internal::PIXEL_BYTES> data);

    std::uint8_t getR() const noexcept;
    std::uint8_t getG() const noexcept;
    std::uint8_t getB() const noexcept;

    void setR(std::uint8_t value) noexcept;
    void setG(std::uint8_t value) noexcept;
    void setB(std::uint8_t value) noexcept;

    std::span<std::uint8_t, OWOP::Internal::PIXEL_BYTES> data() noexcept;
    std::span<const std::uint8_t, OWOP::Internal::PIXEL_BYTES> data() const noexcept;

    OWOP::Color& operator=(const OWOP::Color& other);
private:
    PixelData m_data;
};
}

#endif // OWOPCPP_PIXEL_H
