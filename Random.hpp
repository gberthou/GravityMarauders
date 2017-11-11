#ifndef UTILS_RANDOM_H
#define UTILS_RANDOM_H

#include <random>

#include <SFML/System.hpp>

template <class T>
class RandomRange
{
    public:
        RandomRange(const T &pointA, const T &pointB):
            generator(randomDevice()),
            distribution(0.f, 1.f),
            pointA(pointA),
            pointB(pointB)
        {
        }

        RandomRange(const RandomRange<T> &other):
            RandomRange(other.pointA, other.pointB)
        {
        }

        virtual ~RandomRange()
        {
        }

        T operator()()
        {
            float a = distribution(generator);
            return pointA * a + pointB * (1.f - a);
        }

        RandomRange &operator=(const RandomRange &other)
        {
            pointA = other.pointA;
            pointB = other.pointB;
            return *this;
        }

    protected:
        std::random_device randomDevice;
        std::mt19937 generator;
        std::uniform_real_distribution<float> distribution;
        T pointA;
        T pointB;
};

using RandomVector2 = RandomRange<sf::Vector2f>;
using RandomUint    = RandomRange<size_t>;
using RandomFloat   = RandomRange<float>;

#endif

