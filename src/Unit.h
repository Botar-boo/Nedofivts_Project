#include "Additional.h"

class Unit {
public:
    Unit(tImages& Texture, vectorU imageCount, float sizeX, float sizeY);
    ~Unit() {}
    userRectangleShape getBody();
    vectorF getPosition();
    Animation getAnimation();

public:
    unsigned int Row;
    Animation Animation;
    bool faceRight;
protected:
    userRectangleShape Body;
};
