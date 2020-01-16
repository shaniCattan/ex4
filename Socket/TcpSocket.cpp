//
// Created by mevaseret on 16/01/2020.
//

#include <utility>
#include <system_error>

#include <cerrno>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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

        std::string TcpSocket::readAtMost(size_t count) const {
            auto buffer = std::string(count, '\0');

            const auto bytesRead = read(m_socketFd, const_cast<char *>(buffer.data()), buffer.size());
            if (bytesRead == -1) {
                throw std::system_error{errno, std::system_category()};
            }
            buffer.resize(bytesRead);
            return buffer;
        }

        void TcpSocket::send(const std::string &buffer) const {
            const auto bytesWritten = write(m_socketFd, buffer.data(), buffer.size());
            if (bytesWritten == -1 || bytesWritten < buffer.size()) {
                throw std::system_error{errno, std::system_category()};
            }
        }

        TcpSocket::TcpSocket(const std::string &ip, const std::uint16_t port) {
            m_socketFd = socket(AF_INET, SOCK_STREAM, 0);
            if (-1 == m_socketFd) {
                throw std::system_error{errno, std::system_category()};
            }

            auto serverAddress = sockaddr_in{};
            serverAddress.sin_family = AF_INET;
            serverAddress.sin_port = htons(port);
            if (0 == inet_pton(AF_INET, ip.c_str(), &(serverAddress.sin_addr))) {
                throw std::system_error{errno, std::system_category()};
            }

            if (-1 == connect(m_socketFd, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress))) {
                throw std::system_error{errno, std::system_category()};
            }
        }

        std::string TcpSocket::readExactly(const std::size_t count) const {
            auto buffer = std::string{};
            buffer.reserve(count);

            while (buffer.size() < count) {
                buffer += readAtMost(count - buffer.size());
            }

            return buffer;
        }
    }
}