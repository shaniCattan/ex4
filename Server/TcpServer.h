//
// Created by mevaseret on 16/01/2020.
//

#pragma once

#include "Server.h"
#include "Socket/TcpSocket.h"

namespace server_side {
    namespace sockets {
        class TcpServer {
            constexpr static auto MAX_SERVER_BACKLOG = 5;
        public:
            TcpServer() = default;

            TcpServer(const TcpServer&) = delete;
            TcpServer& operator=(const TcpServer&) = delete;

            TcpServer(TcpServer&& rhs) noexcept;
            TcpServer& operator=(TcpServer&& rhs) noexcept;

            ~TcpServer();

            void open(std::uint16_t port);
            utilities::sockets::TcpSocket accept() const;
            void stop();

        private:

            int m_serverFd = -1;
        };
    }
}
