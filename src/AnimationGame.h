#include "Adapter.h"


// Default values

const unsigned int windowWidth = 960;
const unsigned int windowHeight = 672;

const float blockSizeX = 48;
const float blockSizeY = 48;

const unsigned int roundsToWin = 10;

const unsigned int defaultRadius = 10;


const unsigned int samSpeed = 100;
const unsigned int batSpeed = 140;
const unsigned int samHealth = 8;
const unsigned int batHealth = 4;
const unsigned int samSizeX = 48;
const unsigned int samSizeY = 48;
const unsigned int batSizeX = 32;
const unsigned int batSizeY = 32;
const unsigned int samReward = 10;
const unsigned int batReward = 5;
const unsigned int minSpeed = 50;
const unsigned int fireBallDamage = 2;
const unsigned int snowBallDamage = 1;
const unsigned int desolBallDamage = 3;
const unsigned int singleTowerPrice = 20;
const unsigned int multiTowerPrice = 40;
const unsigned int freezingTowerPrice = 30;
const unsigned int onePunchTowerPrice = 40;
const unsigned int multiTowerShotCount = 3;
const unsigned int towerRadius = 100;
const unsigned int winWaveGold = 5;
const unsigned int fontSize1 = 30;
const unsigned int fontSize2 = 40;
const float slowSnowBall = 0.3f;
const float desolDesolBall = 0.1f;
const float deadTime = 0.9f;
const float animationTime = 0.3f;
const float batEvasion = 0.1f;
const float samEvasion = 0.01f;
const float batArmor = 0.25f;
const float samArmor = 0.4f;
const float evasionMul = 1.03f;
const float armorMul = 1.04f;
const float towerReloadTime = 1.0f;

const unsigned int defaultBallSpeed = 300;
const vectorU mapSize = { 14, 20 };
const vectorU creepImageCount = { 3, 2 };
const vectorU towerImageCount = { 3, 1 };
const vectorF towerSize = { 48, 72 };
const vectorF gameOverPosition = { 220, 70 };
const vectorF moneyPosition = { 820, 630 };
const vectorF healthPosition = { 380, 620 };
const vectorF wavePosition = { 5, 630 };
const vectorF originPosition = { 100, 100 };
const vectorF blockSize = { 48.0f, 48.0f };



class Animation {
public:
    Animation(tImages* texture, vectorU imageCount, float switchTime);
    ~Animation() {};
    void Update(int row, float deltaTime, bool FaceRight);
public:
    IntRect uvRect;
    float totalTime;
    vectorU currImage = { 0, 0 };
private:
    vectorU imageCount;

    float switchTime;
};
