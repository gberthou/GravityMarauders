#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <forward_list>

#include <SFML/Graphics.hpp>

#include <Random.hpp>
#include <Entity.h>

struct Particle
{
    public:
        Particle(size_t id,
                 sf::VertexArray &vertices,
                 size_t offset,
                 const sf::Vector2f &position,
                 const sf::Vector2f &velocity,
                 size_t initialTicks):
            id(id),
            vertices(vertices),
            offset(offset),
            position(position),
            velocity(velocity),
            remainingTicks(initialTicks)
        {
        }

        void Update()
        {
            if(IsDead())
                return;

            const float PARTICLE_SIZE = 2;
            position += velocity * Entity::FRAME_DT;

            vertices[offset + 0].position = sf::Vector2f(position.x - PARTICLE_SIZE / 2,
                                                position.y - PARTICLE_SIZE / 2);
            vertices[offset + 1].position = sf::Vector2f(position.x + PARTICLE_SIZE / 2,
                                                position.y - PARTICLE_SIZE / 2);
            vertices[offset + 2].position = sf::Vector2f(position.x + PARTICLE_SIZE / 2,
                                                position.y + PARTICLE_SIZE / 2);
            vertices[offset + 3].position = vertices[offset + 0].position;
            vertices[offset + 4].position = sf::Vector2f(position.x - PARTICLE_SIZE / 2,
                                                position.y + PARTICLE_SIZE / 2);
            vertices[offset + 5].position = vertices[offset + 2].position;

            --remainingTicks;
        }

        bool IsDead() const
        {
            return remainingTicks == 0;
        }

        size_t GetId() const
        {
            return id;
        }

    protected:
        size_t id;
        sf::VertexArray &vertices;
        size_t offset;
        sf::Vector2f position;
        sf::Vector2f velocity;
        size_t remainingTicks;
};

class ParticleSystem : public sf::Drawable
{
    public:
        // Angle == 0 <=> (intensity, 0)
        ParticleSystem(size_t quadCount,
                       const sf::Vector2f &velocity,
                       const RandomVector2 &positionGenerator,
                       const RandomFloat &velocityAngleGenerator,
                       const RandomFloat &velocityIntensityGenerator,
                       const RandomUint &tickGenerator);
        virtual ~ParticleSystem();

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states)
            const;

        void Update();

        void Stop();
        bool IsDone() const;

        void SetVelocityOffset(const sf::Vector2f &velocity);

    protected:
        sf::VertexArray vertices;
        std::forward_list<Particle> particles;
        sf::Vector2f velocityOffset;
        RandomVector2 positionGenerator;
        RandomFloat velocityAngleGenerator;
        RandomFloat velocityIntensityGenerator;
        RandomUint tickGenerator;
        bool stopped;
};

#endif

