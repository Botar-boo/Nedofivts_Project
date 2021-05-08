#include "Additional.h"

class Unit {
public:
    Unit(userImages& Texture, Vector<int> imageCount, float sizeX, float sizeY);
    ~Unit() {}
    userRectangleShape getBody();
    Vector<float> getPosition();
    Animation getAnimation();

public:
    unsigned int Row;
    Animation Animation;
    bool faceRight;
protected:
    userRectangleShape Body;
};