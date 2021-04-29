#pragma once
class Game {
public:
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
    bool get_Hard();
    int get_playerHealth();
    unsigned int get_playerGold();
    unsigned int get_waveNumber();
    void switch_gameOver();
    void decr_playerHealth();
    void set_playerGold(int Gold);
    void incr_waveNumber();

    void startGame(bool Hard);

private:
    Game();
    bool gameOver;
    int playerHealth;
    unsigned int playerGold;
    unsigned int waveNumber;
    bool Hard;

};
