#include "../include/AdditionalFunctions.h"

const float Eps = 5;

bool epsSqPos(Vector<float> Pos1, Vector<float> Pos2) {
    return (fabs(Pos2.x - Pos1.x) <= Eps && fabs(Pos2.y - Pos1.y) <= Eps);
}
bool epsCirclePos(Vector<float> Pos1, Vector<float> Pos2) {
    return ((Pos2.x - Pos1.x) * (Pos2.x - Pos1.x) + (Pos2.y - Pos1.y) * (Pos2.y - Pos1.y) <= Eps * Eps);
}

// Find centre of object

Vector <float> findCentre(Rect<float> rect) {
    Vector <float> posCentre = { rect.left +  rect.width / 2, rect.top + rect.height / 2 };
    return posCentre;
}

// Creating creep wave at the begining of the round

void fillCreep(Game* currentGame, MAP& Map, float& releaseTime, float deltaTime, int& cnt, userImages& tSameer, userImages& tBatyr, userImages& tJegor) {
    releaseTime -= deltaTime;
    if (releaseTime <= 0 && cnt != 0) {
        releaseTime = deadTime;
        if (cnt % 3 == 0) {
            Jegor Jegor(tJegor, currentGame->get_waveNumber(), Map.Road[Map.startNumb].first);
            MediatorCreepBall m;
            Jegor.setMediator(&m);
            currentGame->Creeps.push_back(Jegor);
        }
            
        else if (cnt % 3 == 1) {
            Batyr Batyr(tBatyr, currentGame->get_waveNumber(), Map.Road[Map.startNumb].first);
            MediatorCreepBall m;
            Batyr.setMediator(&m);
            currentGame->Creeps.push_back(Batyr);
        }
        else {
            Sameer Sameer(tSameer, currentGame->get_waveNumber(), Map.Road[Map.startNumb].first);
            MediatorCreepBall m;
            Sameer.setMediator(&m);
            currentGame->Creeps.push_back(Sameer);
        }
        cnt--;
    }
}

// Rendering map, units, additional objects
void Draw(Game* currentGame, userRenderWindow& App, userSprite sGameOver, MAP& Map, userFont& Font) {
    drawMap(App, Map);

    for (unsigned int i = 0; i < currentGame->Creeps.size(); ++i) {
        App.userDraw(currentGame->Creeps[i].getBody());
        for (unsigned int j = 0; j < currentGame->Creeps[i].getBalls().size(); ++j) { 
            App.userDraw(currentGame->Creeps[i].getBalls()[j].getBody()); 
        }
    }


    for (unsigned int i = 0; i < currentGame->Dead.size(); ++i) {
        App.userDraw(currentGame->Dead[i].first.getBody());
    }

    for (unsigned int i = 0; i < currentGame->Towers.size(); ++i) {
        App.userDraw(currentGame->Towers[i]->getBody());
    }
    userText Money("Gold: " + std::to_string(currentGame->get_playerGold()), Font, fontSize1);
    userText Lives("Health: " + std::to_string(currentGame->get_playerHealth()), Font, fontSize2);
    userText Wave("Wave: " + std::to_string(currentGame->get_waveNumber()), Font, fontSize1);
    Money.setPos(moneyPosition.x, moneyPosition.y);
    Lives.setPos(healthPosition.x, healthPosition.y);
    Wave.setPos(wavePosition.x, wavePosition.y);
    if (!currentGame->get_gameOver()) {
        App.userDraw(Money);
        App.userDraw(Lives);
        App.userDraw(Wave);
    }
    if (currentGame->get_gameOver()) App.draw(sGameOver);
}

// Visualization of objects
void Visualize(Game* currentGame, userRenderWindow& App, userSprite sGameOver, MAP& Map, userColor& Blue, int& buttonCheck, userFont& Font) {
    App.userClear();
    Draw(currentGame, App, sGameOver, Map, Font);
    if (buttonCheck != -1) {
        userCircleShape Area;
        Area.setOrigin(originPosition.x, originPosition.y);
        Area.setRadius(towerRadius);
        Area.setPos(static_cast<float>(userMouse::getPosition(App).x), static_cast<float>(userMouse::getPosition(App).y));
        Area.setFillColor(Blue);
        App.userDraw(Area);
    }
    App.userDisplay();
}


// Check keypress
void checkSpeed(int& gameSpeed, bool& gameStop, Game* game, float deltaTime) {
    userKeyboard kBoard;
    static float speedTime = 0, stopTime = 0;
    speedTime += deltaTime;
    stopTime += deltaTime;
    if (kBoard.checkButtonPressed('A') && speedTime >= 0.2) {
        gameSpeed = 3 - gameSpeed;
        speedTime = 0;
    }
    if (kBoard.checkButtonPressed('B') && stopTime >= 0.2) {
        gameStop = !gameStop;
        stopTime = 0;
    }
    if (kBoard.checkButtonPressed('D')) {
        game->set_gameOver();
    }
}

void checkPress(Game* currentGame, userRenderWindow& Window, std::vector<std::pair<userSprite, bool>>& Grass, int& buttonCheck, std::vector <userImages>& Textures) {
    userKeyboard kBoard;
    if (kBoard.checkButtonPressed('Q')) {
        buttonCheck = 0;
    }
    if (kBoard.checkButtonPressed('W')) {
        buttonCheck = 1;
    }
    if (kBoard.checkButtonPressed('E')) {
        buttonCheck = 2;
    }
    if (kBoard.checkButtonPressed('R')) {
        buttonCheck = 3;
    }
    if (kBoard.checkButtonPressed('X')) {
        buttonCheck = -1;
    }
    userMouse mouse;
    switch (buttonCheck) {
    case 0: {
        if (mouse.buttonPressed('L')) {
            Vector<float> Pos = { mouse.getPos(Window).x, mouse.getPos(Window).y };

            for (unsigned int i = 0; i < Grass.size(); ++i) {
                Vector<float> cellCenter = { findCentre(Grass[i].first.gGB()).x , findCentre(Grass[i].first.gGB()).y };
                if ((Pos.y > cellCenter.y - Grass[i].first.gGB().height / 2)
                    && (Pos.y < cellCenter.y + Grass[i].first.gGB().height / 2)
                    && (Pos.x > cellCenter.x - Grass[i].first.gGB().width / 2)
                    && (Pos.x < cellCenter.x + Grass[i].first.gGB().width / 2)
                    && Grass[i].second == false) {
                    Vector<float> grassPos = { findCentre(Grass[i].first.gGB()).x - towerSize.x / 2, findCentre(Grass[i].first.gGB()).y - towerSize.y / 2 };
                    Tower* Tower = new SingleTower(Textures[2], grassPos);
                    if (Tower->getPrice() <= static_cast <int> (currentGame->get_playerGold())) {
                        addNewTower(currentGame, Tower);
                        Grass[i].second = true;
                    }
                    else {
                        delete Tower;
                    }

                }
            }

            buttonCheck = -1;
        }
        break;
    }
    case 1: {
        if (mouse.buttonPressed('L')) {
            Vector<float> Pos = { mouse.getPos(Window).x, mouse.getPos(Window).y };

            for (unsigned int i = 0; i < Grass.size(); ++i) {
                Vector<float> cellCenter = { findCentre(Grass[i].first.gGB()).x , findCentre(Grass[i].first.gGB()).y };
                if ((Pos.y > cellCenter.y - Grass[i].first.gGB().height / 2)
                    && (Pos.y < cellCenter.y + Grass[i].first.gGB().height / 2)
                    && (Pos.x > cellCenter.x - Grass[i].first.gGB().width / 2)
                    && (Pos.x < cellCenter.x + Grass[i].first.gGB().width / 2)
                    && Grass[i].second == false) {
                    Vector<float> grassPos = { findCentre(Grass[i].first.gGB()).x - towerSize.x / 2, findCentre(Grass[i].first.gGB()).y - towerSize.y / 2 };
                    Tower* Tower = new MultiTower(Textures[3], grassPos);
                    if (static_cast <int> (Tower->getPrice()) <= static_cast <int> (currentGame->get_playerGold())) {
                        addNewTower(currentGame, Tower);
                        Grass[i].second = true;
                    }
                    else {
                        delete Tower;
                    }

                }
            }

            buttonCheck = -1;
        }
        break;
    }
    case 2: {
        if (mouse.buttonPressed('L')) {
            Vector<float> Pos = { mouse.getPos(Window).x, mouse.getPos(Window).y };

            for (unsigned int i = 0; i < Grass.size(); ++i) {
                Vector<float> cellCenter = { findCentre(Grass[i].first.gGB()).x , findCentre(Grass[i].first.gGB()).y };
                if ((Pos.y > cellCenter.y - Grass[i].first.gGB().height / 2)
                    && (Pos.y < cellCenter.y + Grass[i].first.gGB().height / 2)
                    && (Pos.x > cellCenter.x - Grass[i].first.gGB().width / 2)
                    && (Pos.x < cellCenter.x + Grass[i].first.gGB().width / 2)
                    && Grass[i].second == false) {
                    Vector<float> grassPos = { findCentre(Grass[i].first.gGB()).x - towerSize.x / 2, findCentre(Grass[i].first.gGB()).y - towerSize.y / 2 };
                    Tower* Tower = new FreezingTower(Textures[4], grassPos);
                    if (static_cast <int> (Tower->getPrice()) <= static_cast <int> (currentGame->get_playerGold())) {
                        addNewTower(currentGame, Tower);
                        Grass[i].second = true;
                    }
                    else {
                        delete Tower;
                    }

                }
            }

            buttonCheck = -1;
        }
        break;
    }
    case 3: {
        if (mouse.buttonPressed('L')) {
            Vector<float> Pos = { mouse.getPos(Window).x, mouse.getPos(Window).y };

            for (unsigned int i = 0; i < Grass.size(); ++i) {
                Vector<float> cellCenter = { findCentre(Grass[i].first.gGB()).x , findCentre(Grass[i].first.gGB()).y };
                if ((Pos.y > cellCenter.y - Grass[i].first.gGB().height / 2)
                    && (Pos.y < cellCenter.y + Grass[i].first.gGB().height / 2)
                    && (Pos.x > cellCenter.x - Grass[i].first.gGB().width / 2)
                    && (Pos.x < cellCenter.x + Grass[i].first.gGB().width / 2)
                    && Grass[i].second == false) {
                    Vector<float> grassPos = { findCentre(Grass[i].first.gGB()).x - towerSize.x / 2, findCentre(Grass[i].first.gGB()).y - towerSize.y / 2 };
                    Tower* Tower = new OnePunchTower(Textures[5], grassPos);
                    if (static_cast <int> (Tower->getPrice()) <= static_cast <int> (currentGame->get_playerGold())) {
                        addNewTower(currentGame, Tower);
                        Grass[i].second = true;
                    }
                    else {
                        delete Tower;
                    }

                }
            }

            buttonCheck = -1;
        }
        break;
    }
    }
}

// Add new tower to vector

void addNewTower(Game* currentGame, Tower* newTower) {
    currentGame->Towers.push_back(newTower);
    std::sort(currentGame->Towers.begin(), currentGame->Towers.end(), [](Tower* Tower1, Tower* Tower2) { return Tower1->getBody().gGB().top < Tower2->getBody().gGB().top; });
    currentGame->set_playerGold(-newTower->getPrice());
}

// Switching creep directions

void checkDir(Creep& Creep, std::vector <std::pair<userSprite, int>>& Road) {
    int i = 0;
    for (unsigned int i = 0; i < Road.size(); i++) {
        Vector<float> creepPos = findCentre(Creep.getBody().gGB());
        Vector<float> blockPos = findCentre(Road[i].first.gGB());
        if (epsSqPos(creepPos, blockPos)) {
            if (Road[i].second == 6) {
                if (Creep.getDirection() == 0) {
                    Creep.setDirection(1);
                }
                if (Creep.getDirection() == 3) {
                    Creep.setDirection(2);
                }
            }
            if (Road[i].second == 4) {
                if (Creep.getDirection() == 3) {
                    Creep.setDirection(0);
                }
                if (Creep.getDirection() == 2) {
                    Creep.setDirection(1);
                }
            }
            if (Road[i].second == 5) {
                if (Creep.getDirection() == 1) {
                    Creep.setDirection(2);
                }
                if (Creep.getDirection() == 0) {
                    Creep.setDirection(3);
                }
            }
            if (Road[i].second == 3) {
                if (Creep.getDirection() == 1) {
                    Creep.setDirection(0);
                }
                if (Creep.getDirection() == 2) {
                    Creep.setDirection(3);
                }
            }
        }
    }
}

// Clearing memory

void towerClear(std::vector <Tower*>& Towers) {
    for (auto t : Towers) {
        delete t;
    }
}

// Additioanl windows rendering

void AdditionalWindowDraw(userRenderWindow& Window, std::vector<userSprite>& Buttons, std::vector<userSprite>& Background, std::vector<userSprite>& AddObjects) {
    Window.userClear();
    for (auto& Tile : Background) {
        Window.userDraw(Tile);
    }
    for (auto& Button : Buttons) {
        Window.userDraw(Button);
    }
    for (auto& Obj : AddObjects) {
        Window.userDraw(Obj);
    }
    Window.userDisplay();
}

// Loading textures

void loadAdditionalWindowTextures(std::vector <userSprite>& Buttons, const std::vector <Vector<float>>& ButtonPosition, const std::vector <std::string>& tButtonPath, std::vector <userImages>& ButtonTextures, std::vector <userSprite>& Background, const std::string tBackgroundPath, userImages& tBackground) {

    tBackground.loadTexture(tBackgroundPath);

    for (unsigned int i = 0; i < ButtonTextures.size(); ++i) {
        ButtonTextures[i].loadTexture(tButtonPath[i]);
        userSprite Button(ButtonTextures[i]);
        Button.setPos(ButtonPosition[i].x, ButtonPosition[i].y);
        Buttons.push_back(Button);
    }

    for (unsigned int i = 0; i < static_cast<unsigned int>(windowWidth / blockSizeX); ++i) {
        for (unsigned int j = 0; j < static_cast<unsigned int>(windowHeight / blockSizeY); ++j) {
            userSprite Ground(tBackground);
            Ground.setPosition(blockSizeX * i, blockSizeY * j);
            Background.push_back(Ground);
        }
    }
}

// Loading textures

void loadTexture(std::vector <userImages>& Textures, const std::vector <std::string>& texturePath) {
    for (unsigned int i = 0; i < Textures.size(); ++i) {
        Textures[i].loadTexture(texturePath[i]);
    }
}
