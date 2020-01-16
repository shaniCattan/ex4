//
// Created by mevaseret on 16/01/2020.
//

#pragma once

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

        private:
            int m_socketFd = -1;
        };
    }
}


