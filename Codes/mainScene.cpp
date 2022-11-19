#include "mainScene.h"

void MainScene::draw()
{
    ChunkLoader::draw();
    Player::draw();
    Raycast::drawBlockSelection();
}