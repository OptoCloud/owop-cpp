#ifndef NETWORKING_INCLUDES_H
#define NETWORKING_INCLUDES_H

#define ASIO_STANDALONE
#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"

typedef websocketpp::server<websocketpp::config::asio> WsppServer;
typedef WsppServer::message_ptr MessagePtr;
typedef WsppServer::connection_ptr ConnectionPtr;
typedef websocketpp::connection_hdl ConnectionHdl;
typedef websocketpp::frame::opcode::value OpCode;

#endif // NETWORKING_INCLUDES_H
