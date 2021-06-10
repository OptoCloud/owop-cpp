#include "chunksystem.h"

constexpr std::uint64_t getMapKey(std::int32_t x, std::int32_t y) {
    return ((std::uint64_t)x << 32) | (std::uint64_t)y;
}

OWOP::ChunkSystem::ChunkSystem()
{

}

void OWOP::ChunkSystem::setChunk(std::int32_t x, std::int32_t y, const OWOP::Chunk& chunk)
{
    auto key = getMapKey(x, y);
    auto it = m_chunks.find(key);

    auto shared = std::make_shared<OWOP::Chunk>(chunk);

    if (it != m_chunks.end()) {
        it->second = shared;
    }
    else {
        m_chunks.insert(std::pair<std::uint64_t, std::shared_ptr<OWOP::Chunk>>(key, shared));
    }
}

std::shared_ptr<OWOP::Chunk> OWOP::ChunkSystem::getChunk(std::int32_t x, std::int32_t y) const
{
    auto it = m_chunks.find(getMapKey(x, y));

    if (it != m_chunks.end()) {
        return it->second;
    }

    return nullptr;
}

bool OWOP::ChunkSystem::removeChunk(std::int32_t x, std::int32_t y)
{
    auto it = m_chunks.find(getMapKey(x, y));

    if (it != m_chunks.end()) {
        m_chunks.erase(it);
        return true;
    }

    return false;
}

bool OWOP::ChunkSystem::setPixel(std::int64_t x, std::int64_t y, OWOP::Color pixel)
{
    std::int32_t chunkX = x / OWOP::CHUNK_SIZE;
    std::int32_t chunkY = y / OWOP::CHUNK_SIZE;

    auto it = m_chunks.find(getMapKey(chunkX, chunkY));

    if (it != m_chunks.end()) {
        std::uint8_t pixelX = x - (chunkX * OWOP::CHUNK_SIZE);
        std::uint8_t pixelY = y - (chunkY * OWOP::CHUNK_SIZE);

        it->second->setPixel(pixelX, pixelY, pixel);
        return true;
    }

    return false;
}

OWOP::Color OWOP::ChunkSystem::getPixel(std::int64_t x, std::int64_t y) const
{
    std::int32_t chunkX = x / OWOP::CHUNK_SIZE;
    std::int32_t chunkY = y / OWOP::CHUNK_SIZE;

    auto it = m_chunks.find(getMapKey(chunkX, chunkY));

    if (it != m_chunks.end()) {
        std::uint8_t pixelX = x - (chunkX * OWOP::CHUNK_SIZE);
        std::uint8_t pixelY = y - (chunkY * OWOP::CHUNK_SIZE);

        return it->second->getPixel(pixelX, pixelY);
    }

    return OWOP::Color();
}

bool OWOP::ChunkSystem::protectChunk(std::int32_t x, std::int32_t y)
{
    auto it = m_chunks.find(getMapKey(x, y));

    if (it != m_chunks.end()) {
        it->second->protect();
        return true;
    }

    return false;
}

bool OWOP::ChunkSystem::unprotectChunk(std::int32_t x, std::int32_t y)
{
    auto it = m_chunks.find(getMapKey(x, y));

    if (it != m_chunks.end()) {
        it->second->unprotect();
        return true;
    }

    return false;
}

bool OWOP::ChunkSystem::isChunkProtected(std::int32_t x, std::int32_t y)
{
    auto it = m_chunks.find(getMapKey(x, y));

    if (it != m_chunks.end()) {
        return it->second->isProtected();
    }

    return false;
}
