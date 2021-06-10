#ifndef OWOPCPP_CLIENT_H
#define OWOPCPP_CLIENT_H

#include "chunksystem.h"
#include "clientoptions.h"
#include "playerrank.h"

#include <span>

namespace OWOP {
class Client
{
public:
    Client();

    std::shared_ptr<OWOP::ClientOptions> options();
    std::shared_ptr<const OWOP::ClientOptions> options() const;
private:
    std::shared_ptr<OWOP::ClientOptions> m_options;
    OWOP::ChunkSystem m_chunkSystem;
    OWOP::PlayerRank m_playerRank;
};
}

#endif // OWOPCPP_CLIENT_H
