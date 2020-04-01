#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/private/tinyxml2.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Menu.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Engine.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Pawn.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Actor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Tile.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Mapa.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/AudioManager.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/private/game.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Projectile.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Enemy.cpp"

)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}/public"
)

