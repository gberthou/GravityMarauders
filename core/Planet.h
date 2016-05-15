#ifndef PLANET_H
#define PLANET_H

#include <Entity.h>

class Planet: public Entity
{
    public:
        Planet(float density, float radius);
        virtual ~Planet();

        void ApplyGravityTo(Entity &entity) const;

    protected:
        float radius;

        friend class ViewPlanet;
};

#endif

