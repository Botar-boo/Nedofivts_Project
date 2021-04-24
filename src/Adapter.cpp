#include "Adapter.h"

// Обертки для объектов и методов SFML

tImages::tImages() : sf::Texture() {}

void tImages::loadTexture(const std::string& file) {
    this->loadFromFile(file);
}

vectorF tImages::getImageSize() {
    vectorF size = { static_cast<float>(this->getSize().x), static_cast<float>(this->getSize().y) };
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

vectorF userCircleShape::getPos() {
    vectorF pos = { this->getPosition().x, this->getPosition().y };
    return pos;
}

void userCircleShape::moveObj(float x, float y) {
    this->move(x, y);
}

FloatRect userCircleShape::gGB() const {
    FloatRect rect = { this->getGlobalBounds().left, this->getGlobalBounds().top, this->getGlobalBounds().width, this->getGlobalBounds().height };
    return rect;
}

userText::userText(const std::string& str, const userFont& font, unsigned int characterSize) : sf::Text(str, font, characterSize) {}

void userText::setPos(float x, float y) {
    this->setPosition(x, y);
}

vectorF userText::getPos() {
    vectorF pos = { this->getPosition().x, this->getPosition().y };
    return pos;
}

userSprite::userSprite(const tImages& texture) : sf::Sprite(texture) {}

FloatRect userSprite::gGB() const {
    FloatRect rect = { this->getGlobalBounds().left, this->getGlobalBounds().top, this->getGlobalBounds().width, this->getGlobalBounds().height };
    return rect;
}

void userSprite::setPos(float x, float y) {
    this->setPosition(x, y);
}

vectorF userSprite::getPos() {
    vectorF pos = { this->getPosition().x, this->getPosition().y };
    return pos;
}

userRenderWindow::userRenderWindow(unsigned int modeWidth, unsigned int modeHeight, const std::string& title) :
    sf::RenderWindow(
        sf::VideoMode(modeWidth, modeHeight),
        title,
        sf::Style::Close | sf::Style::Resize) {}
userRectangleShape::userRectangleShape() : sf::RectangleShape() {}

vectorF userRectangleShape::getPos() {
    vectorF pos = { this->getPosition().x, this->getPosition().y };
    return pos;
}

FloatRect userRectangleShape::gGB() const {
    FloatRect rect = { this->getGlobalBounds().left, this->getGlobalBounds().top, this->getGlobalBounds().width, this->getGlobalBounds().height };
    return rect;
}

void userRectangleShape::setTextureArea(IntRect uvRect) {
    sf::IntRect rect;
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

bool userKeyboard::checkButtonPressed(char c) {
    bool res = false;
    if (c == 'A' || c == 'a') {
        res = userKeyboard::isKeyPressed(userKeyboard::Key::A);
    }
    if (c == 'B' || c == 'b') {
        res = userKeyboard::isKeyPressed(userKeyboard::Key::B);
    }
    if (c == 'C' || c == 'c') {
        res = userKeyboard::isKeyPressed(userKeyboard::Key::C);
    }
    if (c == 'D' || c == 'd') {
        res = userKeyboard::isKeyPressed(userKeyboard::Key::D);
    }
    if (c == 'Q' || c == 'q') {
        res = userKeyboard::isKeyPressed(userKeyboard::Key::Q);
    }
    if (c == 'W' || c == 'w') {
        res = userKeyboard::isKeyPressed(userKeyboard::Key::W);
    }
    if (c == 'E' || c == 'e') {
        res = userKeyboard::isKeyPressed(userKeyboard::Key::E);
    }
    if (c == 'R' || c == 'r') {
        res = userKeyboard::isKeyPressed(userKeyboard::Key::R);
    }
    if (c == 'X' || c == 'x') {
        res = userKeyboard::isKeyPressed(userKeyboard::Key::X);
    }
    return res;
}


vectorF userMouse::getPos(userRenderWindow& window) {
    vectorF pos = { static_cast<float>(userMouse::getPosition(window).x), static_cast<float>(userMouse::getPosition(window).y) };
    return pos;
}


bool userRenderWindow::windowOpen() {
    return this->isOpen();
}