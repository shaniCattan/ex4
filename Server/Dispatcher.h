//
// Created by shani on 1/31/20.
//

#pragma once

#include <memory>

#include "TcpServer.h"
#include "ClientHandler.h"

namespace server_side {
    class Dispatcher {
    public:
        virtual void dispatch(sockets::TcpServer server, std::unique_ptr<ClientHandler> handler) = 0;
    };
}
