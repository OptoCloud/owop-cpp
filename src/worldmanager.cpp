#include "worldmanager.h"

OWOP::WorldManager::WorldManager()
{

}

OWOP::World* OWOP::WorldManager::GetWorld(std::string_view name) const
{
    std::shared_lock l(l_worlds);

    auto w_it = m_worlds.find(std::string(name));

    if (w_it == m_worlds.end()) {
        return nullptr;
    }

    return w_it->second;
}

OWOP::World* OWOP::WorldManager::CreateWorld(std::string_view name, std::string_view adminPassword)
{
    std::unique_lock l(l_worlds);

    auto w_it = m_worlds.insert(std::pair<std::string, OWOP::World*>(name, nullptr));

    if (w_it.second) {
        w_it.first->second = new OWOP::World(name, adminPassword);
    }

    return w_it.first->second;
}

void OWOP::WorldManager::DestroyWorld(std::string_view name)
{
    std::unique_lock l(l_worlds);

    auto w_it = m_worlds.find(std::string(name));

    if (w_it != m_worlds.end()) {
        delete w_it->second;
        m_worlds.erase(w_it);
    }
}
