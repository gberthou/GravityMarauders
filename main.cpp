#include <iostream>

#include <SFML/Graphics.hpp>

#include <GameException.h>
#include <Resources.h>
#include <ControllerSpaceShipUserKeyboard.h>
#include <ControllerFormation.h>
#include <ControllerEntity.h>
#include <Snapshot.h>
#include <SnapshotHistory.h>
#include <EntityManager.h>

#ifndef SERVER
#include <Client.h>
#include <ViewFormation.h>
#include <ViewSpaceShip.h>
#include <ViewMap.h>
#include <ViewEntityManager.h>

int main(void)
{
    try
    {
        Resources::LoadTextures();

        EntityManager entityManager;

        // Create empty map (to be received from server)
        Map map;

        // Create formation (to be sent to server)
        Formation formation({96, 96});
        formation.AddSlotDescriptor(0, 0);
        formation.AddSlotDescriptor(1, 1);
        formation.AddSlotDescriptor(-1, -1);

        // Create client
        Client client("127.0.0.1", entityManager, map, formation);

        std::cout << "Waiting for server..." << std::endl;
        client.Connect();
        if(!client.WaitForConnectionAck(sf::seconds(3))
        || !client.WaitForMap(sf::seconds(3))
        || !client.WaitForInfoTransferred(sf::seconds(3)))
            throw GameException("No response from server");

        sf::RenderWindow window(sf::VideoMode(800, 600), "GravityMarauders");

        // Build formation
        /*
        SpaceShip spaceship(200);
        SpaceShip spaceshipSlaves[] = {200, 200};
        spaceship.MoveTo({300, 300});
        */

        // Populate snapshot
        /*
        Snapshot snapshot;
        snapshot.AddEntity(spaceship);
        snapshot.AddEntity(spaceshipSlaves[0]);
        snapshot.AddEntity(spaceshipSlaves[1]);
        */

        // Create views
        ViewMap vMap(map);

        // Create controllers
        /*
        ControllerSpaceShipUserKeyboard cSpaceship(spaceship);
        ControllerFormation cFormation(formation);
        ControllerEntity cEntity(spaceship);
        ControllerEntity cEntitySlaves[] = {spaceshipSlaves[0], spaceshipSlaves[1]};
        */

        window.setFramerateLimit(120);
        while(window.isOpen())
        {
            sf::Event event;
            while(window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                    window.close();
                
                //cSpaceship.Update(event);
            }

            // Compute forces, must be called at the beginning
            /*
            map.ApplyGravityTo(spaceship);
            map.ApplyGravityTo(spaceshipSlaves[0]);
            map.ApplyGravityTo(spaceshipSlaves[1]);
            */
            client.UpdateControllers();

            // AI computations
            //cFormation.Update();

            // Entity controllers must be updated at the end
            /*
            cEntity.Update();
            cEntitySlaves[0].Update();
            cEntitySlaves[1].Update();
            */

            window.clear();
            ViewFormation(formation).CenterView(window);
            //ViewSpaceShip(spaceship).CenterWindowView(window);
            window.draw(vMap);
            window.draw(ViewEntityManager(entityManager));
            window.display();

            client.Receive();
        }
    }
    catch(GameException e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

#else // SERVER
#include <Server.h>

int main(void)
{
    try
    {
        std::cout << "Initialization..." << std::endl;

        EntityManager entityManager;

        // Build map
        Planet *planet0 = entityManager.AddPlanet(1, 2000);
        Planet *planet1 = entityManager.AddPlanet(1, 1500);
        
        planet0->MoveTo({2300, -1000});
        planet1->MoveTo({-1300, 1100});
        
        Map map;
        map.AddPlanet(*planet0);
        map.AddPlanet(*planet1);
        
        Server server(entityManager, map);

        std::cout << "Server is fully initialized!" << std::endl;

        // Create controllers
        //ControllerSpaceShipUserKeyboard cSpaceship(spaceship);

        for(;;)
        {
            // Compute forces, must be called at the beginning
            
            // AI computations
            //cFormation.Update();

            // Entity controllers must be updated at the end
            
            server.Receive();

            // FPS control
            sf::sleep(sf::milliseconds(100));
        }
    }
    catch(std::exception e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
#endif

