#include "../include/Creep.h"

Creep::Creep(userImages& Texture, userSprite& startBlock, Vector<int> imageCount, float sizeX, float sizeY, float Health, float Speed) :
    Unit(
        Texture,
        imageCount,
        sizeX,
        sizeY)
{
    this->Killed = true;
    this->Health = Health;
    this->Speed = Speed;
    this->Body.setPos(startBlock.gGB().left + (startBlock.gGB().width - sizeX) / 2, startBlock.gGB().top + (startBlock.gGB().height - sizeY) / 2);
    this->Dir = 0;
}



Batyr::Batyr(userImages& Texture, unsigned int waveNumber, userSprite& startBlock) :
    Creep(
        Texture,
        startBlock,
        creepImageCount,
        batSizeX,
        batSizeY,
        batHealth,
        batSpeed) {
    this->setReward(batReward);
    this->Evasion = batEvasion;
    this->Armor = batArmor;
    this->Evasion *= (float)pow(evasionMul, waveNumber);
}

Sameer::Sameer(userImages& Texture, unsigned int waveNumber, userSprite& startBlock) :
    Creep(
        Texture,
        startBlock,
        creepImageCount,
        samSizeX,
        samSizeY,
        samHealth,
        samSpeed) {
    this->setReward(samReward);
    this->Armor = samArmor;
    this->Evasion = samEvasion;
    this->Armor *= (float)pow(armorMul, waveNumber);
}

Jegor::Jegor(userImages& Texture, unsigned int waveNumber, userSprite& startBlock) :
    Creep(
        Texture,
        startBlock,
        creepImageCount,
        jgrSizeX,
        jgrSizeY,
        jgrHealth,
        jgrSpeed) {
    this->setReward(jgrReward);
    this->Armor = jgrArmor;
    this->Evasion = jgrEvasion;
    this->Armor *= (float)pow(armorMul, waveNumber);
}

// Preparing creep animation for update
void Creep::Update(float deltaTime) {
    Vector<float> movement = { 0.0f, 0.0f };
    startProcessing(deltaTime, "flight");
    if (Row == 0) {
        if (this->Dir == 0) {
            movement.x += Speed * deltaTime;
            faceRight = true;
        }
        if (this->Dir == 1) {
            movement.y += Speed * deltaTime;
        }
        if (this->Dir == 2) {
            movement.x -= Speed * deltaTime;
            faceRight = false;
        }
        if (this->Dir == 3) {
            movement.y -= Speed * deltaTime;
        }
    }

    animation.Update(Row, deltaTime, faceRight);
    Body.setTextureArea(animation.uvRect);
    Body.moveObj(movement.x, movement.y);
}

void Creep::setSpeed(float Speed)
{
    this->Speed = Speed;
}
float Creep::getSpeed() {
    return this->Speed;
}

void Creep::getDamage(Ball ball) {
    this->Armor *= (1 - ball.getDesolation());
    this->Speed = ((1 - ball.getSlow()) * this->Speed >= minSpeed ? (1 - ball.getSlow()) * this->Speed : minSpeed);
    float deltaHP = ball.getDamage() * (1 - this->Armor);
    int a = rand() % 101;
    if (a * 0.01 >= this->Evasion) {
        this->setHealth(-deltaHP);
    }
}

void Creep::setDirection(int Dir) {
    this->Dir = Dir;
}

int Creep::getDirection() {
    return this->Dir;
}

bool Creep::isKilled() {
    return this->Killed;
}

void Creep::Arrived() {
    this->Killed = false;
}

float Creep::getHealth() {
    return Health;
}

void Creep::setHealth(float deltaHealth) {
    Health += deltaHealth;
}

unsigned int Creep::getReward() {
    return Reward;
}

void Creep::setReward(int Reward) {
    this->Reward = Reward;
}


// ???????????? ?? ???????????????? ???????????? ??????????
void Creep::killCreep(std::vector <Creep>& Creeps, std::vector<std::pair<Creep, float>>& Dead, int creepNumber, float deltaTime) {
    auto it = Creeps.begin();
    for (int i = 0; i < creepNumber; ++i) {
        it++;
    }
    auto& creep = *it;
    creep.animation.totalTime = 0;
    creep.animation.currImage.x = 0;
    Row = 1;
    Dead.push_back({ creep, deadTime });
    this->startProcessing(deltaTime, "clear");
    Creeps.erase(it);
}


std::vector <Ball> Creep::getBalls() {
    return this->BallsFlow;
}

 void Creep::setMediator(MediatorCreepBall *mediator) {
    this->Mediator = mediator;
 }

 void Creep::startProcessing(float deltaTime, const std::string Event) {
    if (Event == "flight") this->Mediator->processFlight(this, deltaTime);
    if (Event == "clear") this->Mediator->clearBallsFlow(this);
}

 void Creep::addBall(Ball& ball) {
     this->BallsFlow.push_back(ball);
 }
