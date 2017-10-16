#include <SFML/System.hpp>

const float EPSILON = 0.1f;

inline float dot(const sf::Vector2f &a, const sf::Vector2f &b)
{
    return a.x * b.x + a.y * b.y;
}

inline float len2(const sf::Vector2f &v)
{
    return dot(v, v);
}

// Computes cross product of a and b and returns z corrdinate
inline float crossZ(const sf::Vector2f &a, const sf::Vector2f &b)
{
    return a.x * b.y - a.y * b.x;
}

inline float min(float a, float b)
{
    return a < b ? a : b;
}

inline float max(float a, float b)
{
    return a < b ? b : a;
}

// clamp x to range [a, b]
// Assumes that a < b
inline float clamp(float x, float a, float b)
{
    if(x < a)
        return a;
    if(x > b)
        return b;
    return x;
}
