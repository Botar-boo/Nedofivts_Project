﻿#pragma once
#include "Creep.h"


Creep::Creep(userImages& Texture, userSprite& startBlock, Vector<int> imageCount, float sizeX, float sizeY, float Health, float Speed) :
    Unit(
        Texture,
        imageCount,
        sizeX,
        sizeY) {
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

// Preparing creep animation for update
void Creep::Update(float deltaTime) {
    Vector<float> movement = { 0.0f, 0.0f };

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

    Animation.Update(Row, deltaTime, faceRight);
    Body.setTextureArea(Animation.uvRect);
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

// Смерть и анимация смерти крипа
void Creep::killCreep(std::vector <Creep>& Creeps, std::vector<std::pair<Creep, float>>& Dead, int creepNumber, float deltaTime) {
    auto it = Creeps.begin();
    for (int i = 0; i < creepNumber; ++i) {
        it++;
    }
    it->Animation.totalTime = 0;
    it->Animation.currImage.x = 0;
    Row = 1;
    Dead.push_back({ *it, deadTime });
    Creeps.erase(it);
}
