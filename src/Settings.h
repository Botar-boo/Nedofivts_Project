 #include "Gameplay.h"

void Settings(userRenderWindow& Window, GameSettings& gameSettings);
void AdditionalWindowDraw(userRenderWindow& Window, std::vector<userSprite>& Buttons, std::vector<userSprite>& Background);
void loadAdditionalWindowTextures(std::vector <userSprite>& Buttons, const std::vector <Vector<float>>& ButtonPosition, const std::vector <std::string>& tButtonPath, std::vector <userImages>& ButtonTextures, std::vector <userSprite>& Background, const std::string tBackgroundPath, userImages& tBackground);
