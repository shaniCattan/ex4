//
// Created by shani on 1/24/20.
//

#pragma once

#include <string>

#include "Socket/TcpSocket.h"

namespace server_side {
    constexpr auto END_TOKEN = "end";
    constexpr auto ENDLINE_TOKEN = '\n';

    std::string readClientData(const utilities::sockets::TcpSocket& socket);
}
