cmake_minimum_required(VERSION 3.28.3)
project(doodlejump)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(doodlejump
        src/main.cpp
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
    set(SFML_DIR "C:/SFML-2.6.1/lib/cmake/SFML")
elseif (UNIX)
    set(SFML_DIR "/usr/lib/cmake/SFML")
endif ()
# Find SFML
find_package(SFML 2.6.1 COMPONENTS graphics window system audio REQUIRED)

# Link SFML libraries
target_link_libraries(doodlejump sfml-graphics sfml-window sfml-network sfml-audio)