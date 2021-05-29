#include "../include/Menu.h"


const unsigned int menuButtons = 2;

// Menu logic

void Menu(userRenderWindow& Window, GameSettings& gameSettings) {
    // Commented out piece of code is needed to switch to jpg files
    const std::vector <std::string> tButtonPath = {
            "images/Play.png",
            "images/Settings.png" };
    const std::string tBackgroundPath = "images/GrassGround.png";

    std::vector <userImages> ButtonTextures(menuButtons);
    userImages tBackground;

    const std::vector <Vector<float>> ButtonPos = { { 384, 200 }, { 816, 528} };

    std::vector <userSprite> AddObjects;
    std::vector <userSprite> Buttons;
    std::vector <userSprite> Background;
    bool openSettings = false;
    bool gameStart = false;
    Vector<int> Pos = { 0, 0 };

    loadAdditionalWindowTextures(Buttons, ButtonPos, tButtonPath, ButtonTextures, Background, tBackgroundPath, tBackground);
    srand(static_cast <unsigned int> (time(0)));

    while (Window.isOpen() && !gameStart) {
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
                if (i == 0) gameStart = true;  // В игру
                if (i == 1) openSettings = true; // Вернуться в Settings
            }
        }
        if (openSettings) {
            Settings(Window, gameSettings);
            openSettings = false;
        }
        AdditionalWindowDraw(Window, Buttons, Background, AddObjects);
    }
}