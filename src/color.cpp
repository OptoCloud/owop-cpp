#include "color.h"

OWOP::Color::Color()
    : m_data{ std::byte(0) }
{
}

OWOP::Color::Color(const OWOP::Color& other)
    : m_data(other.m_data)
{
}

OWOP::Color::Color(std::uint8_t r, std::uint8_t g, std::uint8_t b)
    : m_data{ std::byte(r), std::byte(g), std::byte(b) }
{
}

OWOP::Color::Color(std::span<const std::byte, OWOP::Internal::PIXEL_BYTES> data)
{
    std::copy(data.begin(), data.end(), m_data.begin());
}

std::uint8_t OWOP::Color::getR() const noexcept
{
    return (std::uint8_t)m_data[0];
}

std::uint8_t OWOP::Color::getG() const noexcept
{
    return (std::uint8_t)m_data[1];
}

std::uint8_t OWOP::Color::getB() const noexcept
{
    return (std::uint8_t)m_data[2];
}

void OWOP::Color::setR(std::uint8_t value) noexcept
{
    m_data[0] = (std::byte)value;
}

void OWOP::Color::setG(std::uint8_t value) noexcept
{
    m_data[1] = (std::byte)value;
}

void OWOP::Color::setB(std::uint8_t value) noexcept
{
    m_data[2] = (std::byte)value;
}

std::span<std::byte, OWOP::Internal::PIXEL_BYTES> OWOP::Color::data() noexcept
{
    return m_data;
}

std::span<const std::byte, OWOP::Internal::PIXEL_BYTES> OWOP::Color::data() const noexcept
{
    return m_data;
}

OWOP::Color& OWOP::Color::operator=(const OWOP::Color& other)
{
    this->m_data = other.m_data;
    return *this;
}
