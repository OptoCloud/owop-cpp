#ifndef SERVER_H
#define SERVER_H

#include "ipinfo.h"
#include "connection.h"

#include "networking_includes.h"
#include "parallel_hashmap/phmap.h"

#include <atomic>

class Server
{
public:
    Server();

    bool listen(std::uint16_t port);
private:
    bool validateConnection(ConnectionHdl hdl);

    struct IpInfoPtr {
        IpInfoPtr():ptr(std::make_shared<IpInfo>()){}
        std::shared_ptr<IpInfo> ptr;
    };

    WsppServer m_server;
    phmap::parallel_flat_hash_map<std::string, IpInfoPtr> m_ipInfo;
};



#endif // SERVER_H
