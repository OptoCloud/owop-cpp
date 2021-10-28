#ifndef OWOPCPP_PLAYER_H
#define OWOPCPP_PLAYER_H

#include "pixel.h"
#include "uuid.h"

#include <span>
#include <cstddef>

class Connection;

namespace OWOP {
class World;
class Player
{
public:
    Player(Connection* connection, OWOP::World* world);
    ~Player();

    void sendMessage(std::span<const std::byte> data) const;

    OWOP::World* world() const noexcept { return m_world; }
private:
    Connection* m_connection;
    OWOP::World* m_world;

    OWOP::Uuid m_id;
    std::int64_t m_posX;
    std::int64_t m_posY;
    OWOP::Pixel m_selectedColor;
};
}

#endif // OWOPCPP_PLAYER_H
