# Gravity Marauders

Simple 2D demo game that involves spaceships and gravity.
Spaceships are organized in formations, like squadron formations.
While the user controls the main spaceship of their formation using keyboard, the other spaceships of their formation keep their positions within the formation.

## Controls

Keyboard:

 - Left/right arrows: change orientation
 - Spacebar: thrust
 - O: automated orbit around the nearest planet

## Quickstart

*Gravity Marauders* requires **SFML 2.4.2-3** as a dependence. Earlier versions of SFML might work as well, however this demo was developed using version 2.4.2-3.

To build the game, run:
```
make build GMServer GravityMarauders
```
This operation may take some time to complete.

When the game is built, run an instance of the server using `./GMServer`.
Once the server is on, run an instance of the client using `./GravityMarauders`.
