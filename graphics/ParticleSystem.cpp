#include <ParticleSystem.h>

static sf::Vector2f buildVector(float angle, float intensity)
{
    sf::Transform transform;
    transform.rotate(angle);
    return transform.transformPoint(intensity, 0);
}

ParticleSystem::ParticleSystem(size_t quadCount,
                               const sf::Vector2f &velocity,
                               const RandomVector2 &positionGenerator,
                               const RandomFloat &velocityAngleGenerator,
                               const RandomFloat &velocityIntensityGenerator,
                               const RandomUint &tickGenerator):
    vertices(sf::Triangles, quadCount * 6),
    velocityOffset(velocity),
    positionGenerator(positionGenerator),
    velocityAngleGenerator(velocityAngleGenerator),
    velocityIntensityGenerator(velocityIntensityGenerator),
    tickGenerator(tickGenerator),
    stopped(false)
{
    for(size_t i = 0; i < quadCount * 6; ++i)
        vertices[i].color = sf::Color::Red;

    for(size_t i = 0; i < quadCount; ++i)
    {
        particles.emplace_front(
            i,
            vertices,
            i * 6,
            this->positionGenerator(),
            velocityOffset + buildVector(this->velocityAngleGenerator(), this->velocityIntensityGenerator()),
            this->tickGenerator());
    }
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::draw(sf::RenderTarget &target, sf::RenderStates states)
    const
{
    target.draw(vertices, states);
}

void ParticleSystem::Update()
{
    auto toRemove = particles.before_begin();
    for(auto it = particles.begin(); it != particles.end();)
    {
        if(it->IsDead())
        {
            size_t id = it->GetId();
            it = particles.erase_after(toRemove);
            if(!stopped)
            {
                particles.emplace_front(
                    id,
                    vertices,
                    id * 6,
                    positionGenerator(),
                    velocityOffset + buildVector(velocityAngleGenerator(), velocityIntensityGenerator()), tickGenerator());
            }
        }
        else
        {
            it->Update();
            ++it;
            ++toRemove;
        }
    }
}

void ParticleSystem::Stop()
{
    stopped = true;
}

bool ParticleSystem::IsDone() const
{
    for(const auto &p : particles)
        if(!p.IsDead())
            return false;
    return true;
}

void ParticleSystem::SetVelocityOffset(const sf::Vector2f &velocity)
{
    velocityOffset = velocity;
}

