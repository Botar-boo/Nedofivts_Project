#include "Settings.h"


void Settings(userRenderWindow& Window, GameSettings& gameSettings) {
    const std::vector <std::string> tButtonPath = {
            "images/Eazy.png",
            "images/Hard.png",
            "images/Back.png" };
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
