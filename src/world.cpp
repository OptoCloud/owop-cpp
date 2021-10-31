#include "world.h"

OWOP::World::World()
    : l_name()
    , m_name()
    , l_players()
    , m_players()
    , m_chunkSystem()
{
}

OWOP::World::~World()
{
}

void OWOP::World::add(const std::shared_ptr<Player>& player)
{
    std::unique_lock l(l_players);
    m_players.insert(player);
}

void OWOP::World::remove(const std::shared_ptr<Player>& player)
{
    std::unique_lock l(l_players);
    auto it = m_players.find(player);
    if (it != m_players.end()) {
        m_players.erase(it);
    }
}

std::string OWOP::World::name() const
{
    std::shared_lock l(l_name);
    return m_name;
}

void OWOP::World::setName(std::string_view name)
{
    std::unique_lock l(l_name);
    m_name = name;
}

void OWOP::World::setChunk(std::int32_t x, std::int32_t y, const Chunk &chunk)
{
    m_chunkSystem.setChunk(x, y, chunk);
}

void OWOP::World::getChunk(std::int32_t x, std::int32_t y, Chunk &chunk)
{
    m_chunkSystem.getChunk(x, y, chunk);
}

bool OWOP::World::fillChunk(std::int32_t x, std::int32_t y, Pixel pixel)
{
    if (!m_chunkSystem.fillChunk(x, y, pixel)) {
        return false;
    }

    // broadcastToPlayers();

    return true;
}

bool OWOP::World::setPixel(std::int64_t x, std::int64_t y, Pixel pixel)
{
    return m_chunkSystem.setPixel(x, y, pixel);
}

OWOP::Pixel OWOP::World::getPixel(std::int64_t x, std::int64_t y)
{
    return m_chunkSystem.getPixel(x, y);
}

void OWOP::World::protectChunk(std::int32_t x, std::int32_t y)
{
    m_chunkSystem.protectChunk(x, y);
}

void OWOP::World::unprotectChunk(std::int32_t x, std::int32_t y)
{
    m_chunkSystem.unprotectChunk(x, y);
}

bool OWOP::World::isChunkProtected(std::int32_t x, std::int32_t y)
{
    return m_chunkSystem.isChunkProtected(x, y);
}

void OWOP::World::broadcastToPlayers(std::span<const std::byte> data) const
{
    std::shared_lock l(l_players);
    for (auto& player : m_players) {
        player->sendMessage(data);
    }
}
