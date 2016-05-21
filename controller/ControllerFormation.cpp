#include <cmath>

#include <ControllerFormation.h>
#include <GameException.h>

const float EPSILON2     = 0.01f; // EPSILON = 0.1
const float MAX_VELOCITY = 2.f;
const float ONE_SQRT_2   = 0.707107f;

/*
static float dot(const sf::Vector2f &a, const sf::Vector2f &b)
{
    return a.x * b.x + a.y * b.y;
}

static float len2(const sf::Vector2f &v)
{
    return dot(v, v);
}
*/

inline float min(float a, float b)
{
    return a < b ? a : b;
}

ControllerFormation::ControllerFormation(Formation &f):
    formation(f)
{
}

ControllerFormation::~ControllerFormation()
{
}

void ControllerFormation::Update()
{
    if(!formation.leader)
        throw GameException("Formation has no leader");

    for(auto it : formation.slots)
    {
        if(!it.IsLeader())
        {
            sf::Vector2f targetLocal =
                formation.leader->localMatrix.transformPoint(
                        {formation.gridUnit.x * it.desc.gridX,
                         formation.gridUnit.y * it.desc.gridY}
                );

            sf::Vector2f targetWorld =
                formation.leader->GetNextPosition() + targetLocal;
            
            it.spaceship.GoToPoint(targetWorld, formation.leader->velocity);
        }
    }
}

