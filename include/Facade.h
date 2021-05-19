#pragma once
#include "Adapter.h"

class Facade {
public:
    std::unique_ptr<userMusic> uMusic;
    std::unique_ptr<userFont> uFont;
    std::unique_ptr<userClock> uClock;
    std::unique_ptr<userColor> uColor;
    std::unique_ptr<userText> uText;
    std::unique_ptr<userRenderWindow> uRenderWindow;
    std::unique_ptr<userEvent> uEvent;
    std::unique_ptr<userMouse> uMouse;
    std::unique_ptr<userKeyboard> uKeyboard;


    void CreateMusic();
    void CreateFont();
    void CreateClock();
    void CreateColor(int red, int green, int blue, int alpha);
    void CreateText(const std::string& str, const userFont& font, unsigned int characterSize = 30);
    void CreateRenderWindow(unsigned int modeWidth, unsigned int modeHeight, const std::string& title);
    void CreateEvent();
    void CreateMouse();
    void CreateKeyboard();


    void playMusic(const std::string filename);
    void setTextPos(float x, float y);
    Vector<float> getTextPos();
    void userDisplay();
    void userDraw(const sf::CircleShape drawable);
    void userDraw(const sf::RectangleShape drawable);
    void userDraw(const sf::Sprite drawable);
    void userDraw(const sf::Text drawable);
    void userClear();
    bool windowOpen();
    void setFramerateLim(unsigned int fps);
    bool mousePressed(char c);
    Vector<float> getMousePos(userRenderWindow& window);
    bool buttonPressed(char c);
    void loadFont(const std::string filename);
    
};
