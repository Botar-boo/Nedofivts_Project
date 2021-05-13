#include "Gameplay.h"

void Settings(userRenderWindow& Window, GameSettings& gameSettings);
void fillAdditional(std::vector<userSprite>& Minimap, std::vector <userImages>& MinimapTextures, std::vector<std::string>& tMinimapPath, Vector <float> MinimapPos, std::vector<std::pair<userImages, userImages>>& AddTextures, GameSettings gameSettings);
void switchDifficulty(std::vector<userSprite>& Buttons, std::vector<std::pair<userImages, userImages>>& AddTextures, bool isPressed);