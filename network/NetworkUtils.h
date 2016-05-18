#ifndef NETWORK_UTILS_H
#define NETWORK_UTILS_H

#include <SFML/Network.hpp>

sf::Packet &operator<<(sf::Packet &packet, const sf::Vector2f &v);
sf::Packet &operator>>(sf::Packet &packet, sf::Vector2f &v);

#endif

