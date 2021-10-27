#ifndef OWOPCPP_WORLD_H
#define OWOPCPP_WORLD_H

#include "chunksystem.h"
#include "player.h"
#include "uuid.h"

#include <string>
#include <queue>
#include <unordered_map>
#include <shared_mutex>

namespace OWOP {

class World
{
public:
    World(std::string_view name, std::string_view adminPassword);
    ~World();

    std::string name() const;

    OWOP::Pixel GetPixel(std::int64_t x, std::int64_t y);
    bool SetPixel(std::int64_t x, std::int64_t y, OWOP::Pixel c);
private:
    mutable std::shared_mutex l_name;
    std::string m_name;
    std::unordered_map<OWOP::Uuid, OWOP::Player> m_players;
    OWOP::ChunkSystem m_chunkSystem;
};

}

#endif // OWOPCPP_WORLD_H
