#include "client.h"

OWOP::Client::Client()
{

}

std::shared_ptr<OWOP::ClientOptions> OWOP::Client::options()
{
    return m_options;
}

std::shared_ptr<const OWOP::ClientOptions> OWOP::Client::options() const
{
    return m_options;
}
