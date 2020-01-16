//
// Created by mevaseret on 16/01/2020.
//

#pragma once

#include "Socket/TcpSocket.h"

namespace server_side {
    class ClientHandler {
    public:
        virtual void handleClient(utilities::sockets::TcpSocket sock) = 0;
    };
}
