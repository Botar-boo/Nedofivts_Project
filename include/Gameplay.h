#pragma once
#include "Mediator.h"

void Logic(Game* currentGame, float deltaTime, MAP& Map);

void Gameplay(unsigned int roundsToWin, userRenderWindow& Window, const GameSettings& gameSettings);