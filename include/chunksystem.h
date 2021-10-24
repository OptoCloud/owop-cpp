#ifndef OWOPCPP_CHUNKSYSTEM_H
#define OWOPCPP_CHUNKSYSTEM_H

#include "chunk.h"
#include "color.h"
#include "constants.h"

#include "phmap.h"

#include <shared_mutex>
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
    OWOP::Chunk getChunk(std::int32_t x, std::int32_t y);

    bool setPixel(std::int64_t x, std::int64_t y, OWOP::Color pixel);
    OWOP::Color getPixel(std::int64_t x, std::int64_t y);

    void protectChunk(std::int32_t x, std::int32_t y);
    void unprotectChunk(std::int32_t x, std::int32_t y);
    bool isChunkProtected(std::int32_t x, std::int32_t y);
private:
    phmap::parallel_node_hash_map<std::uint64_t, OWOP::Chunk> m_chunks;
};
}

#endif // OWOPCPP_CHUNKSYSTEM_H
