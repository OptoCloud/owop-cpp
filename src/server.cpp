#include "server.h"

#include "fmt/core.h"

#include <utility>

Server::Server()
    : m_server()
{
    // Set logging settings
    m_server.set_access_channels(websocketpp::log::alevel::all);
    m_server.clear_access_channels(websocketpp::log::alevel::frame_payload);

    // Initialize Asio
    m_server.init_asio();

    // Register our message handler
    m_server.set_validate_handler(std::bind(&Server::validateConnection, this, std::placeholders::_1));
}

bool Server::listen(std::uint16_t port)
{
    websocketpp::lib::error_code ec;
    m_server.listen(port, ec);
    if (ec) {
        fmt::print("Server listen failed: {}\n", ec.message());
        return false;
    }

    m_server.start_accept(ec);
    if (ec) {
        fmt::print("Server accept failed: {}\n", ec.message());
        return false;
    }

    m_server.run();

    return true;
}

bool Server::validateConnection(ConnectionHdl hdl)
{
    auto conPtr = m_server.get_con_from_hdl(hdl);
    std::string_view connectingIp = conPtr->get_request_header("Cf-Connecting-Ip");

    auto connection = m_ipInfo[connectingIp].ptr->TryAddConnection(hdl, conPtr);
    if (connection == nullptr) {
        fmt::print("[OWOP] Rejected connection from [{}]\n", connectingIp);
        return false;
    }
    fmt::print("[OWOP] Accepted connection from [{}]\n", connectingIp);

    return true;
}
