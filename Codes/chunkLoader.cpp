#include "chunkLoader.h"

void Chunk::init(int x, int y, int z)
{
    chunkCoord.x = x;
    chunkCoord.y = y;
    chunkCoord.z = z;
}

void Chunk::addBlockSurface(float x, float y, float z, Dir dir, BlockTexturePos blockTexturePosX, BlockTexturePos blockTexturePosY)
{
    float s = (float)blockTexturePosX * BLOCK_PIXEL_WH / (float)ChunkLoader::getBlockTextures().getWidth();
    float t = (float)blockTexturePosY * BLOCK_PIXEL_WH / (float)ChunkLoader::getBlockTextures().getHeight();
    s += BLOCK_PIXEL_WH / (float)ChunkLoader::getBlockTextures().getWidth() / 10;
    t += BLOCK_PIXEL_WH / (float)ChunkLoader::getBlockTextures().getHeight() / 10;
    // block texture width and height
    float szw = BLOCK_PIXEL_WH / (float)ChunkLoader::getBlockTextures().getWidth();
    float szh = BLOCK_PIXEL_WH / (float)ChunkLoader::getBlockTextures().getHeight();
    szw -= BLOCK_PIXEL_WH / (float)ChunkLoader::getBlockTextures().getWidth() / 10 * 2;
    szh -= BLOCK_PIXEL_WH / (float)ChunkLoader::getBlockTextures().getHeight() / 10 * 2;

    if (dir == TOP)
    {
        std::array<float, 48> surface = {
            x  , y+1,   z,  0,  1,  0,  s    , t+szh, //A
            x+1, y+1, z+1,  0,  1,  0,  s+szw, t    , //C
            x  , y+1, z+1,  0,  1,  0,  s    , t    , //D

            x  , y+1, z  ,  0,  1,  0,  s    , t+szh, //A
            x+1, y+1, z  ,  0,  1,  0,  s+szw, t+szh, //B
            x+1, y+1, z+1,  0,  1,  0,  s+szw, t    , //C
        };
        surfaces.insert(surfaces.end(), surface.begin(), surface.end());
    }
    else if (dir == BOTTOM)
    {
        std::array<float, 48> surface = {
            x  , y  , z  ,  0, -1,  0,  s+szw, t+szh, //E
            x  , y  , z+1,  0, -1,  0,  s+szw, t    , //H
            x+1, y  , z+1,  0, -1,  0,  s    , t    , //G

            x  , y  , z  ,  0, -1,  0,  s+szw, t+szh, //E
            x+1, y  , z+1,  0, -1,  0,  s    , t    , //G
            x+1, y  , z  ,  0, -1,  0,  s    , t+szh, //F
        };
        surfaces.insert(surfaces.end(), surface.begin(), surface.end());
    }
    else if (dir == LEFT)
    {
        std::array<float, 48> surface = {
            x  , y+1, z  , -1,  0,  0,  s    , t+szh, //A
            x  , y+1, z+1, -1,  0,  0,  s+szw, t+szh, //D
            x  , y  , z+1, -1,  0,  0,  s+szw, t    , //H

            x  , y+1, z  , -1,  0,  0,  s    , t+szh, //A
            x  , y  , z+1, -1,  0,  0,  s+szw, t    , //H
            x  , y  , z  , -1,  0,  0,  s    , t    , //E
        };
        surfaces.insert(surfaces.end(), surface.begin(), surface.end());
    }
    else if (dir == RIGHT)
    {
        std::array<float, 48> surface = {
            x+1, y+1, z  ,  1,  0,  0,  s+szw, t+szh, //B
            x+1, y  , z+1,  1,  0,  0,  s    , t    , //G
            x+1, y+1, z+1,  1,  0,  0,  s    , t+szh, //C

            x+1, y+1, z  ,  1,  0,  0,  s+szw, t+szh, //B
            x+1, y  , z  ,  1,  0,  0,  s+szw, t    , //F
            x+1, y  , z+1,  1,  0,  0,  s    , t    , //G
        };
        surfaces.insert(surfaces.end(), surface.begin(), surface.end());
    }
    else if (dir == FORWARD)
    {
        std::array<float, 48> surface = {
            x  , y+1, z+1,  0,  0,  1,  s    , t+szh, //D
            x+1, y+1, z+1,  0,  0,  1,  s+szw, t+szh, //C
            x+1, y  , z+1,  0,  0,  1,  s+szw, t    , //G

            x  , y+1, z+1,  0,  0,  1,  s    , t+szh, //D
            x+1, y  , z+1,  0,  0,  1,  s+szw, t    , //G
            x  , y  , z+1,  0,  0,  1,  s    , t    , //H
        };
        surfaces.insert(surfaces.end(), surface.begin(), surface.end());
    }
    else if (dir == BACKWARD)
    {
        std::array<float, 48> surface = {
            x  , y+1, z  ,  0,  0, -1,  s+szw, t+szh, //A
            x+1, y  , z  ,  0,  0, -1,  s    , t    , //F
            x+1, y+1, z  ,  0,  0, -1,  s    , t+szh, //B

            x  , y+1, z  ,  0,  0, -1,  s+szw, t+szh, //A
            x  , y  , z  ,  0,  0, -1,  s+szw, t    , //E
            x+1, y  , z  ,  0,  0, -1,  s    , t    , //F
        };
        surfaces.insert(surfaces.end(), surface.begin(), surface.end());
    }
}

void Chunk::addBlock(int x, int y, int z, NearbyBlocks nearbyBlocks, BlockTexturePos blockTexturePosX, BlockTexturePos blockTexturePosY)
{
    if (!nearbyBlocks.top)
    {
        addBlockSurface(x, y, z, TOP, blockTexturePosX, blockTexturePosY);
    }
    if (!nearbyBlocks.bottom)
    {
        addBlockSurface(x, y, z, BOTTOM, blockTexturePosX, blockTexturePosY);
    }
    if (!nearbyBlocks.left)
    {
        addBlockSurface(x, y, z, LEFT, blockTexturePosX, blockTexturePosY);
    }
    if (!nearbyBlocks.right)
    {
        addBlockSurface(x, y, z, RIGHT, blockTexturePosX, blockTexturePosY);
    }
    if (!nearbyBlocks.forward)
    {
        addBlockSurface(x, y, z, FORWARD, blockTexturePosX, blockTexturePosY);
    }
    if (!nearbyBlocks.backward)
    {
        addBlockSurface(x, y, z, BACKWARD, blockTexturePosX, blockTexturePosY);
    }
}

void Chunk::load()
{
    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        int worldX = chunkCoord.x*CHUNK_SIZE + x;
        for (int z = 0; z < CHUNK_SIZE; z++)
        {
            int worldZ = chunkCoord.z*CHUNK_SIZE + z;
            float terrainHeight1 = ChunkLoader::getTerrainHeight1(worldX, worldZ);
            float terrainHeight2 = ChunkLoader::getTerrainHeight2(worldX, worldZ);
            float combinedTerrainHeight = terrainHeight1 * 0.6 + terrainHeight2 * 0.4;
            for (int y = 0; y < CHUNK_SIZE; y++)   
            {
                int worldY = chunkCoord.y*CHUNK_SIZE + y;
                float terrainAlphaValue = ChunkLoader::getTerrainAlphaValue(worldX, worldY, worldZ);
                float caveTerrainDistanceEffect = ((combinedTerrainHeight + 1) / 2) * 0.9 + 0.1;
                float terrainHeight = ChunkLoader::convertToBlockHeight(combinedTerrainHeight);
                float caveHeight = -30*caveTerrainDistanceEffect + ChunkLoader::convertToBlockHeight(combinedTerrainHeight);
                float terrainAlphaValuesEffect = ((float)worldY - caveHeight) / (terrainHeight - caveHeight);

                float cheeseCaveAlphaValue = ChunkLoader::getCheeseCaveAlphaValue(worldX, worldY, worldZ);
                float noodleCaveAlphaValue1 = ChunkLoader::getNoodleCaveAlphaValue1(worldX, worldY, worldZ);
                float noodleCaveAlphaValue2 = ChunkLoader::getNoodleCaveAlphaValue2(worldX, worldY, worldZ);

                float cheeseCaveAlphaValueEffect = (caveHeight - 200 - worldY) / 400; 
                if (cheeseCaveAlphaValueEffect > 0.5)
                {
                    cheeseCaveAlphaValueEffect = 0.5;
                }
                if (!(terrainAlphaValue > -terrainAlphaValuesEffect) && !(cheeseCaveAlphaValue > 0.5 - cheeseCaveAlphaValueEffect)
                && !(noodleCaveAlphaValue1 > -0.15 && noodleCaveAlphaValue1 < 0.15 && noodleCaveAlphaValue2 > -0.3 && noodleCaveAlphaValue2 < 0.3))
                {
                    blocks[x][y][z].blockType = BLOCK;
                }
            }
        }
    }
}

void Chunk::reloadSurfaces()
{
    reloadingSurfaces = true;
    surfaces.clear();

    std::array<std::array<std::array<Block, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> topChunk;
    std::array<std::array<std::array<Block, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> bottomChunk;
    std::array<std::array<std::array<Block, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> leftChunk;
    std::array<std::array<std::array<Block, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> rightChunk;
    std::array<std::array<std::array<Block, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> forwardChunk;
    std::array<std::array<std::array<Block, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> backwardChunk;

    bool topChunkLoaded = ChunkLoader::getChunkBlocks(chunkCoord.x, chunkCoord.y + 1, chunkCoord.z, topChunk);
    bool bottomChunkLoaded = ChunkLoader::getChunkBlocks(chunkCoord.x, chunkCoord.y - 1, chunkCoord.z, bottomChunk);
    bool leftChunkLoaded = ChunkLoader::getChunkBlocks(chunkCoord.x - 1, chunkCoord.y, chunkCoord.z, leftChunk);
    bool rightChunkLoaded = ChunkLoader::getChunkBlocks(chunkCoord.x + 1, chunkCoord.y, chunkCoord.z, rightChunk);
    bool forwardChunkLoaded = ChunkLoader::getChunkBlocks(chunkCoord.x, chunkCoord.y, chunkCoord.z + 1, forwardChunk);
    bool backwardChunkLoaded = ChunkLoader::getChunkBlocks(chunkCoord.x, chunkCoord.y, chunkCoord.z - 1, backwardChunk);

    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                if (blocks[x][y][z].blockType != AIR)
                {
                    NearbyBlocks nearbyBlocks;
                    
                    if (y + 1 < CHUNK_SIZE)
                    {
                        if (blocks[x][y + 1][z].blockType != AIR)
                        {
                            nearbyBlocks.top = true;
                        }
                    }
                    else
                    {
                        if (topChunkLoaded && topChunk[x][0][z].blockType != AIR)
                        {
                            nearbyBlocks.top = true;
                        }
                    }

                    if (y - 1 >= 0)
                    {
                        if (blocks[x][y - 1][z].blockType != AIR)
                        {
                            nearbyBlocks.bottom = true;
                        }
                    }
                    else
                    {
                        if (bottomChunkLoaded && bottomChunk[x][CHUNK_SIZE - 1][z].blockType != AIR)
                        {
                            nearbyBlocks.bottom = true;
                        }
                    }

                    if (x - 1 >= 0)
                    {
                        if (blocks[x - 1][y][z].blockType != AIR)
                        {
                            nearbyBlocks.left = true;
                        }
                    }
                    else
                    {
                        if (leftChunkLoaded && leftChunk[CHUNK_SIZE - 1][y][z].blockType != AIR)
                        {
                            nearbyBlocks.left = true;
                        }
                    }

                    if (x + 1 < CHUNK_SIZE)
                    {
                        if (blocks[x + 1][y][z].blockType != AIR)
                        {
                            nearbyBlocks.right = true;
                        }
                    }
                    else
                    {
                        if (rightChunkLoaded && rightChunk[0][y][z].blockType != AIR)
                        {
                            nearbyBlocks.right = true;
                        }
                    }

                    if (z + 1 < CHUNK_SIZE)
                    {
                        if (blocks[x][y][z + 1].blockType != AIR)
                        {
                            nearbyBlocks.forward = true;
                        }
                    }
                    else
                    {
                        if (forwardChunkLoaded && forwardChunk[x][y][0].blockType != AIR)
                        {
                            nearbyBlocks.forward = true;
                        }
                    }

                    if (z - 1 >= 0)
                    {
                        if (blocks[x][y][z - 1].blockType != AIR)
                        {
                            nearbyBlocks.backward = true;
                        }
                    }
                    else
                    {
                        if (backwardChunkLoaded && backwardChunk[x][y][CHUNK_SIZE - 1].blockType != AIR)
                        {
                            nearbyBlocks.backward = true;
                        }
                    }

                    BlockTexturePos blockTexturePosX, blockTexturePosY;
                    if (blocks[x][y][z].blockType == BLOCK)
                    {
                        blockTexturePosX = DEFAULT_BLOCK_X;
                        blockTexturePosY = DEFAULT_BLOCK_Y;
                    }
                    else if (blocks[x][y][z].blockType == BLUE_LIGHT)
                    {
                        blockTexturePosX = BLUE_LIGHT_BLOCK_X;
                        blockTexturePosY = BLUE_LIGHT_BLOCK_Y;
                    }
                    else if (blocks[x][y][z].blockType == YELLOW_LIGHT)
                    {
                        blockTexturePosX = YELLOW_LIGHT_BLOCK_X;
                        blockTexturePosY = YELLOW_LIGHT_BLOCK_Y;
                    }
                    else if (blocks[x][y][z].blockType == GREEN_LIGHT)
                    {
                        blockTexturePosX = GREEN_LIGHT_BLOCK_X;
                        blockTexturePosY = GREEN_LIGHT_BLOCK_Y;
                    }
                    else if (blocks[x][y][z].blockType == RED_LIGHT)
                    {
                        blockTexturePosX = RED_LIGHT_BLOCK_X;
                        blockTexturePosY = RED_LIGHT_BLOCK_Y;
                    }
                    addBlock(x, y, z, nearbyBlocks, blockTexturePosX, blockTexturePosY);
                }
            }
        }
    }

    VAOReloadRequest = true;
    std::lock_guard<std::mutex> lock(chunkLoadMutex);
    reloadingSurfaces = false;
}

void Chunk::draw()
{
    glm::mat4 modelMat = glm::mat4(1.0f);
    modelMat = glm::translate(modelMat, glm::vec3(chunkCoord.x*CHUNK_SIZE, chunkCoord.y*CHUNK_SIZE, chunkCoord.z*CHUNK_SIZE));
    
    glUseProgram(defaultShader.getShaderProgram());
    glUniformMatrix4fv(defaultShader.getModelMatUniformLocation(), 1, GL_FALSE, glm::value_ptr(modelMat));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ChunkLoader::getBlockTextures().getTexture());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, ChunkLoader::getBlockLightTextures().getTexture());
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, surfaces.size() / 8);
}

void Chunk::drawGBuffer()
{
    glm::mat4 modelMat = glm::mat4(1.0f);
    modelMat = glm::translate(modelMat, glm::vec3(chunkCoord.x*CHUNK_SIZE, chunkCoord.y*CHUNK_SIZE, chunkCoord.z*CHUNK_SIZE));
    
    glUseProgram(GBuffer::getPositionShaderProgram());
    glUniformMatrix4fv(GBuffer::getPositionModelMatUniformLocation(), 1, GL_FALSE, glm::value_ptr(modelMat));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, surfaces.size() / 8);
}

Pos Chunk::getCoord()
{
    return chunkCoord;
}

void Chunk::release()
{
    glDeleteVertexArrays(1, &VAO);
}

Block Chunk::getBlock(int x, int y, int z)
{
    return blocks[x][y][z];
}

std::array<std::array<std::array<Block, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> Chunk::getChunkBlocks()
{
    return blocks;
}

void Chunk::placeBlock(int x, int y, int z, BlockType blockType)
{
    blocks[x][y][z].blockType = blockType;
}

void Chunk::breakBlock(int x, int y, int z)
{
    blocks[x][y][z].blockType = AIR;
}

ChunkLoadStatus Chunk::getChunkLoadStatus()
{
    return chunkLoadStatus;
}

void Chunk::setChunkLoadStatus(ChunkLoadStatus status)
{
    chunkLoadStatus = status;
}

bool Chunk::VAOReloadRequested()
{
    return VAOReloadRequest;
}

void Chunk::reloadVAO()
{   
    if (VAOgenerated)
    {
        glDeleteVertexArrays(1, &VAO);
    }
    else
    {
        VAOgenerated = true;
    }

    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, surfaces.size() * sizeof(float), &surfaces[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    glDeleteBuffers(1, &VBO);

    VAOReloadRequest = false;
}

bool Chunk::isReloadingSurfaces()
{
    return reloadingSurfaces;
}



std::unordered_map<std::string, Chunk> ChunkLoader::chunks;
FastNoiseLite ChunkLoader::terrainHeightNoise;
FastNoiseLite ChunkLoader::terrainHeightNoise2;
FastNoiseLite ChunkLoader::terrainNoise3d;
FastNoiseLite ChunkLoader::cheeseCaveNoise;
FastNoiseLite ChunkLoader::noodleCaveNoise1;
FastNoiseLite ChunkLoader::noodleCaveNoise2;

Texture ChunkLoader::blockTextures;
Texture ChunkLoader::blockLightTextures;

std::vector<Light> ChunkLoader::lights;

std::thread ChunkLoader::chunkLoadThread(ChunkLoader::chunkLoadThreadFunction);
bool ChunkLoader::chunkLoadThreadStopped = false;

void ChunkLoader::chunkLoadThreadFunction()
{
    while (not chunkLoadThreadStopped)
    {
        ChunkLoader::loadChunksAround(playerPos.x, playerPos.y, playerPos.z, RENDER_DISTANCE);
    }
}

void ChunkLoader::loadChunk(int x, int y, int z)
{
    std::string key = convertToKey(x, y, z);
    ChunkLoadStatus chunkLoadStatus = getChunkLoadStatus(key);
    if (chunkLoadStatus == NOT_LOADED)
    {
        Chunk chunk;
        chunk.init(x, y, z);
        chunks.insert(std::make_pair(key, chunk));

        chunks[key].load();
        chunks[key].reloadSurfaces();
        Pos chunkCoord = chunks[key].getCoord();

        if (chunkLoaded(x, y + 1, z))
        {
            std::string key = convertToKey(x, y + 1, z);
            if (!chunks[key].isReloadingSurfaces())
            {
                chunks[key].reloadSurfaces();
            }
        }
        if (chunkLoaded(x, y - 1, z))
        {
            std::string key = convertToKey(x, y - 1, z);
            if (!chunks[key].isReloadingSurfaces())
            {
                chunks[key].reloadSurfaces();
            }
        }
        if (chunkLoaded(x - 1, y, z))
        {
            std::string key = convertToKey(x - 1, y, z);
            if (!chunks[key].isReloadingSurfaces())
            {
                chunks[key].reloadSurfaces();
            }
        }
        if (chunkLoaded(x + 1, y, z))
        {
            std::string key = convertToKey(x + 1, y, z);
            if (!chunks[key].isReloadingSurfaces())
            {
                chunks[key].reloadSurfaces();
            }
        }
        if (chunkLoaded(x, y, z + 1))
        {
            std::string key = convertToKey(x, y, z + 1);
            if (!chunks[key].isReloadingSurfaces())
            {
                chunks[key].reloadSurfaces();
            }
        }
        if (chunkLoaded(x, y, z - 1))
        {
            std::string key = convertToKey(x, y, z - 1);
            if (!chunks[key].isReloadingSurfaces())
            {
                chunks[key].reloadSurfaces();
            }
        }

        std::lock_guard<std::mutex> lock(chunkLoadMutex);
        chunks[key].setChunkLoadStatus(LOADED);
    }
}

std::unordered_map<std::string, Chunk>::iterator ChunkLoader::unloadChunk(int x, int y, int z)
{
    std::string key = convertToKey(x, y, z);
    std::unordered_map<std::string, Chunk>::iterator i = chunks.find(key);

    if (i != chunks.end())
    {
        chunks[key].release();
        return chunks.erase(i);
    }

    return ++i;
}

void ChunkLoader::init()
{
    terrainHeightNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    terrainHeightNoise.SetSeed(rand());
    terrainHeightNoise.SetFractalOctaves(3);
    terrainHeightNoise.SetFrequency(0.005);

    terrainHeightNoise2.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    terrainHeightNoise2.SetSeed(rand());
    terrainHeightNoise2.SetFractalOctaves(1);
    terrainHeightNoise2.SetFrequency(0.002);

    terrainNoise3d.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    terrainNoise3d.SetSeed(rand());
    terrainNoise3d.SetFractalOctaves(3);
    terrainNoise3d.SetFrequency(0.02);

    cheeseCaveNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    cheeseCaveNoise.SetSeed(rand());
    cheeseCaveNoise.SetFractalOctaves(3);
    cheeseCaveNoise.SetFrequency(0.02);
    
    noodleCaveNoise1.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noodleCaveNoise1.SetSeed(rand());
    noodleCaveNoise1.SetFractalOctaves(3);
    noodleCaveNoise1.SetFrequency(0.02);

    noodleCaveNoise2.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noodleCaveNoise2.SetSeed(rand());
    noodleCaveNoise2.SetFractalOctaves(3);
    noodleCaveNoise2.SetFrequency(0.02);

    blockTextures.load("./Textures/blockTexturesUpScaled.png", LINEAR);
    blockLightTextures.load("./Textures/blockLightTexturesUpScaled.png", LINEAR);
    glUseProgram(defaultShader.getShaderProgram());
    glUniform1i(glGetUniformLocation(defaultShader.getShaderProgram(), "blockTextures"), 0);
    glUniform1i(glGetUniformLocation(defaultShader.getShaderProgram(), "blockLightTextures"), 1);
}

void ChunkLoader::draw()
{
    glUseProgram(defaultShader.getShaderProgram());
    for (int i = 0; i < lights.size(); i++)
    {
        std::string pointLightPosUniformName = "pointLights[" + std::to_string(i) + "].pos";
        std::string pointLightColorUniformName = "pointLights[" + std::to_string(i) + "].color";
        int pointLightPosUniformLocation = glGetUniformLocation(defaultShader.getShaderProgram(), pointLightPosUniformName.c_str());
        int pointLightColorUniformLocation = glGetUniformLocation(defaultShader.getShaderProgram(), pointLightColorUniformName.c_str());

        glUniform3f(pointLightPosUniformLocation, lights[i].pos.x, lights[i].pos.y, lights[i].pos.z);
        glUniform3f(pointLightColorUniformLocation, lights[i].color.x, lights[i].color.y, lights[i].color.z);
    }
    int numberOfLightsUniformLocation = glGetUniformLocation(defaultShader.getShaderProgram(), "numberOfLights");
    glUniform1i(numberOfLightsUniformLocation, lights.size());

    for (std::unordered_map<std::string, Chunk>::iterator i = chunks.begin(); i != chunks.end(); i++)
    {
        i->second.draw();
    }
}

void ChunkLoader::drawGBuffer()
{
    glUseProgram(GBuffer::getPositionShaderProgram());

    for (std::unordered_map<std::string, Chunk>::iterator i = chunks.begin(); i != chunks.end(); i++)
    {
        i->second.drawGBuffer();
    }
}

void ChunkLoader::update()
{
    for (std::unordered_map<std::string, Chunk>::iterator i = chunks.begin(); i != chunks.end(); i++)
    {
        if(i->second.VAOReloadRequested())
        {
            i->second.reloadVAO();
        }
    }

    std::lock_guard<std::mutex> lock(chunkLoadMutex);
    ChunkLoader::unloadChunksFarFrom(playerPos.x, playerPos.y, playerPos.z, RENDER_DISTANCE + 2);
}

float ChunkLoader::getTerrainHeight1(int x, int z)
{
    return convertTerrainHeight1(terrainHeightNoise.GetNoise((float)x, (float)z));
}

float ChunkLoader::getTerrainHeight2(int x, int z)
{
    return terrainHeightNoise2.GetNoise((float)x, (float)z);
}

float ChunkLoader::convertToBlockHeight(float terrainHeight)
{
    return (terrainHeight + 1)/2 * 80;
}

float ChunkLoader::convertTerrainHeight1(float normalizedTerrainHeight)
{
    if (normalizedTerrainHeight < -0.1726)
    {
        return normalizedTerrainHeight/9 - (float)8/9;
    }
    if (normalizedTerrainHeight < -0.0467)
    {
        return normalizedTerrainHeight*7 + 0.3;
    }
    if (normalizedTerrainHeight < 0.4667)
    {
        return normalizedTerrainHeight/1.75;
    }
    if (normalizedTerrainHeight < 0.5645)
    {
        return normalizedTerrainHeight*7 - 3;
    }
    return normalizedTerrainHeight/9 + (float)8/9;
}

float ChunkLoader::getTerrainAlphaValue(int x, int y, int z)
{
    return terrainNoise3d.GetNoise((float)x, (float)y, (float)z);
}

float ChunkLoader::getCheeseCaveAlphaValue(int x, int y, int z)
{
    return cheeseCaveNoise.GetNoise((float)x, (float)y, (float)z);
}

float ChunkLoader::getNoodleCaveAlphaValue1(int x, int y, int z)
{
    return noodleCaveNoise1.GetNoise((float)x, (float)y, (float)z);
}

float ChunkLoader::getNoodleCaveAlphaValue2(int x, int y, int z)
{
    return noodleCaveNoise2.GetNoise((float)x, (float)y, (float)z);
}

std::string ChunkLoader::convertToKey(int x, int y, int z)
{
    std::string key = "";
    key += std::to_string(x);
    key += " ";
    key += std::to_string(y);
    key += " ";
    key += std::to_string(z);

    return key;
}

bool ChunkLoader::chunkLoaded(int x, int y, int z)
{
    std::string key = convertToKey(x, y, z);
    if (chunks.find(key) != chunks.end())
    {
        return chunks[key].getChunkLoadStatus() == LOADED;
    }
    return false;
}

bool ChunkLoader::chunkLoaded(std::string key)
{
    if (chunks.find(key) != chunks.end())
    {
        return chunks[key].getChunkLoadStatus() == LOADED;
    }
    return false;
}

bool ChunkLoader::chunkLoading(int x, int y, int z)
{
    std::string key = convertToKey(x, y, z);
    if (chunks.find(key) != chunks.end())
    {
        return chunks[key].getChunkLoadStatus() == LOADING;
    }    
    return false;
}

bool ChunkLoader::chunkLoading(std::string key)
{
    if (chunks.find(key) != chunks.end())
    {
        return chunks[key].getChunkLoadStatus() == LOADING;
    }
    return false;
}

ChunkLoadStatus ChunkLoader::getChunkLoadStatus(int x, int y, int z)
{
    std::string key = convertToKey(x, y, z);
    if (chunks.find(key) != chunks.end())
    {
        return chunks[key].getChunkLoadStatus();
    }
    return NOT_LOADED;
}

ChunkLoadStatus ChunkLoader::getChunkLoadStatus(std::string key)
{
    if (chunks.find(key) != chunks.end())
    {
        return chunks[key].getChunkLoadStatus();
    }
    return NOT_LOADED;
}

void ChunkLoader::loadChunksAround(float x, float y, float z, int renderDistance)
{
    int chunkX = floor(x / CHUNK_SIZE);
    int chunkY = floor(y / CHUNK_SIZE);
    int chunkZ = floor(z / CHUNK_SIZE);

    for (int x = chunkX - renderDistance; x <= chunkX + renderDistance; x++)
    {
        for (int y = chunkY - renderDistance; y <= chunkY + renderDistance; y++)
        {
            for (int z = chunkZ - renderDistance; z <= chunkZ + renderDistance; z++)
            {
                loadChunk(x, y, z);
            }
        }
    }
}

void ChunkLoader::unloadChunksFarFrom(float x, float y, float z, int renderDistance)
{
    int chunkX = floor(x / CHUNK_SIZE);
    int chunkY = floor(y / CHUNK_SIZE);
    int chunkZ = floor(z / CHUNK_SIZE);

    for (std::unordered_map<std::string, Chunk>::iterator i = chunks.begin(); i != chunks.end();)
    {
        Pos chunkCoord = i->second.getCoord();
        if (i->second.getChunkLoadStatus() == LOADED && !i->second.isReloadingSurfaces() && (abs(chunkCoord.x - chunkX) > renderDistance || abs(chunkCoord.z - chunkZ) > renderDistance
        || abs(chunkCoord.y - chunkY) > renderDistance))
        {
            i = unloadChunk(chunkCoord.x, chunkCoord.y, chunkCoord.z);
        }
        else
        {
            i++;
        }
    }
}

bool ChunkLoader::getChunkBlocks(int x, int y, int z, std::array<std::array<std::array<Block, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> &blocks)
{
    if (chunkLoaded(x, y, z))
    {
        blocks = chunks[convertToKey(x, y, z)].getChunkBlocks(); 
        return true;
    }
    return false;
}

Block ChunkLoader::getBlock(int x, int y, int z)
{
    int chunkX = floor(((float)x / CHUNK_SIZE));
    int chunkY = floor(((float)y / CHUNK_SIZE));
    int chunkZ = floor(((float)z / CHUNK_SIZE));
    if (chunkLoaded(chunkX, chunkY, chunkZ))
    {
        std::string key = convertToKey(chunkX, chunkY, chunkZ);
        return chunks[key].getBlock(mod(x, CHUNK_SIZE), mod(y, CHUNK_SIZE), mod(z, CHUNK_SIZE));
    }
    return Block();
}

void ChunkLoader::placeBlock(int x, int y, int z, BlockType blockType)
{
    int chunkX = floor(((float)x / CHUNK_SIZE));
    int chunkY = floor(((float)y / CHUNK_SIZE));
    int chunkZ = floor(((float)z / CHUNK_SIZE));
    if (chunkLoaded(chunkX, chunkY, chunkZ))
    {
        std::string key = convertToKey(chunkX, chunkY, chunkZ);
        int blockX = mod(x, CHUNK_SIZE);
        int blockY = mod(y, CHUNK_SIZE);
        int blockZ = mod(z, CHUNK_SIZE);
        chunks[key].placeBlock(blockX, blockY, blockZ, blockType);
        chunks[key].reloadSurfaces();

        if (blockX == CHUNK_SIZE - 1) 
        {
            key = convertToKey(chunkX + 1, chunkY, chunkZ);
            if (chunkLoaded(key))
            {
                chunks[key].reloadSurfaces();
            }
        }
        else if (blockX == 0) 
        {
            key = convertToKey(chunkX - 1, chunkY, chunkZ);
            if (chunkLoaded(key))
            {
                chunks[key].reloadSurfaces();
            }
        }
        if (blockY == CHUNK_SIZE - 1) 
        {
            key = convertToKey(chunkX, chunkY + 1, chunkZ);
            if (chunkLoaded(key))
            {
                chunks[key].reloadSurfaces();
            }
        }
        else if (blockY == 0) 
        {
            key = convertToKey(chunkX, chunkY - 1, chunkZ);
            if (chunkLoaded(key))
            {
                chunks[key].reloadSurfaces();
            }
        }
        if (blockZ == CHUNK_SIZE - 1) 
        {
            key = convertToKey(chunkX, chunkY, chunkZ + 1);
            if (chunkLoaded(key))
            {
                chunks[key].reloadSurfaces();
            }
        }
        else if (blockZ == 0) 
        {
            key = convertToKey(chunkX, chunkY, chunkZ - 1);
            if (chunkLoaded(key))
            {
                chunks[key].reloadSurfaces();
            }
        }
    }

    if (lights.size() >= MAX_NUMBER_OF_LIGHTS)
    {
        lights.erase(lights.begin());
    }
    if (blockType == BLUE_LIGHT)
    {
        lights.push_back({Vec3(x + 0.5, y + 0.5, z + 0.5), Vec3((float)BLUE_LIGHT_BLOCK_LIGHT_COLOR_R / 255, 
                                                                (float)BLUE_LIGHT_BLOCK_LIGHT_COLOR_G / 255, 
                                                                (float)BLUE_LIGHT_BLOCK_LIGHT_COLOR_B / 255)});
    }
    if (blockType == YELLOW_LIGHT)
    {
        lights.push_back({Vec3(x + 0.5, y + 0.5, z + 0.5), Vec3((float)YELLOW_LIGHT_BLOCK_LIGHT_COLOR_R / 255, 
                                                                (float)YELLOW_LIGHT_BLOCK_LIGHT_COLOR_G / 255, 
                                                                (float)YELLOW_LIGHT_BLOCK_LIGHT_COLOR_B / 255)});
    }
    if (blockType == GREEN_LIGHT)
    {
        lights.push_back({Vec3(x + 0.5, y + 0.5, z + 0.5), Vec3((float)GREEN_LIGHT_BLOCK_LIGHT_COLOR_R / 255, 
                                                                (float)GREEN_LIGHT_BLOCK_LIGHT_COLOR_G / 255, 
                                                                (float)GREEN_LIGHT_BLOCK_LIGHT_COLOR_B / 255)});
    }
    if (blockType == RED_LIGHT)
    {
        lights.push_back({Vec3(x + 0.5, y + 0.5, z + 0.5), Vec3((float)RED_LIGHT_BLOCK_LIGHT_COLOR_R / 255, 
                                                                (float)RED_LIGHT_BLOCK_LIGHT_COLOR_G / 255, 
                                                                (float)RED_LIGHT_BLOCK_LIGHT_COLOR_B / 255)});
    }
}

void ChunkLoader::breakBlock(int x, int y, int z)
{
    int chunkX = floor(((float)x / CHUNK_SIZE));
    int chunkY = floor(((float)y / CHUNK_SIZE));
    int chunkZ = floor(((float)z / CHUNK_SIZE));
    if (chunkLoaded(chunkX, chunkY, chunkZ))
    {
        std::string key = convertToKey(chunkX, chunkY, chunkZ);
        int blockX = mod(x, CHUNK_SIZE);
        int blockY = mod(y, CHUNK_SIZE);
        int blockZ = mod(z, CHUNK_SIZE);
        chunks[key].breakBlock(blockX, blockY, blockZ);
        chunks[key].reloadSurfaces();

        if (blockX == CHUNK_SIZE - 1) 
        {
            key = convertToKey(chunkX + 1, chunkY, chunkZ);
            if (chunkLoaded(key))
            {
                chunks[key].reloadSurfaces();
            }
        }
        else if (blockX == 0) 
        {
            key = convertToKey(chunkX - 1, chunkY, chunkZ);
            if (chunkLoaded(key))
            {
                chunks[key].reloadSurfaces();
            }
        }
        if (blockY == CHUNK_SIZE - 1) 
        {
            key = convertToKey(chunkX, chunkY + 1, chunkZ);
            if (chunkLoaded(key))
            {
                chunks[key].reloadSurfaces();
            }
        }
        else if (blockY == 0) 
        {
            key = convertToKey(chunkX, chunkY - 1, chunkZ);
            if (chunkLoaded(key))
            {
                chunks[key].reloadSurfaces();
            }
        }
        if (blockZ == CHUNK_SIZE - 1) 
        {
            key = convertToKey(chunkX, chunkY, chunkZ + 1);
            if (chunkLoaded(key))
            {
                chunks[key].reloadSurfaces();
            }
        }
        else if (blockZ == 0) 
        {
            key = convertToKey(chunkX, chunkY, chunkZ - 1);
            if (chunkLoaded(key))
            {
                chunks[key].reloadSurfaces();
            }
        }
    }

    for (int i = lights.size() - 1; i >= 0; i--)
    {
        if (lights[i].pos == Vec3(x + 0.5, y + 0.5, z + 0.5))
        {
            lights.erase(lights.begin() + i);
            break;
        }
    }
}

Texture ChunkLoader::getBlockTextures()
{
    return blockTextures;
}

Texture ChunkLoader::getBlockLightTextures()
{
    return blockLightTextures;
}

void ChunkLoader::stopChunkLoadThread()
{
    chunkLoadThreadStopped = true;
}

void ChunkLoader::waitAsyncsToFinish()
{
    chunkLoadThread.join();
}

void ChunkLoader::release()
{
    blockTextures.release();
    blockLightTextures.release();
    for (std::unordered_map<std::string, Chunk>::iterator i = chunks.begin(); i != chunks.end();)
    {
        i->second.release();
        i = chunks.erase(i);
    }
}