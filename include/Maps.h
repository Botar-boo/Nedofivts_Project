#pragma once
#include "Tower.h"

void drawMap(userRenderWindow& Window, MAP& Map);

void createMap(MAP& map, const GameSettings& gameSettings, std::vector <userImages>& Textures);

void constructMap(MAP& Map, std::vector <std::vector<int>>& pseudoMap, std::vector <userImages>& Textures);

void fillMap0(std::vector <std::vector <int>>& Map);

void fillMap1(std::vector <std::vector <int>>& Map);

void fillMap2(std::vector <std::vector <int>>& Map);
