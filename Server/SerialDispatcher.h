//
// Created by shani on 1/31/20.
//

#pragma once

#include "Dispatcher.h"

namespace server_side {
    class SerialDispatcher : public Dispatcher {
    public:
        void dispatch(sockets::TcpServer server, std::unique_ptr<ClientHandler> handler) override;
    };

}