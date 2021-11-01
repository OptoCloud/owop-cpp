#ifndef OWOPCPP_WORLD_H
#define OWOPCPP_WORLD_H

#include "chunksystem.h"
#include "player.h"
#include "uuid.h"

#include <string>
#include <queue>
#include <unordered_set>
#include <shared_mutex>

namespace OWOP {

class World
{
public:
    World();
    ~World();

    void add(const std::shared_ptr<OWOP::Player>& player);
    void remove(const std::shared_ptr<OWOP::Player>& player);

    std::string name() const;
    void setName(std::string_view name);

    void setChunk(std::int32_t x, std::int32_t y, const OWOP::Chunk& chunk);
    void getChunk(std::int32_t x, std::int32_t y, OWOP::Chunk& chunk);
    bool fillChunk(std::int32_t x, std::int32_t y, OWOP::Pixel pixel);

    bool setPixel(std::int64_t x, std::int64_t y, OWOP::Pixel pixel);
    OWOP::Pixel getPixel(std::int64_t x, std::int64_t y);

    void protectChunk(std::int32_t x, std::int32_t y);
    void unprotectChunk(std::int32_t x, std::int32_t y);
    bool isChunkProtected(std::int32_t x, std::int32_t y);
private:
    void broadcastToPlayers(std::span<const std::uint8_t> data) const;

    mutable std::shared_mutex l_name;
    std::string m_name;
    mutable std::shared_mutex l_players;
    std::unordered_set<std::shared_ptr<OWOP::Player>> m_players;
    OWOP::ChunkSystem m_chunkSystem;
};

}

#endif // OWOPCPP_WORLD_H
