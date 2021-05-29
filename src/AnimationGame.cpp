#include "../include/AnimationGame.h"


Animation::Animation(userImages* texture, Vector<int> imageCount, float switchTime) {
    this->imageCount.x = imageCount.x;
    this->imageCount.y = imageCount.y;
    this->switchTime = switchTime;
    this->totalTime = 0.0f;

    this->uvRect.width = static_cast <int> (texture->getImageSize().x) / (imageCount.x);
    this->uvRect.height = static_cast <int> (texture->getImageSize().y) / (imageCount.y);
}


// Units animation update
void Animation::Update(int row, float deltaTime, bool faceRight) {
    currImage.y = row;
    totalTime += deltaTime;
    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currImage.x++;
        if (currImage.x >= imageCount.x)
            currImage.x = 0;

    }
    uvRect.top = currImage.y * uvRect.height;

    if (faceRight) {
        uvRect.left = currImage.x * abs(uvRect.width);
        uvRect.width = abs(uvRect.width);
    }
    else {
        uvRect.left = (currImage.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }

}
