#ifndef OWOPCPP_WORLD_H
#define OWOPCPP_WORLD_H

#include "godef.h"
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
    _GoString_ nameGostr() const;

    OWOP::Color GetPixel(std::int64_t x, std::int64_t y);
    bool SetPixel(std::int64_t x, std::int64_t y, OWOP::Color c);
private:
    mutable std::shared_mutex l_name;
    std::string m_name;
    std::unordered_map<OWOP::Uuid, OWOP::Player> m_players;
    OWOP::ChunkSystem m_chunkSystem;
};

}

#endif // OWOPCPP_WORLD_H
