#include "Additional.h"

class MediatorCreepBall;

class Unit {
public:
    Unit(userImages& Texture, Vector<int> imageCount, float sizeX, float sizeY);
    ~Unit() {}
    userRectangleShape getBody();
    Vector<float> getPosition();
    Animation getAnimation();

public:
    unsigned int Row;
    Animation animation;
    bool faceRight;
protected:
    userRectangleShape Body;
};