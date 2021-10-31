#ifndef CONNECTION_H
#define CONNECTION_H

#include "player.h"
#include "networking_includes.h"

#include <functional>

class Connection
{
public:
    Connection(ConnectionHdl conHdl, WsppServer::connection_ptr conPtr, std::function<void(Connection*)> onDisconnected);
    ~Connection();

    ConnectionHdl conHdl() const;
    WsppServer::connection_ptr conPtr() const;

    void send(std::span<const std::byte> data);
private:
    void onMessage(ConnectionHdl hdl, MessagePtr msg);
    void onDisconnect(ConnectionHdl hdl);

    WsppServer::connection_ptr m_conPtr;
    websocketpp::connection_hdl m_conHdl;
    std::function<void(Connection*)> f_onDisconnected;

    std::shared_ptr<OWOP::Player> m_player;

};

#endif // CONNECTION_H
