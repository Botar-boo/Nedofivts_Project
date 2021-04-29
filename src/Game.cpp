#include "Game.h"


// General object that contains all information about current game
Game* Game::instance;

Game::Game() {}

void Game::startGame(bool Hard) {
    this->gameOver = false;
    this->playerHealth = 10;
    this->playerGold = 40;
    this->waveNumber = 0;
    this->Hard = Hard;
}

bool Game::get_gameOver() {
    return gameOver;
}
bool Game::get_Hard() {
    return Hard;
}
int Game::get_playerHealth() {
    return playerHealth;
}
unsigned int Game::get_playerGold() {
    return playerGold;
}
unsigned int Game::get_waveNumber() {
    return waveNumber;
}
void Game::switch_gameOver() {
    gameOver = 1 - gameOver;
}
void Game::decr_playerHealth() {
    playerHealth--;
}
void Game::set_playerGold(int Gold) {
    playerGold += Gold;
}
void Game::incr_waveNumber() {
    waveNumber++;
}
