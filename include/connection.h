#ifndef CONNECTION_H
#define CONNECTION_H

#include "networking_includes.h"

class Connection
{
public:
    Connection(ConnectionHdl conHdl, WsppServer::connection_ptr conPtr);
    ~Connection();

    ConnectionHdl conHdl() const;
    WsppServer::connection_ptr conPtr() const;

    void disconnected();
private:
    void onMessage(ConnectionHdl hdl, MessagePtr msg);

    ConnectionHdl m_conHdl;
    WsppServer::connection_ptr m_conPtr;
};

#endif // CONNECTION_H
