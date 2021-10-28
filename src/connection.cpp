#include "connection.h"

#include "fmt/core.h"

Connection::Connection(ConnectionHdl conHdl, WsppServer::connection_ptr conPtr, std::function<void(Connection*)> onDisconnected)
    : m_conHdl(conHdl)
    , m_conPtr(conPtr)
    , f_onDisconnected(onDisconnected)
    , m_player(nullptr)
{
    conPtr->set_message_handler(std::bind(&Connection::onMessage, this, std::placeholders::_1, std::placeholders::_2));
    conPtr->set_close_handler(std::bind(&Connection::onDisconnect, this, std::placeholders::_1));
}

Connection::~Connection()
{
}

ConnectionHdl Connection::conHdl() const
{
    return m_conHdl;
}
WsppServer::connection_ptr Connection::conPtr() const
{
    return m_conPtr;
}

void Connection::send(std::span<const std::byte> data)
{
    m_conPtr->send(data.data(), data.size(), OpCode::BINARY);
}

void Connection::onMessage(ConnectionHdl hdl, MessagePtr msg)
{
    if (msg)
    if (msg->get_opcode() != OpCode::BINARY) {
        m_conPtr->send(msg->get_payload(), msg->get_opcode());
        return;
    }
}

void Connection::onDisconnect(ConnectionHdl hdl)
{
    f_onDisconnected(this);
}
