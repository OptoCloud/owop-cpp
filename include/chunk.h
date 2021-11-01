#ifndef OWOPCPP_CHUNK_H
#define OWOPCPP_CHUNK_H

#include "pixel.h"
#include "constants.h"

#include <span>
#include <array>
#include <shared_mutex>
#include <atomic>
#include <cstdint>

namespace OWOP {
struct Chunk
{
    typedef std::array<std::uint8_t, OWOP::Internal::CHUNK_BYTES> ChunkData;

    Chunk();
    Chunk(const OWOP::Chunk& other);
    Chunk(OWOP::Chunk&& other) noexcept;
    Chunk(std::span<const Pixel, OWOP::Internal::CHUNK_PIXELS> pixels, bool isProtected);
    Chunk(std::span<const std::uint8_t, OWOP::Internal::CHUNK_BYTES> data, bool isProtected);

    OWOP::Pixel getPixel(std::uint8_t x, std::uint8_t y) const;
    bool setPixel(std::uint8_t x, std::uint8_t y, const OWOP::Pixel& pixel);
    bool fill(OWOP::Pixel color) noexcept;

    void protect() noexcept;
    void unprotect() noexcept;
    bool isProtected() const noexcept;

    std::span<const std::uint8_t, OWOP::Internal::CHUNK_BYTES> data() const noexcept;

    OWOP::Chunk& operator=(const OWOP::Chunk& other);
    OWOP::Chunk& operator=(OWOP::Chunk&& other) noexcept;
private:
    ChunkData m_data;
    std::atomic_uint8_t m_flags;
    mutable std::shared_mutex m_mtx;
};
}

#endif // OWOPCPP_CHUNK_H
