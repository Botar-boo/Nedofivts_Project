#pragma once
#include "AdditionalFunctions.h"

void Logic(Game* currentGame, std::vector <Tower*>& Towers, std::vector <Creep>& Creeps, std::vector <std::pair<Creep, float>>& Dead, float deltaTime, MAP& Map);

void Gameplay(unsigned int roundsToWin, userRenderWindow& Window, const GameSettings& gameSettings);
