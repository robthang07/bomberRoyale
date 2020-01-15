cmake_minimum_required(VERSION 3.12)
project(Bomber_Royale)

set(CMAKE_CXX_STANDARD 14)

add_executable(Bomber_Royale main.cpp gamestates/machine.cpp gamestates/machine.h gamestates/state.h config.h
        gamestates/stateMainMenu.cpp gamestates/stateMainMenu.h gamestates/stateGameScreen.cpp
        gamestates/stateGameScreen.h gamestates/stateScoreScreen.cpp gamestates/stateScoreScreen.h
        gamestates/statePauseScreen.cpp gamestates/statePauseScreen.h gamestates/gamestatesdata/mainmenuData.h
        gamestates/gamestatesdata/stateData.h gamestates/gamestatesdata/gamescreenData.h
        gamestates/gamestatesdata/pausescreenData.h gamestates/gamestatesdata/scorescreenData.h
        gamestates/gamestatesdata/gamescreenData.cpp gamestates/gamestatesdata/mainmenuData.cpp
        gamestates/gamestatesdata/pausescreenData.cpp gamestates/gamestatesdata/scorescreenData.cpp
        gamestates/mainmenustates/mainMenuMachine.cpp gamestates/mainmenustates/mainMenuMachine.h
        config.cpp objects/BaseObject.cpp objects/BaseObject.h objects/Player.cpp objects/Player.h
        objects/Bomb.cpp objects/Bomb.h
        layers/layers.cpp layers/layers.h layers/map.cpp layers/map.h
        design.cpp design.h
        objects/object.h objects/sprite.cpp objects/sprite.h
        jsonobjects/highscores.cpp jsonobjects/highscores.h jsonobjects/credits.cpp jsonobjects/credits.h
        functions/controllers/menuControler.cpp functions/controllers/menuControler.h
        functions/calculators/bombPlacement.cpp functions/calculators/bombPlacement.h
        functions/detectors/collision.cpp functions/detectors/collision.h objects/powerups/basePowerUps.cpp
        objects/powerups/basePowerUps.h objects/powerups/powerUpHP.cpp objects/powerups/powerUpHP.h
        objects/powerups/powerUpSpeed.cpp objects/powerups/powerUpSpeed.h
        objects/powerups/bombPU.cpp objects/powerups/bombPU.h
        functions/calculators/playerPositions.cpp functions/calculators/playerPositions.h
        functions/calculators/baseAI.cpp functions/calculators/baseAI.h
        objects/powerups/powerUpBombPower.cpp objects/powerups/powerUpBombPower.h functions/animation/animation.cpp functions/animation/animation.h functions/scoresystem/scoreSystem.cpp functions/scoresystem/scoreSystem.h)


target_link_libraries(Bomber_Royale tgui jsoncpp sfml-graphics sfml-window sfml-system sfml-audio)