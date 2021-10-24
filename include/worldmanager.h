#ifndef OWOP_WORLDMANAGER_H
#define OWOP_WORLDMANAGER_H

#include "world.h"

#include <unordered_map>
#include <memory>
#include <atomic>
#include <shared_mutex>

namespace OWOP {

class WorldManager
{
public:
    WorldManager();

    OWOP::World* GetWorld(std::string_view name) const;
    OWOP::World* CreateWorld(std::string_view name, std::string_view adminPassword);
    void DestroyWorld(std::string_view name);
private:
    mutable std::shared_mutex l_worlds;
    std::unordered_map<std::string, OWOP::World*> m_worlds;
};

}

#endif // OWOP_WORLDMANAGER_H
