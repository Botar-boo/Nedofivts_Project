#pragma once
#include "Gameplay.h"


// Logic proccesing

void Logic(Game* currentGame, std::vector <Tower*>& Towers, std::vector <Creep>& Creeps, std::vector <std::pair<Creep, float>>& Dead, float deltaTime, MAP& Map) {

    // Tower state update

    for (auto t : Towers) {
        if (t->Timer > 0) {
            t->Timer -= deltaTime;
        }
        else {
            for (unsigned int i = 0; i < Creeps.size(); i++) {
                float deltaX = (t->getBody().gGB().left + t->getBody().gGB().width / 2) - (Creeps[i].getBody().gGB().left + Creeps[i].getBody().gGB().width / 2);
                float deltaY = (t->getBody().gGB().top + t->getBody().gGB().height / 2) - (Creeps[i].getBody().gGB().top + Creeps[i].getBody().gGB().height / 2);
                if (sqrt(deltaX * deltaX + deltaY * deltaY) <= t->getArea().getRad()) {
                    t->Fire(Creeps[i]);
                    break;
                }
            }
        }
    }

    // Creep state update

    for (unsigned int i = 0; i < Creeps.size(); i++) {
        checkDir(Creeps[i], Map.Road);
    }

    // Ball flight proccesing

    for (unsigned int i = 0; i < Creeps.size(); ++i) {
        Creeps[i].Update(deltaTime);
        for (unsigned int j = 0; j < Creeps[i].ballsFollow.size(); ++j) {
            Creeps[i].ballsFollow[j].Update(Creeps[i].getBody().getPos().x + Creeps[i].getBody().gGB().width / 2, Creeps[i].getBody().getPos().y + Creeps[i].getBody().gGB().height / 2, deltaTime);
            Vector<float> ballPos = { Creeps[i].ballsFollow[j].getBody().getPos().x + Creeps[i].ballsFollow[j].getBody().gGB().width / 2, Creeps[i].ballsFollow[j].getBody().getPos().y + Creeps[i].ballsFollow[j].getBody().gGB().height / 2 };
            Vector<float> creepPos = { Creeps[i].getBody().getPos().x + Creeps[i].getBody().gGB().width / 2, Creeps[i].getBody().getPos().y + Creeps[i].getBody().gGB().height / 2 };
            if (epsCirclePos(ballPos, creepPos)) {
                Creeps[i].getDamage(Creeps[i].ballsFollow[j]); //Creeps[i].setHealth(-Creeps[i].ballsFollow[j].getDamage()); 
                Creeps[i].ballsFollow.erase(Creeps[i].ballsFollow.begin() + j);
                --j;
            }
        }
        Vector<float> creepPos = { Creeps[i].getBody().getPos().x + (Creeps[i].getBody().gGB().width / 2), Creeps[i].getBody().getPos().y + (Creeps[i].getBody().gGB().height / 2) };
        Vector<float> endPos = { Map.Road[Map.endNumb].first.getPos().x + blockSize.x, Map.Road[Map.endNumb].first.getPos().y + blockSize.y / 2 };
        if (epsCirclePos(creepPos, endPos)) {
            Creeps[i].Arrived();
            Creeps[i].setHealth(-Creeps[i].getHealth());
            currentGame->decr_playerHealth();
        }
    }

    // Getting damage

    for (unsigned int i = 0; i < Creeps.size(); ++i) {
        if (Creeps[i].getHealth() <= 0) {

            if (Creeps[i].isKilled()) { currentGame->set_playerGold(Creeps[i].getReward()); }

            Creeps[i].ballsFollow.clear();
            Creeps[i].killCreep(Creeps, Dead, i, deltaTime);
        }
    }

    // Preparing creep death animation

    for (unsigned int i = 0; i < Dead.size(); i++) {
        Dead[i].second -= deltaTime;
        Dead[i].first.Update(deltaTime);
        if (Dead[i].second <= 0) {
            auto it = Dead.begin();
            for (unsigned int j = 0; j < i; j++) {
                it++;
            }
            Dead.erase(it);
        }
    }

    // Tower animation proccesing

    for (unsigned int i = 0; i < Towers.size(); i++) {
        Towers[i]->Update(deltaTime);
    }
}


// Starting the gameplay and creating general objects

void Gameplay(unsigned int roundsToWin, userRenderWindow& Window, const GameSettings& gameSettings) {
    srand(static_cast <unsigned int> (time(0)));

    Game* currentGame = Game::get_instance();
    currentGame->startGame(gameSettings.Hard);
    std::vector <std::pair<Creep, float>> Dead;
    std::vector <Tower*> Towers;
    std::vector <Creep> Creeps;

    // Initialization of textures, music and font

    userImages tSameer, tBatyr, tSingle, tMulti, tFreezing, tOnePunch, tGameOver, tHGround, tGrass, tVGround, tURGround, tDRGround, tULGround, tDLGround;
    std::vector <userImages> Textures = { tSameer, tBatyr, tSingle, tMulti, tFreezing, tOnePunch, tGameOver, tHGround, tGrass, tVGround, tURGround, tDRGround, tULGround, tDLGround };

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
                                             "images/ULGround.png" };

    loadTexture(Textures, texturePath);
    userFont Font;
    Font.loadFromFile("images/Classic.ttf");
    int buttonCheck = -1;
    userMusic Music;
    Music.playMusic("images/music.ogg");
    userColor Blue = userColor(0, 0, 255, 25);

    MAP Map;
    std::vector <std::vector <int>> pseudoMap(mapSize.x, std::vector <int>(mapSize.y));
    fillMap1(pseudoMap);
    constructMap(Map, pseudoMap, Textures);

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
            Visualize(currentGame, Window, sGameOver, Creeps, Towers, Dead, Map, Blue, buttonCheck, Font);

            while (waitingTime > 0) {

                deltaTime = Clock.restart().asSeconds();
                waitingTime -= deltaTime;
                userEvent e;
                while (Window.pollEvent(e))
                    if (e.type == userEvent::Closed) {
                        Window.close();
                        towerClear(Towers);
                        exit(0);
                    }
                checkPress(currentGame, Window, Towers, Map.Grass, buttonCheck, Textures);

                for (unsigned int i = 0; i < Towers.size(); i++) {
                    Towers[i]->Update(deltaTime);
                }
                Visualize(currentGame, Window, sGameOver, Creeps, Towers, Dead, Map, Blue, buttonCheck, Font);

            }

            buttonCheck = -1;

            while (!Creeps.empty() || !Dead.empty() || cnt != 0) {
                userEvent e;

                while (Window.pollEvent(e))
                    if (e.type == userEvent::Closed) {
                        Window.close();
                        towerClear(Towers);
                        exit(0);
                    }
                deltaTime = Clock.restart().asSeconds();
                if (cnt != 0) fillCreep(currentGame, Creeps, Map, releaseTime, deltaTime, cnt, Textures[0], Textures[1]);
                Logic(currentGame, Towers, Creeps, Dead, deltaTime, Map);
                if (currentGame->get_playerHealth() <= 0) {
                    currentGame->switch_gameOver();
                    break;
                }
                Visualize(currentGame, Window, sGameOver, Creeps, Towers, Dead, Map, Blue, buttonCheck, Font);
            }
            if (currentGame->get_gameOver()) {
                Creeps.clear();
                Towers.clear();
                Dead.clear();
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
            userEvent e;
            while (Window.pollEvent(e))
                if (e.type == userEvent::Closed) {
                    Window.close();
                    towerClear(Towers);
                    exit(0);
                }
            Visualize(currentGame, Window, sGameOver, Creeps, Towers, Dead, Map, Blue, buttonCheck, Font);
        }
        break;
    }
}