#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Pawn.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Actor.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/private/game.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Projectile.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/private/Animation.cpp"

)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}/public"
)

