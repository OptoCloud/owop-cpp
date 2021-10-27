#ifndef IPINFO_H
#define IPINFO_H

#include "connection.h"

#include "networking_includes.h"

#include <shared_mutex>

class IpInfo
{
public:
    IpInfo();

    std::shared_ptr<Connection> TryAddConnection(ConnectionHdl conHdl, WsppServer::connection_ptr conPtr);
private:
    void onDisconnect(ConnectionHdl conHdl);

    bool m_banned;
    std::vector<std::shared_ptr<Connection>> m_connections;
    std::shared_mutex m_mtx;
};

#endif // IPINFO_H
