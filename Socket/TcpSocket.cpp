//
// Created by mevaseret on 16/01/2020.
//

#include <utility>

#include <unistd.h>

#include "TcpSocket.h"

namespace utilities {
    namespace sockets {

        TcpSocket::TcpSocket(TcpSocket &&rhs) noexcept {
            *this = std::move(rhs);
        }

        TcpSocket &TcpSocket::operator=(TcpSocket &&rhs) noexcept {
            if (&rhs == this) {
                return *this;
            }

            m_socketFd = rhs.m_socketFd;
            rhs.m_socketFd = -1;
            return *this;
        }

        TcpSocket::TcpSocket(int socketFd) noexcept :
                m_socketFd(socketFd) {
        }

        TcpSocket::~TcpSocket() {
            try {
                if (-1 != m_socketFd) {
                    close(m_socketFd);
                }
            }
            catch (...) {

            }
        }
    }
}