cmake_minimum_required(VERSION 3.22.1)
project(doodlejump)
set(CMAKE_CXX_STANDARD 17)
add_executable(doodlejump src/main.cpp
        src/Model/Entities/Player.cpp
        src/Model/Entities/Player.h
        src/Model/Entities/Platform.cpp
        src/Model/Entities/Platform.h
        src/Model/Entities/Entitymodel.cpp
        src/Model/Entities/Entitymodel.h
        src/View/ConcreteFactory.cpp
        src/View/ConcreteFactory.h
        src/Model/AbstractFactory.cpp
        src/Model/AbstractFactory.h
        src/Helper/StopWatch.cpp
        src/Helper/StopWatch.h
        src/Helper/Random.cpp
        src/Helper/Random.h
        src/Model/World.cpp
        src/Model/World.h
        src/Model/Entities/Subject.cpp
        src/Model/Entities/Subject.h
        src/Model/Entities/BGTile.cpp
        src/Model/Entities/BGTile.h
        src/Model/Entities/Bonus.cpp
        src/Model/Entities/Bonus.h
        src/Model/Enums.h
        src/Controller/PlayerController.cpp
        src/Controller/PlayerController.h
        src/Controller/PlatformController.cpp
        src/Controller/PlatformController.h
        src/Controller/CameraController.cpp
        src/Controller/CameraController.h
        src/View/PlayerView.cpp
        src/View/PlayerView.h
        src/View/PlatformView.cpp
        src/View/PlatformView.h
        src/Model/Observer.cpp
        src/Model/Observer.h
        src/View/EntitytView.cpp
        src/View/EntitytView.h
        src/Game.cpp
        src/Game.h
        src/Controller/EntityController.cpp
        src/Controller/EntityController.h
        src/Model/Camera.cpp
        src/Model/Camera.h
        src/View/BGTileView.cpp
        src/View/BGTileView.h
        src/View/BonusView.cpp
        src/View/BonusView.h
        src/Model/PlatformManager.cpp
        src/Model/PlatformManager.h
        src/Model/BonusManager.cpp
        src/Model/BonusManager.h
        src/Model/CollisionSystem.cpp
        src/Model/CollisionSystem.h
        src/Model/BGTileManager.cpp
        src/Model/BGTileManager.h
)
set(SFML_STATIC_LIBRARIES TRUE)
if (WIN32)
    set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")
elseif (UNIX)
    set(SFML_DIR "/usr/lib/cmake/SFML")
endif ()

find_package(SFML 2.5.1 COMPONENTS graphics window network audio REQUIRED)
include_directories("C:/SFML-2.5.1/include/SFML")
target_link_libraries(doodlejump sfml-window sfml-graphics sfml-network sfml-audio)
