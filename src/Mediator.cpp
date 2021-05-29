#include "../include/Mediator.h"

void MediatorCreepBall::processFlight(Creep* creep, float deltaTime) {
    Vector<float> creepPos = { findCentre(creep->getBody().gGB()).x, findCentre(creep->getBody().gGB()).y };
    
    for (unsigned int j = 0; j < creep->BallsFlow.size(); j++) {
        auto& ball = creep->BallsFlow[j];
        Vector<float> ballPos = { findCentre(ball.getBody().gGB()).x, findCentre(ball.getBody().gGB()).y };

        ball.Update(creepPos.x, creepPos.y, deltaTime);

        if (epsCirclePos(ballPos, creepPos)) {
            creep->getDamage(ball);
            creep->BallsFlow.erase(creep->BallsFlow.begin() + j);
            --j;
        }
    }
}

void MediatorCreepBall::clearBallsFlow(Creep* creep) {
    creep->BallsFlow.clear();
}
