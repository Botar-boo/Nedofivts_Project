#include "Mediator.h"

void MediatorCreepBall::processFlight(std::pair<Creep, std::vector<Ball>>& CreepBall, float deltaTime) {
    auto& creep = CreepBall.first;
    Vector<float> creepPos = { findCentre(creep.getBody().gGB()).x, findCentre(creep.getBody().gGB()).y };
    
    for (int j = 0; j < CreepBall.second.size(); j++) {
        auto& ball = CreepBall.second[j];
        Vector<float> ballPos = { findCentre(ball.getBody().gGB()).x, findCentre(ball.getBody().gGB()).y };

        ball.Update(creepPos.x, creepPos.y, deltaTime);

        if (epsCirclePos(ballPos, creepPos)) {
            creep.getDamage(ball);
            CreepBall.second.erase(CreepBall.second.begin() + j);
            --j;
        }
    }
}