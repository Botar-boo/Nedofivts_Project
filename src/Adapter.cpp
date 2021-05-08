#include "Adapter.h"

// Adapters to SFML objects
userImages::userImages() : sf::Texture() {} // calls sf::Texture constructor

void userImages::loadTexture(const std::string& file) {
    this->loadFromFile(file);
}

Vector<float> userImages::getImageSize() {
    Vector<float> size = { static_cast<float>(this->getSize().x), static_cast<float>(this->getSize().y) };
    // getSize() is inherited from Texture
    return size;
}


userFont::userFont() : sf::Font() {}

userMusic::userMusic() : sf::Music() {}

void userMusic::playMusic(const std::string filename) {
    this->openFromFile(filename);
    this->play();
    this->setLoop(true);
}

userClock::userClock() : sf::Clock() {}

userColor::userColor(int red, int green, int blue, int alpha) : sf::Color(red, green, blue, alpha) {}

userCircleShape::userCircleShape() : sf::CircleShape() {}

void userCircleShape::setRad(float radius) {
    this->setRadius(radius);
}

float userCircleShape::getRad() {
    return this->getRadius();
}

void userCircleShape::setPos(float x, float y) {
    this->setPosition(x, y);
}

Vector<float> userCircleShape::getPos() {
    Vector<float> pos = { this->getPosition().x, this->getPosition().y };
    return pos;
}

void userCircleShape::moveObj(float x, float y) {
    this->move(x, y);
}

Rect<float> userCircleShape::gGB() const {
    Rect<float> rect = { this->getGlobalBounds().left, this->getGlobalBounds().top, this->getGlobalBounds().width, this->getGlobalBounds().height };
    return rect;
}

userText::userText(const std::string& str, const userFont& font, unsigned int characterSize) : sf::Text(str, font, characterSize) {}

void userText::setPos(float x, float y) {
    this->setPosition(x, y);
}

Vector<float> userText::getPos() {
    Vector<float> pos = { this->getPosition().x, this->getPosition().y };
    return pos;
}

userSprite::userSprite(const userImages& texture) : sf::Sprite(texture) {}

Rect<float> userSprite::gGB() const {
    Rect<float> rect = { this->getGlobalBounds().left, this->getGlobalBounds().top, this->getGlobalBounds().width, this->getGlobalBounds().height };
    return rect;
}

void userSprite::setPos(float x, float y) {
    this->setPosition(x, y);
}

Vector<float> userSprite::getPos() {
    Vector<float> pos = { this->getPosition().x, this->getPosition().y };
    return pos;
}

userRenderWindow::userRenderWindow(unsigned int modeWidth, unsigned int modeHeight, const std::string& title) :
    sf::RenderWindow(
        sf::VideoMode(modeWidth, modeHeight),
        title,
        sf::Style::Close) {}
userRectangleShape::userRectangleShape() : sf::RectangleShape() {}

Vector<float> userRectangleShape::getPos() {
    Vector<float> pos = { this->getPosition().x, this->getPosition().y };
    return pos;
}

Rect<float> userRectangleShape::gGB() const {
    Rect<float> rect = { this->getGlobalBounds().left, this->getGlobalBounds().top, this->getGlobalBounds().width, this->getGlobalBounds().height };
    return rect;
}

void userRectangleShape::setTextureArea(Rect<int> uvRect) {
    sf::Rect<int> rect;
    rect.left = uvRect.left;
    rect.top = uvRect.top;
    rect.width = uvRect.width;
    rect.height = uvRect.height;
    this->setTextureRect(rect);
}

void userRectangleShape::moveObj(float x, float y) {
    this->move(x, y);
}

void userRectangleShape::setPos(float x, float y) {
    this->setPosition(x, y);
}

userEvent::userEvent() : sf::Event() {}
userMouse::userMouse() : sf::Mouse() {}
userKeyboard::userKeyboard() : sf::Keyboard() {}



bool userMouse::buttonPressed(char c) {
    if (c == 'L')
        return this->userMouse::isButtonPressed(userMouse::Left);
    if (c == 'R')
        return this->userMouse::isButtonPressed(userMouse::Right);
}


void userRenderWindow::userDisplay() {
    this->display();
}

void userRenderWindow::userDraw(const sf::CircleShape obj) {
    this->draw(obj);
}
void userRenderWindow::userDraw(const sf::RectangleShape obj) {
    this->draw(obj);
}
void userRenderWindow::userDraw(const sf::Text obj) {
    this->draw(obj);
}
void userRenderWindow::userDraw(const sf::Sprite obj) {
    this->draw(obj);
}

void userRenderWindow::userClear() {
    this->clear();
}

void userRenderWindow::setFramerateLim(unsigned int fps) {
    this->setFramerateLimit(fps);
}

bool userKeyboard::checkButtonPressed(char keyName) {
    bool res = false;
    if (keyName < 'A') {
        keyName += 'A' - 'a';
    }
    switch (keyName) {
    case 'A':
            res = userKeyboard::isKeyPressed(userKeyboard::Key::A);
            break;
    case 'B':
            res = userKeyboard::isKeyPressed(userKeyboard::Key::B);
            break;
    case 'C':
            res = userKeyboard::isKeyPressed(userKeyboard::Key::C);
            break;
    case 'D':
            res = userKeyboard::isKeyPressed(userKeyboard::Key::D);
            break;
    case 'Q':
            res = userKeyboard::isKeyPressed(userKeyboard::Key::Q);
            break;
    case 'W':
            res = userKeyboard::isKeyPressed(userKeyboard::Key::W);
            break;
    case 'E':
            res = userKeyboard::isKeyPressed(userKeyboard::Key::E);
            break;
    case 'R':
            res = userKeyboard::isKeyPressed(userKeyboard::Key::R);
            break;
    case 'X':
            res = userKeyboard::isKeyPressed(userKeyboard::Key::X);
            break;
    }
    return res;
}


Vector<float> userMouse::getPos(userRenderWindow& window) {
    Vector<float> pos = { static_cast<float>(userMouse::getPosition(window).x), static_cast<float>(userMouse::getPosition(window).y) };
    return pos;
}


bool userRenderWindow::windowOpen() {
    return this->isOpen();
}