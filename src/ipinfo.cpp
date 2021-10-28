#include "ipinfo.h"

IpInfo::IpInfo()
{

}

std::shared_ptr<Connection> IpInfo::TryAddConnection(ConnectionHdl conHdl, WsppServer::connection_ptr conPtr)
{
    std::unique_lock l(m_mtx);
    if (m_banned || m_connections.size() >= 16) {
        return nullptr;
    }

    auto connection = std::make_shared<Connection>(
                conHdl,
                conPtr,
                std::bind(&IpInfo::onDisconnect, this, std::placeholders::_1)
                );
    m_connections.push_back(connection);

    return connection;
}

void IpInfo::onDisconnect(Connection* conPtr)
{
    std::unique_lock l(m_mtx);
    auto it = std::find_if(m_connections.begin(), m_connections.end(), [conPtr](const std::shared_ptr<Connection>& connection) -> bool {
        return connection.get() == conPtr;
    });
    if (it != m_connections.end()) {
        m_connections.erase(it);
    }
}
