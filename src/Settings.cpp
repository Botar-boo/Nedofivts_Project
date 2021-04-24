#include "Settings.h"


void Settings(userRenderWindow& Window, GameSettings& gameSettings) {
    // ���� � ���������
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

    //�������� �������
    std::vector <tImages> ButtonTextures(tButtonPath.size());
    tImages tBackground;
    //������ ��������� ������ ����
    const std::vector <vectorF> ButtonPos = { { 234, 350 }, { 534, 350 }, { 48, 528} };

    std::vector <userSprite> Buttons;
    std::vector <userSprite> Background;
    bool goBack = false;
    vectorU Pos = { 0, 0 };

    loadAdditionalWindowTextures(Buttons, ButtonPos, tButtonPath, ButtonTextures, Background, tBackgroundPath, tBackground);
    srand(static_cast <unsigned int> (time(0)));

    while (Window.isOpen() && !goBack) {
        userEvent e;
        while (Window.pollEvent(e))
            if (e.type == userEvent::Closed) {
                Window.close();
                exit(0);
            }
        vectorF Pos = { 0.f, 0.f };
        userMouse mouse;
        if (mouse.buttonPressed('L')) {
            Pos = { mouse.getPos(Window).x, mouse.getPos(Window).y };
        }
        for (unsigned int i = 0; i < Buttons.size(); i++) {
            vectorF buttonCenter = { Buttons[i].gGB().left + Buttons[i].gGB().width / 2,
                                    Buttons[i].gGB().top + Buttons[i].gGB().height / 2 };
            if ((Pos.y > buttonCenter.y - Buttons[i].gGB().height / 2) &&
                (Pos.y < buttonCenter.y + Buttons[i].gGB().height / 2) &&
                (Pos.x > buttonCenter.x - Buttons[i].gGB().width / 2) &&
                (Pos.x < buttonCenter.x + Buttons[i].gGB().width / 2)) {
                if (i == 0) gameSettings.Hard = false; // ��������� ����������
                if (i == 1) gameSettings.Hard = true; // ��������� �������
                if (i == 2) goBack = true; // ��������� � ����
            }
            AdditionalWindowDraw(Window, Buttons, Background);
        }
    }
}

//������� ������������ � ������������� �������
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

//�������� �������
void loadAdditionalWindowTextures(std::vector <userSprite>& Buttons, const std::vector <vectorF>& ButtonPosition, const std::vector <std::string>& tButtonPath, std::vector <tImages>& ButtonTextures, std::vector <userSprite>& Background, const std::string tBackgroundPath, tImages& tBackground) {

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