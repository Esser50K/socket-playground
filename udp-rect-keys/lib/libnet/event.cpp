#include "event.h"

#include <SFML/Network/Packet.hpp>
#include <SFML/Network/UdpSocket.hpp>

namespace net {
    sf::Packet &operator<<(sf::Packet &packet, Event::EventType &type)
    {
        packet << static_cast<uint16_t>(type);
        return packet;
    }

    sf::Packet &operator>>(sf::Packet &packet, Event::EventType &type)
    {
        uint16_t commandId;
        packet >> commandId;
        type = static_cast<Event::EventType>(commandId);
        return packet;
    }

    bool receiveNetEvent(sf::UdpSocket &socket, sf::Packet &packet,
                         Event &event)
    {
        if (socket.receive(packet, event.details.senderIp,
                           event.details.senderPort) != sf::Socket::Done) {
            return false;
        }
        packet >> event.type >> event.details.senderId;
        return true;
    }
} // namespace net