#ifndef OWOP_WORLDMANAGER_H
#define OWOP_WORLDMANAGER_H

#include "world.h"

#include "parallel_hashmap/phmap.h"

#include <memory>

namespace OWOP {

class WorldManager
{
public:
    WorldManager();

    std::shared_ptr<OWOP::World> GetWorld(const std::string& name);
    void ForgetWorld(const std::string& name);
private:
    struct WorldPtr {
        WorldPtr():ptr(std::make_shared<OWOP::World>()){};
        std::shared_ptr<OWOP::World> ptr;
    };

    phmap::parallel_flat_hash_map<std::string, WorldPtr> m_worlds;
};

}

#endif // OWOP_WORLDMANAGER_H
