#include "../include/Gameplay.h"

// Logic proccesing

void Logic(Game* currentGame, float deltaTime, MAP& Map) {

    MediatorCreepBall mediator;
    // Tower state update

    for (auto t : currentGame->Towers) {
        if (t->Timer > 0) {
            t->Timer -= deltaTime;
        }
        else {
            for (auto& Creep : currentGame->Creeps){
                auto& creep = Creep.first;
                float deltaX = findCentre(t->getBody().gGB()).x - findCentre(creep.getBody().gGB()).x;
                float deltaY = findCentre(t->getBody().gGB()).y - findCentre(creep.getBody().gGB()).y;
                if (sqrt(deltaX * deltaX + deltaY * deltaY) <= t->getArea().getRad()) {
                    t->Fire(Creep);
                    break;
                }
            }
        }
    }

    // Creep state update

    for (unsigned int i = 0; i < currentGame->Creeps.size(); i++) {
        checkDir(currentGame->Creeps[i].first, Map.Road);
    }

    // Ball flight proccesing
    
    for (auto& Creep : currentGame->Creeps) {
        auto& creep = Creep.first;
        creep.Update(deltaTime);
        mediator.processFlight(Creep, deltaTime);
    }

    // Getting damage

    for (int i = 0; i < currentGame->Creeps.size(); i++) {
        auto& creep = currentGame->Creeps[i].first;
        Vector<float> creepPos = { findCentre(creep.getBody().gGB()).x, findCentre(creep.getBody().gGB()).y };
        Vector<float> endPos = { Map.Road[Map.endNumb].first.getPos().x + blockSize.x, Map.Road[Map.endNumb].first.getPos().y + blockSize.y / 2 };

        if (epsCirclePos(creepPos, endPos)) {
            creep.Arrived();
            creep.setHealth(-creep.getHealth());
            currentGame->decr_playerHealth();
        }
        if (creep.getHealth() <= 0) {

            if (creep.isKilled()) { currentGame->set_playerGold(creep.getReward()); }
            creep.killCreep(currentGame->Creeps, currentGame->Dead, i, deltaTime);
        }
    }

    // Preparing creep death animation

    for (int i = 0; i < currentGame->Dead.size(); i++) {
        auto& dead = currentGame->Dead[i];
        dead.second -= deltaTime;
        dead.first.Update(deltaTime);
        if (dead.second <= 0) {
            currentGame->Dead.erase(currentGame->Dead.begin() + i);
        }
    }

    // Tower animation proccesing

    for (auto& tower : currentGame->Towers) {
        tower->Update(deltaTime);
    }
}

// Starting the gameplay and creating general objects

void Gameplay(unsigned int roundsToWin, userRenderWindow& Window, const GameSettings& gameSettings) {
    srand(static_cast <unsigned int> (time(0)));

    Game* currentGame = Game::get_instance();
    currentGame->startGame(gameSettings.Hard);
    int gameSpeed = 1;
    bool gameStop = false;

    // Initialization of textures, music and font

    userImages tSameer, tBatyr, tSingle, tMulti, tFreezing, tOnePunch, tGameOver, tHGround, tGrass, tVGround, tURGround, tDRGround, tULGround, tDLGround, tJegor;
    std::vector <userImages> Textures = { tSameer, tBatyr, tSingle, tMulti, tFreezing, tOnePunch, tGameOver, tHGround, tGrass, tVGround, tURGround, tDRGround, tULGround, tDLGround, tJegor};

    const std::vector <std::string> texturePath = { "images/Sameer2.0.png",
                                                    "images/Batyr2.0.png",
                                                    "images/SingleTower.png",
                                                    "images/MultiTower.png",
                                                    "images/FreezingTower.png",
                                                    "images/OnePunchMan.png",
                                                    "images/GameOver.png",
                                                    "images/GrassGround.png",
                                                    "images/HGround.png",
                                                    "images/VGround.png",
                                                    "images/URGround.png",
                                                    "images/DRGround.png",
                                                    "images/DLGround.png",
                                                    "images/ULGround.png",
                                                    "images/Jegor.png" };

    loadTexture(Textures, texturePath);
    userFont Font;
    Font.loadFromFile("images/Classic.ttf");
    int buttonCheck = -1;
    userMusic Music;
    Music.playMusic("images/music.ogg");
    userColor Blue = userColor(0, 0, 255, 25);

    MAP Map;
    createMap(Map, gameSettings, Textures);

    userSprite sGameOver(Textures[6]);
    sGameOver.setPos(gameOverPosition.x, gameOverPosition.y);

    float deltaTime;
    userClock Clock;
    int healthPrev = currentGame->get_playerHealth();

    while (Window.windowOpen()) {

        unsigned int winWave = 0;

        for (unsigned int i = 0; i < roundsToWin; ++i) {
            // Main loop
            float releaseTime = 0.5f;
            float waitingTime = 10;
            int cnt;
            if (currentGame->get_difficulty()) cnt = 2 * currentGame->get_waveNumber() + 1;
            else cnt = currentGame->get_waveNumber();
            Visualize(currentGame, Window, sGameOver, Map, Blue, buttonCheck, Font);

            while (waitingTime > 0) {
                if (gameStop) {
                    deltaTime = gameSpeed * Clock.restart().asSeconds();
                    checkSpeed(gameSpeed, gameStop, currentGame, deltaTime);
                    continue;
                }
                if (currentGame->get_gameOver()) break;
                deltaTime = gameSpeed * Clock.restart().asSeconds();
                waitingTime -= deltaTime;
                userEvent e;
                while (Window.pollEvent(e))
                    if (e.type == userEvent::Closed) {
                        Window.close();
                        towerClear(currentGame->Towers);
                        exit(0);
                    }
                checkPress(currentGame, Window, Map.Grass, buttonCheck, Textures);
                checkSpeed(gameSpeed, gameStop, currentGame, deltaTime);

                for (unsigned int i = 0; i < currentGame->Towers.size(); i++) {
                    currentGame->Towers[i]->Update(deltaTime);
                }
                Visualize(currentGame, Window, sGameOver, Map, Blue, buttonCheck, Font);

            }

            buttonCheck = -1;

            while (!currentGame->Creeps.empty() || !currentGame->Dead.empty() || cnt != 0) {
                if (gameStop) {
                    deltaTime = gameSpeed * Clock.restart().asSeconds();
                    checkSpeed(gameSpeed, gameStop, currentGame, deltaTime);
                    continue;
                }
                userEvent e;

                while (Window.pollEvent(e))
                    if (e.type == userEvent::Closed) {
                        Window.close();
                        towerClear(currentGame->Towers);
                        exit(0);
                    }
                checkSpeed(gameSpeed, gameStop, currentGame, deltaTime);
                deltaTime = gameSpeed * Clock.restart().asSeconds();
                if (cnt != 0) fillCreep(currentGame, Map, releaseTime, deltaTime, cnt, Textures[0], Textures[1], Textures[14]);
                Logic(currentGame, deltaTime, Map);
                if (currentGame->get_gameOver()) break;
                if (currentGame->get_playerHealth() <= 0) {
                    currentGame->switch_gameOver();
                    break;
                }
                Visualize(currentGame, Window, sGameOver, Map, Blue, buttonCheck, Font);
            }
            if (currentGame->get_gameOver()) {
                currentGame->Creeps.clear();
                currentGame->Towers.clear();
                currentGame->Dead.clear();
                break;
            }
            else if (healthPrev == currentGame->get_playerHealth()) {
                winWave++;
            }
            else
                winWave = 0;
            healthPrev = currentGame->get_playerHealth();
            currentGame->set_playerGold(winWave * winWaveGold);
            currentGame->incr_waveNumber();
        }
        while (currentGame->get_gameOver()) {
            deltaTime = gameSpeed * Clock.restart().asSeconds();
            static float gameOverTime = 0;
            gameOverTime += deltaTime;
            if (gameOverTime > 5) {
                gameOverTime = 0;
                break;
            }
            userEvent e;
            while (Window.pollEvent(e))
                if (e.type == userEvent::Closed) {
                    Window.close();
                    towerClear(currentGame->Towers);
                    exit(0);
                }
            Visualize(currentGame, Window, sGameOver, Map, Blue, buttonCheck, Font);
        }
        break;
    }
}
