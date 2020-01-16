//
// Created by mevaseret on 16/01/2020.
//

#include "TcpServer.h"

#include <system_error>

#include <unistd.h>
#include <netinet/in.h>

namespace server_side {
    namespace sockets {

        void TcpServer::open(const std::uint16_t port) {
            m_serverFd = socket(AF_INET, SOCK_STREAM, 0);
            if (-1 == m_serverFd) {
                throw std::system_error{errno, std::system_category()};
            }

            auto bindAddress = sockaddr_in{};
            bindAddress.sin_family = AF_INET;
            bindAddress.sin_port = htons(port);
            bindAddress.sin_addr.s_addr = INADDR_ANY;

            auto action = 1;
            if (-1 == setsockopt(m_serverFd, SOL_SOCKET, SO_REUSEPORT, &action, sizeof(action))) {
                throw std::system_error{errno, std::system_category()};
            }

            if (-1 == bind(m_serverFd, reinterpret_cast<sockaddr *>(&bindAddress), sizeof(bindAddress))) {
                throw std::system_error{errno, std::system_category()};
            }

            if (-1 == listen(m_serverFd, MAX_SERVER_BACKLOG)) {
                throw std::system_error{errno, std::system_category()};
            }

        }

        void TcpServer::stop() {
            if (-1 != m_serverFd) {
                if (-1 == close(m_serverFd)) {
                    throw std::system_error{errno, std::system_category()};
                }
                m_serverFd = -1;
            }
        }

        TcpServer::TcpServer(TcpServer &&rhs) noexcept {
            *this = std::move(rhs);
        }

        TcpServer &TcpServer::operator=(TcpServer &&rhs) noexcept {
            if (&rhs == this) {
                return *this;
            }

            m_serverFd = rhs.m_serverFd;
            rhs.m_serverFd = -1;
            return *this;
        }

        TcpServer::~TcpServer() {
            try {
                if (-1 != m_serverFd) {
                    close(m_serverFd);
                }
            }
            catch (...) {

            }
        }

        utilities::sockets::TcpSocket TcpServer::accept() const {
            auto clientAddress = sockaddr_in{};
            auto clientLength = static_cast<socklen_t>(sizeof(clientAddress));
            const auto clientSocketFd = ::accept(m_serverFd,
                                                 reinterpret_cast<sockaddr *>(&clientAddress), &clientLength);
            if (clientSocketFd == -1) {
                throw std::system_error{errno, std::system_category()};
            }

            return utilities::sockets::TcpSocket(clientSocketFd);
        }
    }
}