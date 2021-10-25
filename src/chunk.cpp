#include "chunk.h"

#include <mutex>

enum ChunkFlags : std::uint8_t
{
    Protected = 1 << 0,
};

constexpr std::uint32_t GetPixelIndex(std::uint8_t x, std::uint8_t y) {
    return (OWOP::CHUNK_SIZE * y + x) * OWOP::Internal::PIXEL_BYTES;
}
template <ChunkFlags F>
constexpr void SetFlag(std::atomic_uint8_t& flags) noexcept {
    flags.fetch_or(F, std::memory_order::relaxed);
}
template <ChunkFlags F>
constexpr void ClearFlag(std::atomic_uint8_t& flags) noexcept {
    flags.fetch_and(~F, std::memory_order::relaxed);
}
template <ChunkFlags F>
constexpr bool CheckFlag(const std::atomic_uint8_t& flags) noexcept {
    return (flags.load(std::memory_order::relaxed) & F) != 0;
}
constexpr bool IsInBounds(std::uint32_t index) noexcept {
    return (index + OWOP::Internal::PIXEL_BYTES) < OWOP::Internal::CHUNK_BYTES;
}

OWOP::Chunk::Chunk()
    : m_data{ std::byte(0) }
    , m_flags(0)
    , m_mtx()
{
    printf("Chunk created!\n");
}

OWOP::Chunk::Chunk(const Chunk& other)
    : m_mtx()
{
    std::shared_lock l(other.m_mtx);
    m_data = other.m_data;
    m_flags.store(other.m_flags.load(std::memory_order::relaxed), std::memory_order::relaxed);
}

OWOP::Chunk::Chunk(Chunk&& other) noexcept
    : m_mtx()
{
    std::shared_lock l(other.m_mtx);
    m_data = std::move(other.m_data);
    m_flags.store(other.m_flags.load(std::memory_order::relaxed), std::memory_order::relaxed);
    other.m_data = { std::byte(0) };
    other.m_flags.store(0, std::memory_order::relaxed);
}

OWOP::Chunk::Chunk(std::span<const OWOP::Pixel, OWOP::Internal::CHUNK_PIXELS> pixels, bool isProtected)
    : m_flags(0)
    , m_mtx()
{
    auto pit = pixels.begin();
    auto dit = m_data.begin();
    while (pit != pixels.end()) {
        const auto& data = pit->data();
        std::copy(data.begin(), data.end(), dit);
        pit += 1;
        dit += 3;
    }

    if (isProtected) {
        SetFlag<ChunkFlags::Protected>(m_flags);
    }
}

OWOP::Chunk::Chunk(std::span<const std::byte, OWOP::Internal::CHUNK_BYTES> data, bool isProtected)
    : m_flags(0)
    , m_mtx()
{
    std::copy(data.begin(), data.end(), m_data.begin());

    if (isProtected) {
        SetFlag<ChunkFlags::Protected>(m_flags);
    }
}

OWOP::Pixel OWOP::Chunk::getPixel(std::uint8_t x, std::uint8_t y) const
{
    std::shared_lock l(m_mtx);

    auto index = GetPixelIndex(x, y);

    OWOP::Pixel pixel;

    if (IsInBounds(index)) {
        auto beg = m_data.begin() + index;
        auto end = beg + OWOP::Internal::PIXEL_BYTES;

        std::copy(beg, end, pixel.data().begin());
    }

    return pixel;
}

bool OWOP::Chunk::setPixel(std::uint8_t x, std::uint8_t y, const OWOP::Pixel& pixel)
{
    std::unique_lock l(m_mtx);

    auto index = GetPixelIndex(x, y);

    if (CheckFlag<ChunkFlags::Protected>(m_flags) || !IsInBounds(index)) {
        return false;
    }

    auto pixelData = pixel.data();

    std::copy(pixelData.begin(), pixelData.end(), m_data.begin() + index);

    return true;
}

bool OWOP::Chunk::fill(OWOP::Pixel color) noexcept
{
    std::unique_lock l(m_mtx);

    if (CheckFlag<ChunkFlags::Protected>(m_flags)) {
        return false;
    }

    auto colorDat = color.data();

    for (auto it = m_data.begin(); it != m_data.end(); it += OWOP::Internal::PIXEL_BYTES) {
        std::copy(colorDat.begin(), colorDat.end(), it);
    }

    return true;
}

void OWOP::Chunk::protect() noexcept
{
    SetFlag<ChunkFlags::Protected>(m_flags);
}

void OWOP::Chunk::unprotect() noexcept
{
    ClearFlag<ChunkFlags::Protected>(m_flags);
}

bool OWOP::Chunk::isProtected() const noexcept
{
    std::shared_lock l(m_mtx);
    return CheckFlag<ChunkFlags::Protected>(m_flags);
}

#ifdef COMPILE_GOAPI
static_assert (sizeof(CChunk::data) == OWOP::Internal::CHUNK_BYTES, "GO API differs in size for Chunk data!");
CChunk OWOP::Chunk::cchunk() const noexcept {
    CChunk c;
    c.flags = m_flags.load(std::memory_order::relaxed);
    std::shared_lock l(m_mtx);
    memcpy(c.data, m_data.data(), OWOP::Internal::CHUNK_BYTES);
    return c;
}
#endif

OWOP::Chunk& OWOP::Chunk::operator=(const Chunk& other)
{
    if (this != &other) {
        std::unique_lock l_this(m_mtx, std::defer_lock);
        std::shared_lock l_other(other.m_mtx, std::defer_lock);
        std::lock(l_this, l_other);

        m_data = other.m_data;
        m_flags.store(other.m_flags.load(std::memory_order::relaxed), std::memory_order::relaxed);
    }
    return *this;
}

OWOP::Chunk& OWOP::Chunk::operator=(Chunk&& other) noexcept
{
    if (this != &other) {
        std::unique_lock l_this(m_mtx, std::defer_lock);
        std::unique_lock l_other(other.m_mtx, std::defer_lock);
        std::lock(l_this, l_other);

        m_data = std::move(other.m_data);
        m_flags.store(other.m_flags.load(std::memory_order::relaxed), std::memory_order::relaxed);
        other.m_data = { std::byte(0) };
        other.m_flags.store(0, std::memory_order::relaxed);
    }
    return *this;
}
