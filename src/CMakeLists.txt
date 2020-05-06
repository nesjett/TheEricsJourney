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
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Player.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Controller.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/PlayerController.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Explosionenemy.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Fixedenemy.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Movingenemy.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Zombie.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Skeleton.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Stalker.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Door.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/private/enemies/BouncingBoss.cpp"

    
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Hud.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Mejora.cpp"


    "${CMAKE_CURRENT_SOURCE_DIR}/private/projectiles/FireBall.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/projectiles/Arrow.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/projectiles/Rock.cpp"


    "${CMAKE_CURRENT_SOURCE_DIR}/private/Trap.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/traps/Spikes.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/traps/Saw.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/private/particles/Fireball_Explosion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/particles/PlayerHit.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/private/particles/EfectoMejora.cpp"

)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}/public"
"${CMAKE_CURRENT_SOURCE_DIR}/public/projectiles"
)

