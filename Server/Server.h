//
// Created by mevaseret on 16/01/2020.
//

#pragma once

#include <cstdint>

#include "ClientHandler.h"

namespace server_side {

    class Server {
    public:
        virtual void open(std::uint16_t port) = 0;
        virtual void accept(const ClientHandler& handler) const = 0;
        virtual void stop() = 0;
    };

}
