//
// Created by shani on 1/24/20.
//

#include "DataReader.h"

namespace server_side {
    std::string readClientData(const utilities::sockets::TcpSocket &socket) {
        auto buffer = std::string{};
        while (true) {
            auto newBuffer = socket.readAtMost(1024);
            buffer += newBuffer;
            if (newBuffer.find(END_TOKEN) != std::string::npos) {
                break;
            }
        }
        return buffer;
    }
}
