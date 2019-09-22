#include "server.h"

#include "event.h"

#include <SFML/Network/Packet.hpp>
#include <iostream>

namespace net {
    Server::Server()
    {
        m_socket.bind(54321);
        m_socket.setBlocking(false);
    }

    void Server::onClientConnect(Server::OnEventFunction function)
    {
        currentConnections++;
        m_onConnect = function;
    }

    void Server::onClientDisconnect(Server::OnEventFunction function)
    {
        currentConnections--;
        m_onDisconnect = function;
    }

    void Server::handleIncomingConnection(const Event &event)
    {
        if (auto slot = emptySlot(); slot < MAX_CONNECTIONS) {
            m_clientConnected[slot] = true;
            m_clients[slot].address = event.details.senderIp;
            m_clients[slot].port = event.details.senderPort;
            m_clients[slot].lastUpdate = m_clock.getElapsedTime();

            event.respond(m_socket, Event::EventType::AcceptConnection,
                          static_cast<ClientId>(slot));
            m_onConnect(event.details);
        }
        else {
            event.respond(m_socket, Event::EventType::RejectConnection);
        }
    }

    void Server::keepAlive(const Event &event)
    {
        auto &client = getClient(event.details.id);
        client.lastUpdate = m_clock.getElapsedTime();
    }

    std::size_t Server::emptySlot() const
    {
        for (std::size_t i = 0; i < MAX_CONNECTIONS; i++) {
            if (!m_clientConnected[i]) {
                return i;
            }
        }
        return MAX_CONNECTIONS + 1;
    }

    Server::ConnectedClient &Server::getClient(ClientId id)
    {
        return m_clients[static_cast<std::size_t>(id)];
    }

} // namespace net