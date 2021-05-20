#include "../include/Facade.h"

void Facade::CreateMusic() {
    uMusic = std::make_unique<userMusic>();
}

void Facade::CreateFont() {
    uFont = std::make_unique<userFont>();
}

void Facade::CreateClock() {
    uClock = std::make_unique<userClock>();
}

void Facade::CreateColor(int red, int green, int blue, int alpha) {
    uColor = std::make_unique<userColor>(red, green, blue, alpha);
}

void Facade::CreateText(const std::string& str, const userFont& font, unsigned int characterSize) {
    uText = std::make_unique<userText>(str, font, characterSize);
}

void Facade::CreateRenderWindow(unsigned int modeWidth, unsigned int modeHeight, const std::string& title) {
    uRenderWindow = std::make_unique<userRenderWindow>(modeWidth, modeHeight, title);
}

void Facade::CreateEvent() {
    uEvent = std::make_unique<userEvent>();
}

void Facade::CreateMouse() {
    uMouse = std::make_unique<userMouse>();
}

void Facade::CreateKeyboard() {
    uKeyboard = std::make_unique<userKeyboard>();
}


userFont Facade::getFont() {
    return *(this->uFont);
}

userColor Facade::getColor() {
    return *(this->uColor);
}

float Facade::restartClock() {
    return uClock->restart().asSeconds();
}


void Facade::playMusic(const std::string filename) {
    uMusic->playMusic(filename);
}

void Facade::setTextPos(float x, float y) {
    uText->setPos(x, y);
}

Vector<float> Facade::getTextPos() {
    return uText->getPos();
}

void Facade::userDisplay() {
    uRenderWindow->userDisplay();
}

void Facade::userDraw(const sf::CircleShape obj) {
    uRenderWindow->userDraw(obj);
}
void Facade::userDraw(const sf::RectangleShape obj) {
    uRenderWindow->userDraw(obj);
}
void Facade::userDraw(const sf::Text obj) {
    uRenderWindow->userDraw(obj);
}
void Facade::userDraw(const sf::Sprite obj) {
    uRenderWindow->userDraw(obj);
}

void Facade::userClear() {
    uRenderWindow->userClear();
}

bool Facade::windowOpen() {
    uRenderWindow->windowOpen();
    return false;
}

void Facade::setFramerateLim(unsigned int fps) {
    uRenderWindow->setFramerateLimit(fps);
}

bool Facade::mousePressed(char c) {
    return uMouse->buttonPressed(c);
}
Vector<float> Facade::getMousePos(userRenderWindow& window) {
    return uMouse->getPos(window);
}
bool Facade::buttonPressed(char c) {
    return uKeyboard->checkButtonPressed(c);
}

void Facade::loadFont(const std::string filename) {
    uFont->loadFromFile(filename);
}
