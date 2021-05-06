#include "Unit.h"


Unit::Unit(userImages& Texture, Vector<int> imageCount, float sizeX, float sizeY) :
    Animation(&Texture, imageCount, animationTime) {
    this->Row = 0;
    Vector<float> size = { sizeX, sizeY };
    this->Body.setSize(sf::Vector2f(sizeX, sizeY)); 
    this->Body.setTexture(&Texture);
    this->faceRight = true;
}

userRectangleShape Unit::getBody() {
    return Body;
}
Animation Unit::getAnimation() {
    return Animation;
}
Vector<float> Unit::getPosition() {
    return this->Body.getPos();
}
