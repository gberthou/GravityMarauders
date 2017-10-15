#include <cmath>

#include <SpaceShip.h>
#include <GameException.h>

// Uncomment to bypass spaceship physics IA
//#define NO_PHYSICS_IA

const float MAX_ANGULAR_VELOCITY = 60.f; // Degrees per frame
const float EPSILON2             = .01;
const float ONE_SQRT_2           = 0.707107f;
const float MAX_THRUST           = 12e3f;

static float dot(const sf::Vector2f &a, const sf::Vector2f &b)
{
    return a.x * b.x + a.y * b.y;
}

static float len2(const sf::Vector2f &v)
{
    return dot(v, v);
}

// Computes cross product of a and b and returns z corrdinate
static float crossZ(const sf::Vector2f &a, const sf::Vector2f &b)
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
    // Clip angleToAdd into range [MAX_ANGULAR_VELOCITY, MAX_ANGULAR_VELOCITY]
    if(angleToAdd >= 0)
        angleToAdd = min(angleToAdd, MAX_ANGULAR_VELOCITY);
    else // angleToAdd < 0
        angleToAdd = max(angleToAdd, -MAX_ANGULAR_VELOCITY);
#endif

    localMatrix.rotate(angleToAdd);
    angle += angleToAdd;

    return localMatrix.transformPoint({0, -1});
}

void SpaceShip::GoToPoint(const sf::Vector2f &destination,
                          const sf::Vector2f &targetVelocity)
{
    const float FORESEEN_FRAMES = 60;

    sf::Vector2f anticipatedDest = 
        destination + targetVelocity * (FORESEEN_FRAMES * Entity::FRAME_DT);
    sf::Vector2f idealVelocity = (anticipatedDest - position) / (FORESEEN_FRAMES * Entity::FRAME_DT);
    sf::Vector2f targetAcceleration = (idealVelocity - velocity) / Entity::FRAME_DT;

    sf::Vector2f idealForce = mass * (targetAcceleration - builtAcceleration - acceleration);

    float idealForceLen2 = len2(idealForce);

    if(idealForceLen2 > EPSILON2) // Thrust required
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

void SpaceShip::Thrust(float thrustIntensity)
{
    // {0, -1} is the default direction since spaceship textures are oriented
    // towards the upper border
    sf::Vector2f direction = localMatrix.transformPoint({0, -1});
    
#ifdef NO_PHYSICS_IA
    // Why?
    thrustIntensity /= 2.f;
#else
    if(thrustIntensity >= 0)
        thrustIntensity = min(thrustIntensity, MAX_THRUST);
    else
        thrustIntensity = max(thrustIntensity, -MAX_THRUST);
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

