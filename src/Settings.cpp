#include "Settings.h"


void Settings(userRenderWindow& Window, GameSettings& gameSettings) {
    const std::vector <std::string> tButtonPath = {
            "images/Eazy.png",
            "images/Hard.png",
            "images/Back.png"};
    const std::string tBackgroundPath = "images/GrassGround.png";
    /*const std::vector <std::string> tButtonPath = {
            "images/Eazy.png",
            "images/Hard.png",
            "images/Back.png" };
    const std::string tBackgroundPath = "images/GrassGround.png";*/

    std::vector <userImages> ButtonTextures(tButtonPath.size());
    userImages tBackground;
    const std::vector <Vector<float>> ButtonPos = { { 234, 350 }, { 534, 350 }, { 48, 528} };

    std::vector <userSprite> Buttons;
    std::vector <userSprite> Background;
    bool goBack = false;
    Vector<int> Pos = { 0, 0 };

    loadAdditionalWindowTextures(Buttons, ButtonPos, tButtonPath, ButtonTextures, Background, tBackgroundPath, tBackground);
    srand(static_cast <unsigned int> (time(0)));

    while (Window.isOpen() && !goBack) {
        userEvent e;
        while (Window.pollEvent(e))
            if (e.type == userEvent::Closed) {
                Window.close();
                exit(0);
            }
        Vector<float> Pos = { 0.f, 0.f };
        userMouse mouse;
        if (mouse.buttonPressed('L')) {
            Pos = { mouse.getPos(Window).x, mouse.getPos(Window).y };
        }
        for (unsigned int i = 0; i < Buttons.size(); i++) {
            Vector<float> buttonCenter = { Buttons[i].gGB().left + Buttons[i].gGB().width / 2,
                                    Buttons[i].gGB().top + Buttons[i].gGB().height / 2 };
            if ((Pos.y > buttonCenter.y - Buttons[i].gGB().height / 2) &&
                (Pos.y < buttonCenter.y + Buttons[i].gGB().height / 2) &&
                (Pos.x > buttonCenter.x - Buttons[i].gGB().width / 2) &&
                (Pos.x < buttonCenter.x + Buttons[i].gGB().width / 2)) {
                if (i == 0) gameSettings.Hard = false; // Простой режим игры
                if (i == 1) gameSettings.Hard = true; // Сложный режим игры
                if (i == 2) goBack = true; // Возвращение в menu
            }
            AdditionalWindowDraw(Window, Buttons, Background);
        }
    }
}

// Additioanl windows rendering
 
void AdditionalWindowDraw(userRenderWindow& Window, std::vector<userSprite>& Buttons, std::vector<userSprite>& Background) {
    Window.userClear();
    for (auto& Tile : Background) {
        Window.userDraw(Tile);
    }
    for (auto& Button : Buttons) {
        Window.userDraw(Button);
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
