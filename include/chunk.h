#ifndef OWOPCPP_CHUNK_H
#define OWOPCPP_CHUNK_H

#include "color.h"
#include "constants.h"

#include <span>
#include <array>
#include <cstdint>

namespace OWOP {
struct Chunk
{
public:
    typedef std::array<std::uint8_t, OWOP::Internal::CHUNK_BYTES> ChunkData;

    Chunk();
    Chunk(const OWOP::Chunk& other);
    Chunk(std::span<const Color, OWOP::Internal::CHUNK_PIXELS> pixels, bool isProtected);
    Chunk(std::span<const std::uint8_t, OWOP::Internal::CHUNK_BYTES> data, bool isProtected);

    OWOP::Color getPixel(std::uint8_t x, std::uint8_t y) const;
    void setPixel(std::uint8_t x, std::uint8_t y, OWOP::Color pixel);
    void fill(OWOP::Color color);

    void protect() noexcept;
    void unprotect() noexcept;
    bool isProtected() const noexcept;

    std::span<const std::uint8_t, OWOP::Internal::CHUNK_BYTES> data() const noexcept;

    OWOP::Chunk& operator=(const OWOP::Chunk& other);
private:
    ChunkData m_data;
    std::uint8_t m_flags;
};
}

#endif // OWOPCPP_CHUNK_H
