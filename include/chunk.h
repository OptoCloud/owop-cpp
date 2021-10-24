#ifndef OWOPCPP_CHUNK_H
#define OWOPCPP_CHUNK_H

#include "color.h"
#include "constants.h"

#include <span>
#include <array>
#include <shared_mutex>
#include <atomic>
#include <cstdint>

namespace OWOP {
struct Chunk
{
    typedef std::array<std::byte, OWOP::Internal::CHUNK_BYTES> ChunkData;

    Chunk();
    Chunk(const OWOP::Chunk& other);
    Chunk(OWOP::Chunk&& other) noexcept;
    Chunk(std::span<const Color, OWOP::Internal::CHUNK_PIXELS> pixels, bool isProtected);
    Chunk(std::span<const std::byte, OWOP::Internal::CHUNK_BYTES> data, bool isProtected);

    OWOP::Color getPixel(std::uint8_t x, std::uint8_t y) const;
    bool setPixel(std::uint8_t x, std::uint8_t y, const OWOP::Color& pixel);
    bool fill(OWOP::Color color) noexcept;

    void protect() noexcept;
    void unprotect() noexcept;
    bool isProtected() const noexcept;

    std::span<const std::byte, OWOP::Internal::CHUNK_BYTES> data() const noexcept;

    OWOP::Chunk& operator=(const OWOP::Chunk& other);
    OWOP::Chunk& operator=(OWOP::Chunk&& other) noexcept;
private:
    ChunkData m_data;
    std::atomic_uint8_t m_flags;
    mutable std::shared_mutex m_mtx;
};
}

#endif // OWOPCPP_CHUNK_H
