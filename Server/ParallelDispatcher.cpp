//
// Created by shani on 1/31/20.
//

#include "ParallelDispatcher.h"

#include <iostream>
#include <thread>

namespace server_side {

    void ParallelDispatcher::dispatch(sockets::TcpServer server, std::unique_ptr<ClientHandler> handler) {
        while (true) {
            try {
                auto client = server.accept();
                m_threads.emplace([&](){handler->handleClient(std::move(client));});
            } catch (std::exception& e) {
                std::cerr << e.what() << std::endl;
                break;
            }
        }

        while (!m_threads.empty()) {
            m_threads.top().join();
            m_threads.pop();
        }
    }
}