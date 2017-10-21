#include <cmath>

#include <SpaceShip.h>
#include <GameException.h>

#include <Utils.hpp>

// Uncomment to bypass spaceship physics IA
//#define NO_PHYSICS_IA

const float MAX_ANGULAR_VELOCITY = 5.f; // Degrees per frame
const float MAX_THRUST           = 12e3f;

SpaceShip::SpaceShip():
    angle(0.f)
{
}

SpaceShip::SpaceShip(const EntityID &i, float mass):
    Entity(i, ET_SPACESHIP, mass, true),
    angle(0.f)
{
}

SpaceShip::SpaceShip(const SpaceShip &spaceship):
    Entity(spaceship),
    angle(spaceship.angle),
    localMatrix(spaceship.localMatrix)
{
}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::Rotate(float angleDegrees)
{
    angleDegrees = clamp(angleDegrees, -MAX_ANGULAR_VELOCITY, MAX_ANGULAR_VELOCITY);
    localMatrix.rotate(angleDegrees);
    angle += angleDegrees;
}

sf::Vector2f SpaceShip::ChangeDirection(const sf::Vector2f &targetDirection)
{
    // Here, direction = thrust direction, not velocity direction
    sf::Vector2f currentDirection = localMatrix.transformPoint({0, -1});
    float cosineAngleToAdd = dot(currentDirection, targetDirection);
    float sineAngleToAdd = crossZ(currentDirection, targetDirection);
    
    // Values are not perfect when current direction and target direction are
    // already the same
    if(cosineAngleToAdd > 1)
        cosineAngleToAdd = 1;
    else if(cosineAngleToAdd < -1)
        cosineAngleToAdd = -1;   

    float angleToAdd = acos(cosineAngleToAdd) * 180.f / M_PI;

    if(sineAngleToAdd < 0) // When sine is negative, the actual angle must be
                           // the opposite (cosine won't change)
    {
        angleToAdd = -angleToAdd;
    }

    // At this point, angleToAdd belongs to [-180,180] deg
    
#ifdef NO_PHYSICS_IA
#else
    // Clamp angleToAdd into range [MAX_ANGULAR_VELOCITY, MAX_ANGULAR_VELOCITY]
    angleToAdd = clamp(angleToAdd, -MAX_ANGULAR_VELOCITY, MAX_ANGULAR_VELOCITY);
#endif

    localMatrix.rotate(angleToAdd);
    angle += angleToAdd;

    return localMatrix.transformPoint({0, -1});
}

void SpaceShip::GoToPoint(const sf::Vector2f &destination,
                          const sf::Vector2f &targetVelocity)
{
    const float FORESEEN_FRAMES = 60;

    sf::Vector2f anticipatedDest    = 
        destination + targetVelocity * (FORESEEN_FRAMES * Entity::FRAME_DT);
    sf::Vector2f idealVelocity      =
        (anticipatedDest - position) / (FORESEEN_FRAMES * Entity::FRAME_DT);
    sf::Vector2f targetAcceleration =
        (idealVelocity - velocity) / Entity::FRAME_DT;

    sf::Vector2f idealForce         =
        mass * (targetAcceleration - builtAcceleration - acceleration);

    generateForce(idealForce);
}

void SpaceShip::FollowOrbit(const Planet &planet)
{
    sf::Vector2f idealVelocity = planet.OrbitVelocityAt(position);
    
    // Orbit must rotate in the same direction than current velocity
    if(dot(velocity, idealVelocity) < 0.f)
        idealVelocity = idealVelocity * -1.f;

    sf::Vector2f targetAcceleration =
        (idealVelocity - velocity) / Entity::FRAME_DT;

    sf::Vector2f idealForce         =
        mass * (targetAcceleration - builtAcceleration - acceleration);

    generateForce(idealForce);
}

void SpaceShip::Thrust(float thrustIntensity)
{
    // {0, -1} is the default direction since spaceship textures are oriented
    // towards the upper border
    sf::Vector2f direction = localMatrix.transformPoint({0, -1});
    
#ifdef NO_PHYSICS_IA
    // Why?
    thrustIntensity /= 2.f;
#else
    thrustIntensity = clamp(thrustIntensity, -MAX_THRUST, MAX_THRUST);
#endif
    
    // Transform force into acceleration
    AddAcceleration(direction * (thrustIntensity / mass));
}

sf::Packet &SpaceShip::WriteToPacket(sf::Packet &packet) const
{
    packet << angle;
    return Entity::WriteToPacket(packet);
}

sf::Packet &SpaceShip::ReadFromPacket(sf::Packet &packet)
{
    packet >> angle;
    return Entity::ReadFromPacket(packet);
}

Entity *SpaceShip::Copy() const
{
    Entity *ret = new SpaceShip(*this);
    if(ret == nullptr)
        throw GameException("Cannot allocate SpaceShip");
    return ret;
}

void SpaceShip::generateForce(const sf::Vector2f &idealForce)
{
    float idealForceLen2 = len2(idealForce);

    if(idealForceLen2 > EPSILON * EPSILON) // Thrust required
    {
        float thrustIntensity = sqrt(idealForceLen2);

        // Normalize direction
        sf::Vector2f thrustDirection = idealForce / thrustIntensity;

        // Rotate spaceship
        sf::Vector2f realDirection =
            ChangeDirection(thrustDirection);

        // Thrust engines only when the spaceship is almost aligned with ideal
        // thrust direction
        float product = dot(realDirection, thrustDirection);
        if(product > .9f)
        {
            Thrust(thrustIntensity);
        }
    }
}
