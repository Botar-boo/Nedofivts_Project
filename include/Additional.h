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
    Ball(Vector<float> towerPos, int n);
    ~Ball() {};
public:
    userCircleShape getBody();
    Vector<float> getPosition();

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
    FireBall(Vector<float> towerPos);
    ~FireBall() {}
};

class SnowBall : public Ball {
public:
    SnowBall(Vector<float> towerPos);
    ~SnowBall() {}

};

class DesolBall : public Ball {
public:
    DesolBall(Vector<float> TowerPos);
    ~DesolBall() {};
};