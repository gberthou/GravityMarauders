#ifndef CONTROLLER_FORMATION
#define CONTROLLER_FORMATION

#include <Formation.h>

class ControllerFormation
{
    public:
        ControllerFormation(Formation &formation);
        virtual ~ControllerFormation();

        void Update();
        void Update(const sf::Event &event);

    protected:
        Formation &formation;
};

#endif

