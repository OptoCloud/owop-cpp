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

    auto connection = std::make_shared<Connection>(conHdl, conPtr);
    m_connections.push_back(connection);

    conPtr->set_close_handler(std::bind(&IpInfo::onDisconnect, this, std::placeholders::_1));

    return connection;
}

void IpInfo::onDisconnect(ConnectionHdl conHdl)
{
    std::unique_lock l(m_mtx);
    for (auto it = m_connections.begin(); it != m_connections.end(); it++) {
        auto& connection = *it;
        if (connection->conHdl().lock() == conHdl.lock()) {
            connection->disconnected();
            m_connections.erase(it);
            printf("Yup!\n");
            return;
        }
    }
}
