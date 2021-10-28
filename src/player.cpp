#include "player.h"

#include "connection.h"

OWOP::Player::Player(Connection* connection, World* world)
    : m_connection(connection)
    , m_world(m_world)
{

}

void OWOP::Player::sendMessage(std::span<const std::byte> data) const
{
    m_connection->send(data);
}
