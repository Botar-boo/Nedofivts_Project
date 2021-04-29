#pragma once
#include "Maps.h"
#include "Game.h"


bool epsSqPos(vectorF Pos1, vectorF Pos2);
bool epsCirclePos(vectorF Pos1, vectorF Pos2);

void checkDir(Creep& Creep, std::vector <std::pair<userSprite, int>>& mapConstruct);
void checkPress(Game* currentGame, userRenderWindow& Window, std::vector <Tower*>& Towers, std::vector<std::pair<userSprite, bool>>& Grass, int& buttonCheck, std::vector <tImages>& Textures);
void towerClear(std::vector <Tower*>& Towers);
void loadTexture(std::vector <tImages>& Textures, const std::vector <std::string>& texturePath);
void addNewTower(Game* currentGame, std::vector <Tower*>& Towers, Tower* newTower);

void Draw(Game* currentGame, userRenderWindow& App, userSprite sGameOver, std::vector <Creep>& Creeps, std::vector <Tower*>& Towers, std::vector <std::pair<Creep, float>>& Dead, MAP& Map, userFont& Font);
void Visualize(Game* currentGame, userRenderWindow& App, userSprite sGameOver, std::vector <Creep>& Creeps, std::vector <Tower*>& Towers, std::vector <std::pair<Creep, float>>& Dead, MAP& Map, userColor& Blue, int& buttonCheck, userFont& Font);
void fillCreep(Game* currentGame, std::vector<Creep>& Creeps, MAP& Map, float& releaseTime, float deltaTime, int& Cnt, tImages& tSameer, tImages& tBatyr);
