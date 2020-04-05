Class hierarchy:  
GameInstance (SIngleton)
Sprite (interface for smfl)
Actor  (Base class for everything that has a visible representation in the world, like enemies, traps, walls...)
- Pawn  (Base class for characters)
-- Enemy  (Enemy characters)
-- Player 
# Project sctructure
* **Main**: Main software container. "Application"
* **GameInstance**: High-level manager object for an instance of the running game
* **Engine**: Interface for SFML abstraction
* **Actor**: An Actor is any object that can be placed into a level. Actors are a generic Class that support 3D transformations such as translation, rotation, and scale. Actors can be created (spawned) and destroyed through gameplay code.
    * **Tile**
        * **Pushable**
    * **Pawn**: The Pawn class is the base class of all Actors that can be controlled by players or AI. A Pawn is the physical representation of a player or AI entity within the world. This not only means that the Pawn determines what the player or AI entity looks like visually, but also how it interacts with the world in terms of collisions and other physical
        * **Player**
        * **Enemy**



# Instalación
Este proyecto requiere la instalación de las siguientes librerias/aplicaciones

## Mac

    * VSCode. Dentro de el mismo se requieren los siguientes plugins. Estos se buscan en el apartado de plugins de la barra de la izquierda (la L formada de 3 cajas)
        - @id:ms-vscode.cpptools+
        - @id:vector-of-bool.cmake-tools

    * Instalar las utilidades de línea de comandos (compilador) mac: `xcode-select --install`. Comprobar que tenemos instalado el compilador clang (`clang++ -v`)

    * Instalar brew: https://brew.sh/index_es
    * Instalar los siguientes paquetes dentro de brew:
        - brew install cmake
        - brew install sfml
        - brew install gcc (solo si no se puede instalar clang o se desea gcc como compilador)


## Linux

* sudo apt-get install libsfml-dev
* sudo apt-get install cmake
* sudo apt-get install clang

+ VSCode. Dentro de el mismo se requieren los siguientes plugins. Estos se buscan en el apartado de plugins de la barra de la izquierda (la L formada de 3 cajas)
    * @id:ms-vscode.cpptools+
    * @id:vector-of-bool.cmake-tools

# CMAKE
Para incluir SFML en el proyecto, propongo la siguiente plantilla. Esta depende de si SFML es >= 2.5 o no. Aquí adjunto las dos versiones (la versión de 2.4 también va en 2.5 por ahora)


## cmake sfml 2.5

    cmake_minimum_required(VERSION 2.8)

    project(prueba)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra")


    find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
    add_executable(prueba main.cpp)
    target_link_libraries(prueba sfml-graphics sfml-audio)


## cmake sfml 2.4

    cmake_minimum_required(VERSION 2.8)

    project(prueba)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra")

    add_executable(prueba main.cpp)

    set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
    find_package(SFML REQUIRED system window graphics network audio)
    if (SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIR})
        target_link_libraries(prueba ${SFML_LIBRARIES})
    endif()

