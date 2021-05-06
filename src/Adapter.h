#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>
#include <string>

typedef struct vectorF {
    float x;
    float y;
} vectorF;

typedef struct vectorU {
    int x;
    int y;
} vectorU;


typedef struct IntRect {
public:
    int left;
    int top;
    int width;
    int height;
} IntRect;



typedef struct FloatRect {
public:
    float left;
    float top;
    float width;
    float height;
} FloatRect;

class tImages : public sf::Texture {
public:
    tImages();
    ~tImages() {};
    void loadTexture(const std::string& file);
    vectorF getImageSize();
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
    vectorF getPos();

    void moveObj(float x, float y);

    FloatRect gGB() const;
};

class userRectangleShape : public sf::RectangleShape {
public:
    userRectangleShape();
    ~userRectangleShape() {};
    void setPos(float x, float y);
    vectorF getPos();
    void setTextureArea(IntRect uvRect);

    void moveObj(float x, float y);

    FloatRect gGB() const;
};

class userText : public sf::Text {
public:
    userText(const std::string& str, const userFont& font, unsigned int characterSize = 30);
    ~userText() {};

    void setPos(float x, float y);
    vectorF getPos();
};

class userSprite : public sf::Sprite {
public:
    userSprite(const tImages& texture);
    ~userSprite() {};
    FloatRect gGB() const;
    vectorF getPos();
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
    vectorF getPos(userRenderWindow& window);

};

class userKeyboard : public sf::Keyboard {
public:
    userKeyboard();
    ~userKeyboard() {};
    bool checkButtonPressed(char c);
};
