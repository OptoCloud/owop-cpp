#include "chunksystem.h"

constexpr std::uint64_t GetMapKey(std::int32_t x, std::int32_t y) noexcept {
    return ((std::uint64_t)x << 32) | (std::uint64_t)y;
}

OWOP::ChunkSystem::ChunkSystem()
{
}

void OWOP::ChunkSystem::setChunk(std::int32_t x, std::int32_t y, const OWOP::Chunk& chunk)
{
    m_chunks[GetMapKey(x, y)] = chunk;
}

void OWOP::ChunkSystem::getChunk(std::int32_t x, std::int32_t y, OWOP::Chunk& chunk)
{
    chunk = m_chunks[GetMapKey(x, y)];
}

bool OWOP::ChunkSystem::fillChunk(std::int32_t x, std::int32_t y, OWOP::Pixel pixel)
{
    return m_chunks[GetMapKey(x, y)].fill(pixel);
}

bool OWOP::ChunkSystem::setPixel(std::int64_t x, std::int64_t y, OWOP::Pixel pixel)
{
    std::int32_t chunkX = x >> 4;
    std::int32_t chunkY = y >> 4;
    std::uint8_t pixelX = x & 0xF;
    std::uint8_t pixelY = y & 0xF;

    return m_chunks[GetMapKey(chunkX, chunkY)].setPixel(pixelX, pixelY, pixel);
}

OWOP::Pixel OWOP::ChunkSystem::getPixel(std::int64_t x, std::int64_t y)
{
    std::int32_t chunkX = x >> 4;
    std::int32_t chunkY = y >> 4;
    std::uint8_t pixelX = x & 0xF;
    std::uint8_t pixelY = y & 0xF;

    return m_chunks[GetMapKey(chunkX, chunkY)].getPixel(pixelX, pixelY);
}

void OWOP::ChunkSystem::protectChunk(std::int32_t x, std::int32_t y)
{
    m_chunks[GetMapKey(x, y)].protect();
}

void OWOP::ChunkSystem::unprotectChunk(std::int32_t x, std::int32_t y)
{
    m_chunks[GetMapKey(x, y)].unprotect();
}

bool OWOP::ChunkSystem::isChunkProtected(std::int32_t x, std::int32_t y)
{
    return m_chunks[GetMapKey(x, y)].isProtected();
}
