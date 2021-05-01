#pragma once
#include "AnimationGame.h"

// Additional objects 

// Map textures, info about start/end block
typedef struct MapStr {
    std::vector<std::pair<userSprite, bool>> Grass;
    std::vector<std::pair<userSprite, int>> Road;
    int startNumb;
    int endNumb;
} MAP;

typedef struct GameSettings {
    bool Hard;
    int MapNumber;
} GameSettings;


class Ball {
public:
    Ball(vectorF towerPos, int n);
    ~Ball() {};
public:
    userCircleShape getBody();
    vectorF getPosition();

    float getDamage();
    void setDamage(float Damage);

    userCircleShape Body;
    void Update(float x, float y, float deltaTime);

    void setDesolation(float Desolation);
    float getDesolation();

    void setSlow(float Slow);
    float getSlow();

private:
    float Speed;
    float Damage;

    float Desolation;
    float Slow;
};

class FireBall : public Ball {
public:
    FireBall(vectorF towerPos);
    ~FireBall() {}
};

class SnowBall : public Ball {
public:
    SnowBall(vectorF towerPos);
    ~SnowBall() {}

};

class DesolBall : public Ball {
public:
    DesolBall(vectorF TowerPos);
    ~DesolBall() {};
};
