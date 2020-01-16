//
// Created by mevaseret on 16/01/2020.
//

#pragma once

#include <string>

namespace utilities {
    namespace sockets {
        class TcpSocket {

        public:
            explicit TcpSocket(int socketFd) noexcept;

            TcpSocket(const TcpSocket &) = delete;

            TcpSocket &operator=(const TcpSocket &) = delete;

            TcpSocket(TcpSocket &&rhs) noexcept;

            TcpSocket &operator=(TcpSocket &&rhs) noexcept;

            ~TcpSocket();

            std::string readAtLeast(std::size_t count) const;

            void send(const std::string &buffer) const;

        private:
            int m_socketFd = -1;
        };
    }
}


