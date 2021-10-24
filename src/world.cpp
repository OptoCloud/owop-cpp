#include "world.h"

OWOP::World::World(std::string_view name, std::string_view adminPassword)
    : m_name(name)
    , m_chunkSystem()
{
    printf("World Created!\n");
}

OWOP::World::~World()
{

}

std::string OWOP::World::name() const
{
    std::shared_lock l(l_name);
    return m_name;
}

_GoString_ OWOP::World::nameGostr() const
{
    std::shared_lock l(l_name);
    return MakeGoString(m_name);
}

OWOP::Color OWOP::World::GetPixel(std::int64_t x, std::int64_t y)
{
    return m_chunkSystem.getPixel(x, y);
}

bool OWOP::World::SetPixel(std::int64_t x, std::int64_t y, OWOP::Color c)
{
    return m_chunkSystem.setPixel(x, y, c);
}
