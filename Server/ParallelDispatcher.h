//
// Created by shani on 1/31/20.
//

#pragma once

#include "Dispatcher.h"

#include <stack>
#include <thread>

namespace server_side {
    class ParallelDispatcher : public Dispatcher {
    public:
        void dispatch(sockets::TcpServer server, std::unique_ptr<ClientHandler> handler) override;
    private:
        std::stack<std::thread> m_threads;
    };

}