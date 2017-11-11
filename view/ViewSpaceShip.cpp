#include <ViewSpaceShip.h>
#include <Resources.h>

#include <iostream>

ViewSpaceShip::ViewSpaceShip(const SpaceShip &sp):
    spaceship(sp),
    thrustEnabled(false)
{
}

ViewSpaceShip::~ViewSpaceShip()
{
}

void ViewSpaceShip::CenterWindowView(sf::RenderWindow &window) const
{
    sf::Vector2u windowSize = window.getSize();
    sf::View view(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
    view.setCenter(spaceship.position);
    view.setRotation(spaceship.angle);
    window.setView(view);
}

void ViewSpaceShip::Update()
{
    const sf::Vector2f THRUST_POSITION_A = sf::Vector2f(-3, 13);
    const sf::Vector2f THRUST_POSITION_B = sf::Vector2f(3, 13);

    const float VELOCITY_ANGLE_A         = 85;
    const float VELOCITY_ANGLE_B         = 90;

    const float VELOCITY_INTENSITY_A     = 200;
    const float VELOCITY_INTENSITY_B     = 400;

    if(!thrustEnabled && spaceship.thrustEnabled)
    {
        particleSystems.emplace_front(
            256,
            spaceship.velocity,
            RandomVector2(THRUST_POSITION_A, THRUST_POSITION_B),
            RandomFloat(VELOCITY_ANGLE_A, VELOCITY_ANGLE_B),
            RandomFloat(VELOCITY_INTENSITY_A, VELOCITY_INTENSITY_B),
            RandomUint(15, 30));
    }
    else if(thrustEnabled && !spaceship.thrustEnabled)
    {
        for(auto ps : particleSystems)
            ps.Stop();
    }
    thrustEnabled = spaceship.thrustEnabled;

    for(auto it = particleSystems.begin(); it != particleSystems.end();)
    {
        sf::Transform matrix;
        matrix.rotate(-spaceship.angle);

        it->SetVelocityOffset(matrix.transformPoint(spaceship.velocity));
        it->Update();
        if(it->IsDone())
            it = particleSystems.erase_after(it);
        else
            ++it;
    }
}

void ViewSpaceShip::draw(sf::RenderTarget &target, sf::RenderStates states)
    const
{
    sf::Sprite sprite =
        Resources::CreateCenteredSprite(Resources::texSpaceships[0]);

    states.transform.translate(spaceship.position);
    states.transform.rotate(spaceship.angle);

    for(auto ps : particleSystems)
        target.draw(ps, states);

    target.draw(sprite, states);
}

