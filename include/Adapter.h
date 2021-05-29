#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>


template<typename T>
struct Vector {
public:
    T x;
    T y;
};


template<typename T>
struct Rect { // Rect is used for rectangle objects. Don't confuse with user userRectangleShape
public:
    T left;
    T top;
    T width;
    T height;
};

// these classes are used for cover over SFML
class userImages : public sf::Texture {
public:
    userImages();
    ~userImages() {};
    void loadTexture(const std::string& file);
    Vector<float>  getImageSize();
};

class userFont : public sf::Font {
public:
    userFont();
    ~userFont() {};
};

class userMusic : public sf::Music {
public:
    userMusic();
    ~userMusic() {};

    void playMusic(const std::string filename);
};

class userClock : public sf::Clock {
public:
    userClock();
    ~userClock() {};	
};

class userColor : public sf::Color {
public:
    userColor(int red, int green, int blue, int alpha);
    ~userColor() {};
};

class userCircleShape : public sf::CircleShape {
public:
    userCircleShape();
    ~userCircleShape() {};

    void setRad(float radius);
    float getRad();

    void setPos(float x, float y);
    Vector<float> getPos();

    void moveObj(float x, float y);

    Rect<float> gGB() const;
};

class userRectangleShape : public sf::RectangleShape { // is used for controlling SFML rectangle shapes
public:
    userRectangleShape();
    ~userRectangleShape() {};
    void setPos(float x, float y);
    Vector<float> getPos();
    void setTextureArea(Rect<int> uvRect);

    void moveObj(float x, float y);

    Rect<float> gGB() const;
};

class userText : public sf::Text {
public:
    userText(const std::string& str, const userFont& font, unsigned int characterSize = 30);
    ~userText() {};

    void setPos(float x, float y);
    Vector<float> getPos();
};

class userSprite : public sf::Sprite {
public:
    userSprite(const userImages& texture);
    ~userSprite() {};
    Rect<float> gGB() const;
    Vector<float> getPos();
    void setPos(float x, float y);
};

class userRenderWindow : public sf::RenderWindow {
public:
    userRenderWindow(unsigned int modeWidth, unsigned int modeHeight, const std::string& title);
    ~userRenderWindow() {};
    void userDisplay();
    void userDraw(const sf::CircleShape drawable);
    void userDraw(const sf::RectangleShape drawable);
    void userDraw(const sf::Sprite drawable);
    void userDraw(const sf::Text drawable);

    void userClear();

    bool windowOpen();

    void setFramerateLim(unsigned int fps);
};

class userEvent : public sf::Event {
public:
    userEvent();
    ~userEvent() {};
};

class userMouse : public sf::Mouse {
public:
    userMouse();
    ~userMouse() {};
    bool buttonPressed(char c);
    Vector<float> getPos(userRenderWindow& window);

};

class userKeyboard : public sf::Keyboard {
public:
    userKeyboard();
    ~userKeyboard() {};
    bool checkButtonPressed(char c);
};
