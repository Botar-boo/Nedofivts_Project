#pragma once
#include "Maps.h"

class Game {
public:
    //singleton
    static Game* instance;
    static Game* get_instance() {
        if (instance) {
            return instance;
        }
        else {
            instance = new Game();
            return instance;
        }
    }
    bool get_gameOver();
    bool get_difficulty();
    int get_playerHealth();
    unsigned int get_playerGold();
    unsigned int get_waveNumber();
    void switch_gameOver();
    void set_gameOver();
    void decr_playerHealth();
    void set_playerGold(int Gold);
    void incr_waveNumber();

    void startGame(bool Diff);

public:
    std::vector <std::pair<Creep, float>> Dead;
    std::vector <Tower*> Towers;
    std::vector <std::pair<Creep, std::vector<Ball>>> Creeps; // Восхождение Кракена
private:
    Game();
    bool gameOver;
    int playerHealth;
    unsigned int playerGold;
    unsigned int waveNumber;
    bool isHard; // true = Hard, false = Easy
};