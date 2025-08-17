cmake_minimum_required(VERSION 3.28.3)

project(AP-DoodleJump)

if (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(SFML_DIR "C:/SFML-2.6.1/lib/cmake/SFML")
elseif (UNIX)
    set(SFML_DIR "/usr/lib/cmake/SFML")
endif()

find_package(SFML 2.6.1 COMPONENTS graphics window network audio REQUIRED)

add_executable(AP-DoodleJump
        src/main.cpp
        src/base/Controller.cpp
        src/base/Model.cpp
        src/base/Observer.cpp
        src/base/View.cpp
        src/bgtile/BGTileModel.cpp
        src/bgtile/BGTileView.cpp
        src/bgtile/BGTileObserver.cpp
        src/bonus/jetpack/JetpackController.cpp
        src/bonus/jetpack/JetpackModel.cpp
        src/bonus/jetpack/JetpackObserver.cpp
        src/bonus/jetpack/JetpackView.cpp
        src/bonus/spring/SpringController.cpp
        src/bonus/spring/SpringModel.cpp
        src/bonus/spring/SpringObserver.cpp
        src/bonus/spring/SpringView.cpp
        src/bonus/BonusController.cpp
        src/bonus/BonusModel.cpp
        src/bonus/BonusObserver.cpp
        src/bonus/BonusView.cpp
        src/camera/Camera.cpp
        src/factory/EntityFactoryAbstract.h
        src/factory/EntityFactory.cpp
        src/game/Game.cpp
        src/player/PlayerController.cpp
        src/player/PlayerModel.cpp
        src/player/PlayerObserver.cpp
        src/player/PlayerView.cpp
        src/platform/PlatformController.cpp
        src/platform/PlatformModel.cpp
        src/platform/PlatformObserver.cpp
        src/platform/PlatformType.h
        src/platform/PlatformView.cpp
        src/score/Score.cpp
        src/score/ScoreView.cpp
        src/base/Collidable.h
        src/util/Config.h
        src/util/Coordinate.h
        src/util/Random.cpp
        src/util/Stopwatch.cpp
        src/world/World.cpp)

target_link_libraries(AP-DoodleJump sfml-window sfml-graphics sfml-network sfml-audio)