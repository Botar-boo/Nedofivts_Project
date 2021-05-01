#include "AdditionalFunctions.h"

const float Eps = 5;

bool epsSqPos(vectorF Pos1, vectorF Pos2) {
    return (fabs(Pos2.x - Pos1.x) <= Eps && fabs(Pos2.y - Pos1.y) <= Eps);
}
bool epsCirclePos(vectorF Pos1, vectorF Pos2) {
    return ((Pos2.x - Pos1.x) * (Pos2.x - Pos1.x) + (Pos2.y - Pos1.y) * (Pos2.y - Pos1.y) <= Eps * Eps);
}

// Creating creep wave at the begining of the round

void fillCreep(Game* currentGame, std::vector<Creep>& Creeps, MAP& Map, float& releaseTime, float deltaTime, int& cnt, tImages& tSameer, tImages& tBatyr) {
    releaseTime -= deltaTime;
    if (releaseTime <= 0 && cnt != 0) {
        releaseTime = deadTime;
        if (cnt % 2 == 1)
            Creeps.push_back(Batyr(tBatyr, currentGame->get_waveNumber(), Map.Road[Map.startNumb].first));
        else
            Creeps.push_back(Sameer(tSameer, currentGame->get_waveNumber(), Map.Road[Map.startNumb].first));
        cnt--;
    }
}

// Rendering map, units, additional objects
void Draw(Game* currentGame, userRenderWindow& App, userSprite sGameOver, std::vector <Creep>& Creeps, std::vector <Tower*>& Towers, std::vector <std::pair<Creep, float>>& Dead, MAP& Map, userFont& Font) {
    drawMap(App, Map);

    for (unsigned int i = 0; i < Creeps.size(); ++i) {
        App.userDraw(Creeps[i].getBody());
        for (unsigned int j = 0; j < Creeps[i].ballsFollow.size(); ++j) { App.userDraw(Creeps[i].ballsFollow[j].getBody()); }
    }


    for (unsigned int i = 0; i < Dead.size(); ++i) {
        App.userDraw(Dead[i].first.getBody());
    }

    for (unsigned int i = 0; i < Towers.size(); ++i) {
        App.userDraw(Towers[i]->getBody());
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
void Visualize(Game* currentGame, userRenderWindow& App, userSprite sGameOver, std::vector <Creep>& Creeps, std::vector <Tower*>& Towers, std::vector <std::pair<Creep, float>>& Dead, MAP& Map, userColor& Blue, int& buttonCheck, userFont& Font) {
    App.userClear();
    Draw(currentGame, App, sGameOver, Creeps, Towers, Dead, Map, Font);
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
void checkPress(Game* currentGame, userRenderWindow& Window, std::vector <Tower*>& Towers, std::vector<std::pair<userSprite, bool>>& Grass, int& buttonCheck, std::vector <tImages>& Textures) {
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
            vectorF Pos = { mouse.getPos(Window).x, mouse.getPos(Window).y };

            for (unsigned int i = 0; i < Grass.size(); ++i) {
                vectorF cellCenter = { Grass[i].first.gGB().left + Grass[i].first.gGB().width / 2, Grass[i].first.gGB().top + Grass[i].first.gGB().height / 2 };
                if ((Pos.y > cellCenter.y - Grass[i].first.gGB().height / 2) && (Pos.y < cellCenter.y + Grass[i].first.gGB().height / 2) && (Pos.x > cellCenter.x - Grass[i].first.gGB().width / 2) && (Pos.x < cellCenter.x + Grass[i].first.gGB().width / 2) && Grass[i].second == false) {
                    vectorF grassPos = { Grass[i].first.gGB().left + Grass[i].first.gGB().width / 2 - towerSize.x / 2, Grass[i].first.gGB().top + Grass[i].first.gGB().height / 2 - towerSize.y / 2 };
                    Tower* Tower = new SingleTower(Textures[2], grassPos);
                    if (Tower->getPrice() <= static_cast <int> (currentGame->get_playerGold())) {
                        addNewTower(currentGame, Towers, Tower);
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
            vectorF Pos = { mouse.getPos(Window).x, mouse.getPos(Window).y };

            for (unsigned int i = 0; i < Grass.size(); ++i) {
                vectorF cellCenter = { Grass[i].first.gGB().left + Grass[i].first.gGB().width / 2, Grass[i].first.gGB().top + Grass[i].first.gGB().height / 2 };
                if ((Pos.y > cellCenter.y - Grass[i].first.gGB().height / 2) && (Pos.y < cellCenter.y + Grass[i].first.gGB().height / 2) && (Pos.x > cellCenter.x - Grass[i].first.gGB().width / 2) && (Pos.x < cellCenter.x + Grass[i].first.gGB().width / 2) && Grass[i].second == false) {
                    vectorF grassPos = { Grass[i].first.gGB().left + Grass[i].first.gGB().width / 2 - towerSize.x / 2, Grass[i].first.gGB().top + Grass[i].first.gGB().height / 2 - towerSize.y / 2 };
                    Tower* Tower = new MultiTower(Textures[3], grassPos); //24 � 36 �������� ��������� �����
                    if (static_cast <int> (Tower->getPrice()) <= static_cast <int> (currentGame->get_playerGold())) {
                        addNewTower(currentGame, Towers, Tower);
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
            vectorF Pos = { mouse.getPos(Window).x, mouse.getPos(Window).y };

            for (unsigned int i = 0; i < Grass.size(); ++i) {
                vectorF cellCenter = { Grass[i].first.gGB().left + Grass[i].first.gGB().width / 2, Grass[i].first.gGB().top + Grass[i].first.gGB().height / 2 };
                if ((Pos.y > cellCenter.y - Grass[i].first.gGB().height / 2) && (Pos.y < cellCenter.y + Grass[i].first.gGB().height / 2) && (Pos.x > cellCenter.x - Grass[i].first.gGB().width / 2) && (Pos.x < cellCenter.x + Grass[i].first.gGB().width / 2) && Grass[i].second == false) {
                    vectorF grassPos = { Grass[i].first.gGB().left + Grass[i].first.gGB().width / 2 - towerSize.x / 2, Grass[i].first.gGB().top + Grass[i].first.gGB().height / 2 - towerSize.y / 2 };
                    Tower* Tower = new FreezingTower(Textures[4], grassPos); //24 � 36 �������� ��������� �����
                    if (static_cast <int> (Tower->getPrice()) <= static_cast <int> (currentGame->get_playerGold())) {
                        addNewTower(currentGame, Towers, Tower);
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
            vectorF Pos = { mouse.getPos(Window).x, mouse.getPos(Window).y };

            for (unsigned int i = 0; i < Grass.size(); ++i) {
                vectorF cellCenter = { Grass[i].first.gGB().left + Grass[i].first.gGB().width / 2, Grass[i].first.gGB().top + Grass[i].first.gGB().height / 2 };
                if ((Pos.y > cellCenter.y - Grass[i].first.gGB().height / 2) && (Pos.y < cellCenter.y + Grass[i].first.gGB().height / 2) && (Pos.x > cellCenter.x - Grass[i].first.gGB().width / 2) && (Pos.x < cellCenter.x + Grass[i].first.gGB().width / 2) && Grass[i].second == false) {
                    vectorF grassPos = { Grass[i].first.gGB().left + Grass[i].first.gGB().width / 2 - towerSize.x / 2, Grass[i].first.gGB().top + Grass[i].first.gGB().height / 2 - towerSize.y / 2 };
                    Tower* Tower = new OnePunchTower(Textures[5], grassPos); //24 � 36 �������� ��������� �����
                    if (static_cast <int> (Tower->getPrice()) <= static_cast <int> (currentGame->get_playerGold())) {
                        addNewTower(currentGame, Towers, Tower);
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

void addNewTower(Game* currentGame, std::vector <Tower*>& Towers, Tower* newTower) {
    Towers.push_back(newTower);
    std::sort(Towers.begin(), Towers.end(), [](Tower* Tower1, Tower* Tower2) { return Tower1->getBody().gGB().top < Tower2->getBody().gGB().top; });
    currentGame->set_playerGold(-newTower->getPrice());
}

// Switching creep directions

void checkDir(Creep& Creep, std::vector <std::pair<userSprite, int>>& Road) {
    int i = 0;
    for (unsigned int i = 0; i < Road.size(); i++) {
        vectorF creepPos = { Creep.getBody().gGB().left + Creep.getBody().gGB().width / 2, Creep.getBody().gGB().top + Creep.getBody().gGB().height / 2 };
        vectorF blockPos = { Road[i].first.gGB().left + Road[i].first.gGB().width / 2, Road[i].first.gGB().top + Road[i].first.gGB().height / 2 };
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

// Loading textures
// Commented piece of code is needed to load .jpg files

void loadTexture(std::vector <tImages>& Textures, const std::vector <std::string>& texturePath) {
    for (unsigned int i = 0; i < Textures.size(); ++i) {
        Textures[i].loadTexture(texturePath[i]);
    }
    /*
   tSameer.loadTexture("images/Sameer2.0.png");
   tBatyr.loadTexture("images/Batyr2.0.png");
   tSingle.loadTexture("images/SingleTower.png");
   tMulti.loadTexture("images/MultiTower.png");
   tFreezing.loadTexture("images/FreezingTower.png");
   tOnePunch.loadTexture("images/OnePunchMan.png");
   tGameOver.loadTexture("images/GameOver.png");
   tGrass.loadTexture("images/GrassGround.png");
   tHGround.loadTexture("images/HGround.png");
   tVGround.loadTexture("images/VGround.png");
   tURGround.loadTexture("images/URGround.png");
   tDRGround.loadTexture("images/DRGround.png");
   tDLGround.loadTexture("images/DLGround.png");
   tULGround.loadTexture("images/ULGround.png");*/

}
