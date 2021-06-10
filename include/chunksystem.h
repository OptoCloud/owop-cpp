#ifndef OWOPCPP_CHUNKSYSTEM_H
#define OWOPCPP_CHUNKSYSTEM_H

#include "chunk.h"
#include "color.h"
#include "constants.h"

#include <shared_mutex>
#include <unordered_map>
#include <memory>
#include <array>
#include <cstdlib>
#include <cstdint>

namespace OWOP {
class ChunkSystem
{
public:
    ChunkSystem();

    void setChunk(std::int32_t x, std::int32_t y, const OWOP::Chunk& chunk);
    std::shared_ptr<OWOP::Chunk> getChunk(std::int32_t x, std::int32_t y) const;
    bool removeChunk(std::int32_t x, std::int32_t y);

    bool setPixel(std::int64_t x, std::int64_t y, OWOP::Color pixel);
    OWOP::Color getPixel(std::int64_t x, std::int64_t y) const;

    bool protectChunk(std::int32_t x, std::int32_t y);
    bool unprotectChunk(std::int32_t x, std::int32_t y);
    bool isChunkProtected(std::int32_t x, std::int32_t y);
private:
    std::shared_mutex l_chunks;
    std::unordered_map<std::uint64_t, std::shared_ptr<OWOP::Chunk>> m_chunks;
};
}

#endif // OWOPCPP_CHUNKSYSTEM_H
