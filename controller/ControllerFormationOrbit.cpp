#include <ControllerFormationOrbit.h>

ControllerFormationOrbit::ControllerFormationOrbit(Formation &f, const Map &m):
    formation(f),
    map(m),
    enabled(false),
    targetPlanet(nullptr)
{
}

ControllerFormationOrbit::~ControllerFormationOrbit()
{
}

void ControllerFormationOrbit::Update()
{
    if(enabled)
        formation.leader->FollowOrbit(*targetPlanet);
}

void ControllerFormationOrbit::Update(const sf::Event &event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::O)
        {
            // Toggle auto orbit mode
            enabled = !enabled;
            if(enabled)
                targetPlanet = &map.ClosestPlanetTo(formation.leader->GetPosition());
        }
    }
}

