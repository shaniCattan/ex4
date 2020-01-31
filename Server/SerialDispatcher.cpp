//
// Created by shani on 1/31/20.
//

#include "SerialDispatcher.h"

#include <iostream>

namespace server_side {

    void SerialDispatcher::dispatch(sockets::TcpServer server, std::unique_ptr<ClientHandler> handler) {
        while (true) {
            try {
                auto client = server.accept();
                handler->handleClient(std::move(client));
            } catch (std::exception& e) {
                std::cerr << e.what() << std::endl;
                break;
            }
        }
    }
}