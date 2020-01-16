//
// Created by mevaseret on 16/01/2020.
//

#include <utility>
#include <system_error>

#include <cerrno>
#include <unistd.h>
#include <sys/socket.h>

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

        std::string TcpSocket::readAtLeast(const std::size_t count) const {
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
    }
}