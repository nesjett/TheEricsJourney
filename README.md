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


