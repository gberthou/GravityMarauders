#include <iostream>
#include <cmath>

#include <SpaceShip.h>

const float MAX_ANGULAR_VELOCITY = 5.f; // Degrees per frame
const float EPSILON2             = .01;
const float ONE_SQRT_2           = 0.707107f;
const float MAX_THRUST           = 60.f;

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

/*
static float sgn(float x)
{
    if(x < 0)
        return -1;
    if(x > 0)
        return 1;
    return 0;
}
*/

inline float min(float a, float b)
{
    return a < b ? a : b;
}

inline float max(float a, float b)
{
    return a < b ? b : a;
}

SpaceShip::SpaceShip(const EntityID &i, float mass):
    Entity(i, mass, true),
    angle(0.f)
{
}

SpaceShip::~SpaceShip()
{
}

/*
void SpaceShip::ChangeDirection(TargetDirection targetDirection)
{
    const float TARGET_ANGULARS[] = {0.f, 180.f, 270.f, 90.f};
    
    float targetAngle = TARGET_ANGULARS[targetDirection];
    float deltaAngle = targetAngle - angle;

    if(deltaAngle > 180.f)
    {
        angle += 360.f;
        deltaAngle = -360.f + deltaAngle;
    }
    else if(deltaAngle < -180.f)
    {
        angle -= 360.f;
        deltaAngle = 360.f + deltaAngle; 
    }

    float angleToAdd =
        min(fabs(deltaAngle), MAX_ANGULAR_VELOCITY) * sgn(deltaAngle);

    localMatrix.rotate(angleToAdd);
    angle += angleToAdd;
}
*/

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
    
    // Clip angleToAdd into range [MAX_ANGULAR_VELOCITY, MAX_ANGULAR_VELOCITY]
    if(angleToAdd >= 0)
        angleToAdd = min(angleToAdd, MAX_ANGULAR_VELOCITY);
    else // angleToAdd < 0
        angleToAdd = max(angleToAdd, -MAX_ANGULAR_VELOCITY);

    localMatrix.rotate(angleToAdd);
    angle += angleToAdd;
    
    return localMatrix.transformPoint({0, -1});
}

void SpaceShip::GoToPoint(const sf::Vector2f &destination,
                          const sf::Vector2f &targetVelocity)
{
    const float T      = 1;
    const float SQRT_T = 1;

    // Based on p = 0.5 * (acc0 + accToAdd) * t*t + vel0 * t + p0
    // Hypothesis: constant acceleration, constant velocity
    

    const float ANTICIPATION_FACTOR = 120;
    sf::Vector2f anticipatedDest =
        destination + targetVelocity * Entity::FRAME_DT * ANTICIPATION_FACTOR;
        
    sf::Vector2f accelerationToAdd =
        ((anticipatedDest - position) / T - velocity / SQRT_T) * 2.f
        - acceleration;

    float accelerationToAddLen2 = len2(accelerationToAdd);

    if(accelerationToAddLen2 > EPSILON2) // Thrust required
    {
        float thrustIntensity = sqrt(accelerationToAddLen2);

        // Normalize direction
        sf::Vector2f thrustDirection = accelerationToAdd / thrustIntensity;

        // Rotate spaceship
        sf::Vector2f realDirection =
            ChangeDirection(thrustDirection);

        // Thrust engines only when the angle is less than 45 deg
        if(dot(realDirection, thrustDirection) > ONE_SQRT_2)
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
    
    if(thrustIntensity >= 0)
        AddAcceleration(direction * min(thrustIntensity, MAX_THRUST));
    else
        AddAcceleration(direction * max(thrustIntensity, -MAX_THRUST));
}

