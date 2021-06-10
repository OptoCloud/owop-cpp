#include "chunk.h"

enum ChunkFlags : std::uint8_t
{
    Protected = 1 << 0,
};

constexpr std::uint32_t getPixelIndex(std::uint8_t x, std::uint8_t y) {
    if (x >= OWOP::CHUNK_SIZE || y >= OWOP::CHUNK_SIZE) {
        throw "Beyond buffer exception TODO"; // TODO: fix this
    }

    return (OWOP::CHUNK_SIZE * y + x) * OWOP::Internal::PIXEL_BYTES;
}

OWOP::Chunk::Chunk()
    : m_data{ 0 }
    , m_flags(0)
{
}

OWOP::Chunk::Chunk(const OWOP::Chunk& other)
    : m_data(other.m_data)
    , m_flags(other.m_flags)
{
}

OWOP::Chunk::Chunk(std::span<const OWOP::Color, OWOP::Internal::CHUNK_PIXELS> pixels, bool isProtected)
    : m_flags(0)
{
    for (std::size_t index = 0; index < OWOP::Internal::CHUNK_PIXELS; index++) {
        auto pixelData = pixels[index].data();
        std::copy(pixelData.begin(), pixelData.end(), m_data.begin() + index);
    }

    if (isProtected) {
        m_flags |= ChunkFlags::Protected;
    }
}

OWOP::Chunk::Chunk(std::span<const std::uint8_t, OWOP::Internal::CHUNK_BYTES> data, bool isProtected)
    : m_flags(0)
{
    std::copy(data.begin(), data.end(), m_data.begin());

    if (isProtected) {
        m_flags |= ChunkFlags::Protected;
    }
}

OWOP::Color OWOP::Chunk::getPixel(std::uint8_t x, std::uint8_t y) const
{
    auto index = getPixelIndex(x, y);

    OWOP::Color pixel;

    auto beg = m_data.begin() + index;
    auto end = beg + OWOP::Internal::PIXEL_BYTES;

    std::copy(beg, end, pixel.data().begin());

    return pixel;
}

void OWOP::Chunk::setPixel(std::uint8_t x, std::uint8_t y, OWOP::Color pixel)
{
    auto index = getPixelIndex(x, y);

    auto pixelData = pixel.data();

    std::copy(pixelData.begin(), pixelData.end(), m_data.begin() + index);
}

void OWOP::Chunk::fill(OWOP::Color color)
{
    auto colorDat = color.data();

    for (std::uint16_t i = 0; i < OWOP::Internal::CHUNK_BYTES;) {
        m_data[i++] = colorDat[0];
        m_data[i++] = colorDat[1];
        m_data[i++] = colorDat[2];
    }
}

void OWOP::Chunk::protect() noexcept
{
    m_flags |= ChunkFlags::Protected;
}

void OWOP::Chunk::unprotect() noexcept
{
    m_flags &= ~ChunkFlags::Protected;
}

bool OWOP::Chunk::isProtected() const noexcept
{
    return (m_flags & ChunkFlags::Protected) != 0;
}

OWOP::Chunk& OWOP::Chunk::operator=(const OWOP::Chunk& other)
{
    this->m_data = other.m_data;
    this->m_flags = other.m_flags;
    return *this;
}
