#include "connection.h"

#include "fmt/core.h"

Connection::Connection(ConnectionHdl conHdl, WsppServer::connection_ptr conPtr)
    : m_conHdl(conHdl)
    , m_conPtr(conPtr)
{
    conPtr->set_message_handler(std::bind(&Connection::onMessage, this, std::placeholders::_1, std::placeholders::_2));
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

void Connection::disconnected()
{
}

void Connection::onMessage(ConnectionHdl hdl, MessagePtr msg)
{
    fmt::print("MSG: {}\n", msg->get_payload());
    m_conPtr->send(msg->get_payload(), msg->get_opcode());
}
