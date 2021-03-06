#pragma once
#include "Game.h"


Vector <float> findCentre(Rect<float> rect);
bool epsSqPos(Vector<float> Pos1, Vector<float> Pos2);
bool epsCirclePos(Vector<float> Pos1, Vector<float> Pos2);

void checkDir(Creep& Creep, std::vector <std::pair<userSprite, int>>& mapConstruct);
void checkSpeed(int& gameSpeed, bool& gameStop, Game* game, float deltaTime);
void checkPress(Game* currentGame, userRenderWindow& Window, std::vector<std::pair<userSprite, bool>>& Grass, int& buttonCheck, std::vector <userImages>& Textures);
void towerClear(std::vector <Tower*>& Towers);
void loadTexture(std::vector <userImages>& Textures, const std::vector <std::string>& texturePath);
void addNewTower(Game* currentGame, Tower* newTower);

void Draw(Game* currentGame, userRenderWindow& App, userSprite sGameOver, MAP& Map, userFont Font);
void Visualize(Game* currentGame, userRenderWindow& App, userSprite sGameOver, MAP& Map, userFont Font, int& buttonCheck);
void fillCreep(Game* currentGame, MAP& Map, float& releaseTime, float deltaTime, int& Cnt, userImages& tSameer, userImages& tBatyr, userImages& tJegor);

void AdditionalWindowDraw(userRenderWindow& Window, std::vector<userSprite>& Buttons, std::vector<userSprite>& Background, std::vector<userSprite>& AddObjects);
void loadAdditionalWindowTextures(std::vector <userSprite>& Buttons, const std::vector <Vector<float>>& ButtonPosition, const std::vector <std::string>& tButtonPath, std::vector <userImages>& ButtonTextures, std::vector <userSprite>& Background, const std::string tBackgroundPath, userImages& tBackground);