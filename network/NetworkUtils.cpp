#include <NetworkUtils.h>

sf::Packet &operator<<(sf::Packet &packet, const sf::Vector2f &v)
{
    return packet << v.x << v.y;
}

sf::Packet &operator>>(sf::Packet &packet, sf::Vector2f &v)
{
    return packet >> v.x >> v.y;
}

