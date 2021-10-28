#include "worldmanager.h"

OWOP::WorldManager::WorldManager()
{
}

std::shared_ptr<OWOP::World> OWOP::WorldManager::GetWorld(const std::string& name)
{
    return m_worlds[name].ptr;
}

void OWOP::WorldManager::ForgetWorld(const std::string& name)
{
    m_worlds.erase(name);
}
