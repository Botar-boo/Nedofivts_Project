#include "../include/Maps.h"

// Map rendering

void drawMap(userRenderWindow& Window, MAP& Map) {
    for (unsigned int i = 0; i < Map.Road.size(); ++i) {
        Window.userDraw(Map.Road[i].first);
    }
    for (unsigned int i = 0; i < Map.Grass.size(); ++i) {
        Window.userDraw(Map.Grass[i].first);
    }
}

// Create map

void createMap(MAP& map, const GameSettings& gameSettings, std::vector <userImages>& Textures) {
    std::vector <std::vector <int>> pseudoMap(mapSize.x, std::vector <int>(mapSize.y));
    switch (gameSettings.MapNumber) {
        case 0:
            fillMap0(pseudoMap);
            break;
        case 1:
            fillMap1(pseudoMap);
            break;
        case 2:
            fillMap2(pseudoMap);
            break;
    }
    constructMap(map, pseudoMap, Textures);
}

// Construct map based on 2-dims array

void constructMap(MAP& Map, std::vector <std::vector<int>>& pseudoMap, std::vector <userImages>& Textures) {
    for (unsigned int i = 0; i < pseudoMap[0].size(); ++i) {
        for (unsigned int j = 0; j < pseudoMap.size(); ++j) {
            switch (pseudoMap[j][i]) {
            case 0: {
                userSprite block(Textures[7]);
                block.setPos(blockSize.x * i, blockSize.y * j);
                Map.Grass.push_back({ block,false });
                break;
            }
            case 1: {
                userSprite block(Textures[8]);
                block.setPos(blockSize.x * i, blockSize.y * j);
                Map.Road.push_back({ block, 1 });
                break;
            }
            case 2: {
                userSprite block(Textures[9]);
                block.setPos(blockSize.x * i, blockSize.y * j);
                Map.Road.push_back({ block, 2 });
                break;
            }
            case 3: {
                userSprite block(Textures[11]);
                block.setPos(blockSize.x * i, blockSize.y * j);
                Map.Road.push_back({ block, 3 });
                break;
            }
            case 4: {
                userSprite block(Textures[10]);
                block.setPos(blockSize.x * i, blockSize.y * j);
                Map.Road.push_back({ block, 4 });
                break;
            }
            case 5: {
                userSprite block(Textures[12]);
                block.setPos(blockSize.x * i, blockSize.y * j);
                Map.Road.push_back({ block, 5 });
                break;
            }
            case 6: {
                userSprite block(Textures[13]);
                block.setPos(blockSize.x * i, blockSize.y * j);
                Map.Road.push_back({ block, 6 });
                break;
            }
            case -10: {
                userSprite block(Textures[8]);
                block.setPos(blockSize.x * i, blockSize.y * j);
                Map.startNumb = Map.Road.size();
                Map.Road.push_back({ block, 1 });
                break;
            }
            case 10: {
                userSprite block(Textures[8]);
                block.setPos(blockSize.x * i, blockSize.y * j);
                Map.endNumb = Map.Road.size();
                Map.Road.push_back({ block, 1 });
                break;
            }
            }
        }
    }

}


// Filling arrays

// -10 10 - staring and end point
// 3 = |_ , 4 = |-, 5 = _|, 6 = -| - turn point

void fillMap0(std::vector <std::vector <int>>& Map) {
    Map[6][0] = -10;
    Map[6][1] = 1;
    Map[6][2] = 5;
    Map[5][2] = 2;
    Map[4][2] = 2;
    Map[3][2] = 2;
    Map[2][2] = 2;
    Map[1][2] = 4;
    Map[1][3] = 1;
    Map[1][4] = 1;
    Map[1][5] = 6;
    Map[2][5] = 2;
    Map[3][5] = 2;
    Map[4][5] = 2;
    Map[5][5] = 2;
    Map[6][5] = 2;
    Map[7][5] = 2;
    Map[8][5] = 2;
    Map[9][5] = 2;
    Map[10][5] = 2;
    Map[11][5] = 3;
    Map[11][6] = 1;
    Map[11][7] = 1;
    Map[11][8] = 1;
    Map[11][9] = 5;
    Map[10][9] = 2;
    Map[9][9] = 2;
    Map[8][9] = 2;
    Map[7][9] = 2;
    Map[6][9] = 2;
    Map[5][9] = 2;
    Map[4][9] = 2;
    Map[3][9] = 2;
    Map[2][9] = 2;
    Map[1][9] = 4;
    Map[1][10] = 1;
    Map[1][11] = 1;
    Map[1][12] = 1;
    Map[1][13] = 1;
    Map[1][14] = 6;
    Map[2][14] = 2;
    Map[3][14] = 2;
    Map[4][14] = 2;
    Map[5][14] = 2;
    Map[6][14] = 2;
    Map[7][14] = 2;
    Map[8][14] = 2;
    Map[9][14] = 2;
    Map[10][14] = 2;
    Map[11][14] = 3;
    Map[11][15] = 1;
    Map[11][16] = 1;
    Map[11][17] = 1;
    Map[11][18] = 5;
    Map[10][18] = 2;
    Map[9][18] = 2;
    Map[8][18] = 2;
    Map[7][18] = 2;
    Map[6][18] = 4;
    Map[6][19] = 10;
}

void fillMap1(std::vector <std::vector <int>>& Map) {
    Map[7][0] = -10;
    Map[7][1] = 1;
    Map[7][2] = 1;
    Map[7][3] = 1;
    Map[7][4] = 1;
    Map[7][5] = 1;
    Map[7][6] = 1;
    Map[7][7] = 1;
    Map[7][8] = 1;
    Map[7][9] = 1;
    Map[7][10] = 1;
    Map[7][11] = 6;
    Map[8][11] = 2;
    Map[9][11] = 3;
    Map[9][12] = 1;
    Map[9][13] = 1;
    Map[9][14] = 1;
    Map[9][15] = 1;
    Map[9][16] = 5;
    Map[8][16] = 2;
    Map[7][16] = 2;
    Map[6][16] = 4;
    Map[6][17] = 1;
    Map[6][18] = 1;
    Map[6][19] = 10;
}

// 3 = |_ , 4 = |-, 5 = _|, 6 = -| - turn point
void fillMap2(std::vector <std::vector <int>>& Map) {
    Map[7][0] = -10;
    Map[7][1] = 1;
    Map[7][2] = 1;
    Map[7][3] = 6;
    Map[8][3] = 2;
    Map[9][3] = 2;
    Map[10][3] = 2;
    Map[11][3] = 3;
    Map[11][4] = 1;
    Map[11][5] = 1;
    Map[11][6] = 1;
    Map[11][7] = 1;
    Map[11][8] = 1;
    Map[11][9] = 5;
    Map[10][9] = 2;
    Map[9][9] = 2;
    Map[8][9] = 2;
    Map[7][9] = 2;
    Map[6][9] = 2;
    Map[5][9] = 2;
    Map[4][9] = 4;
    Map[4][10] = 1;
    Map[4][11] = 1;
    Map[4][12] = 6;
    Map[5][12] = 2;
    Map[6][12] = 2;
    Map[7][12] = 2;
    Map[8][12] = 2;
    Map[9][12] = 2;
    Map[10][12] = 2;
    Map[11][12] = 3;
    Map[11][13] = 1;
    Map[11][14] = 1;
    Map[11][15] = 1;
    Map[11][16] = 5;
    Map[10][16] = 2;
    Map[9][16] = 2;
    Map[8][16] = 2;
    Map[7][16] = 2;
    Map[6][16] = 4;
    Map[6][17] = 1;
    Map[6][18] = 1;
    Map[6][19] = 10;
}