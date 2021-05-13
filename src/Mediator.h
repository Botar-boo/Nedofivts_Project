#pragma once
#include "AdditionalFunctions.h"


class MediatorCreepBall {
public:
    MediatorCreepBall() {};
    ~MediatorCreepBall() {};

    void processFlight(std::pair<Creep, std::vector<Ball>>& CreepBall, float deltaTime);
};