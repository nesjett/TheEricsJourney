# The project
This game was made by a team of 4 people, developed purely in C++ without libraries (appart of SFML) It took over a month to get to this result.

The project started as a subject project for Videogames Fundamentals at the University of Alicante and is non-profit.
The game implements interpolation, collision checking, bouncing, particle effects, interpolation, animations and many more mechanics that a game needs.

The code was also put into consideration during the design phase, making use of Composition, Fachade, State, and some other programming paradigms to ensure the system was consistent and extendible.

A more **detailed blog post** can be found at: [Nestor's Sabater portfolio](https://nsabater.com/the-erics-journey-a-c-game-made-from-scratch)

# Project sctructure
* **Main**: Main software container. "Application". 
* **GameInstance**: High-level manager object for an instance of the running game. It includes the game loop (tick) and main proccessing for the gameplay workflow.
* **Engine**: Interface for SFML abstraction. It includes Particle systems base, Interpolation tools among other base classes. 
* **Actor**: An Actor is any object that can be placed into a level. Actors are a generic Class that support 3D transformations such as translation, rotation, and scale. Actors can be created (spawned) and destroyed through gameplay code.
    * **Tile**
        * **Pushable**
    * **Pawn**: The Pawn class is the base class of all Actors that can be controlled by players or AI. A Pawn is the physical representation of a player or AI entity within the world. This not only means that the Pawn determines what the player or AI entity looks like visually, but also how it interacts with the world in terms of collisions and other physical
        * **Player**
        * **Enemy**
     * **Trap**
     * **Projectile**
* **AudioManager**: Class that handles queueing sound creation/destruction to cap the max simultaneous sounds allowed.




# Installation
## Linux

* sudo apt-get install libsfml-dev
* sudo apt-get install cmake
* sudo apt-get install clang

+ VSCode. We recommend installing the next plugins to use withing VSCode:
    * @id:ms-vscode.cpptools+
    * @id:vector-of-bool.cmake-tools


