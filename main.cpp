#include <iostream>

#include <SFML/Graphics.hpp>

#include <GameException.h>
#include <Resources.h>
#include <ControllerSpaceShipUserKeyboard.h>
#include <ControllerFormation.h>
#include <ControllerEntityManager.h>
#include <ControllerFormationOrbit.h>
#include <Snapshot.h>
#include <SnapshotHistory.h>
#include <EntityManager.h>

#ifndef SERVER
#include <Client.h>
#include <ViewFormation.h>
#include <ViewSpaceShip.h>
#include <ViewMap.h>
#include <ViewEntityManager.h>
#include <ViewFormationTrack.h>
#include <ViewMinimap.h>

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
        || !client.WaitForInfoTransferred(sf::seconds(3))
        || !client.WaitForGameReady(sf::seconds(3)))
            throw GameException("No response from server");

        sf::RenderWindow window(sf::VideoMode(800, 600), "GravityMarauders");

        ControllerFormationOrbit orbitController(formation, map);
        ViewEntityManager viewEntityManager(entityManager);

        window.setFramerateLimit(120);
        window.setVerticalSyncEnabled(true);
        while(window.isOpen())
        {
            sf::Event event;
            while(window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                    window.close();
               
                ControllerFormation(formation).Update(event);
                orbitController.Update(event);
            }

            // Compute forces, must be called at the beginning
            entityManager.ApplyGravity(map);

            // AI computations
            if(formation.IsValid())
                ControllerFormation(formation).Update();

            // Entity controllers must be updated at the end
            ControllerEntityManager(entityManager).Update();
            orbitController.Update();

            // Update views
            viewEntityManager.Update();

            window.clear();
            ViewFormation(formation).CenterView(window);
            window.draw(ViewMap(map));
            window.draw(viewEntityManager);
            //window.draw(ViewFormation(formation)); // Debug only
            window.draw(ViewFormationTrack(formation, map));

            ViewMinimap vMinimap(200, 200, map, formation);
            vMinimap.ApplyView(window);
            window.draw(vMinimap);
            window.display();

            client.Receive();
        }
    }
    catch(const GameException &e)
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
        
        planet0->MoveTo({6000, -1000});
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
            entityManager.ApplyGravity(map);
            
            // AI computations
            //cFormation.Update();

            // Entity controllers must be updated at the end
            ControllerEntityManager(entityManager).Update();
            
            server.Receive();

            // FPS control
            sf::sleep(sf::milliseconds(10));
        }
    }
    catch(const GameException &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
#endif

