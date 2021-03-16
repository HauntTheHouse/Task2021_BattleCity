cmake_minimum_required(VERSION 3.0.0)
project(PlanetOfTanks VERSION 0.1.0)

include(CTest)
enable_testing()

find_library(SDL2 NAMES "SDL2")
find_library(SDL2main NAMES "SDL2main")
find_library(SDL2_image NAMES "SDL2_image")


add_executable(PlanetOfTanks ../Framework/src/launch.cpp src/game.cpp src/Object.h src/GameMap.cpp src/GameMap.h src/Wall.cpp src/Wall.h src/Tank.cpp src/Tank.h src/Bullet.cpp src/Bullet.h src/Boom.cpp src/Boom.h src/MovingObject.cpp src/MovingObject.h src/AnimatedObject.h src/StartedAnimation.cpp src/StartedAnimation.h src/Bonus.h src/Phoenix.h src/RightInterface.cpp src/RightInterface.h)

target_link_libraries(PlanetOfTanks SDL2 SDL2_image)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
