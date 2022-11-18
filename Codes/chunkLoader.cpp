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
        for (int z = 0; z < CHUNK_SIZE; z++)
        {
            blocks[x][ChunkLoader::getNoise(chunkCoord.x*CHUNK_SIZE + x, chunkCoord.z*CHUNK_SIZE + z)][z].blockType = BLOCK;
        }
    }
}

void Chunk::reloadSurfaces()
{
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



std::unordered_map<std::string, Chunk> ChunkLoader::chunks;
FastNoiseLite ChunkLoader::noise;

Texture ChunkLoader::blockTextures;
Texture ChunkLoader::blockLightTextures;

std::vector<Light> ChunkLoader::lights;

void ChunkLoader::loadChunk(int x, int y, int z)
{
    if (!chunkLoaded(x, y, z))
    {
        Chunk chunk;
        chunk.init(x, y, z);
        chunk.load();
        chunk.reloadSurfaces();

        chunks.insert(std::make_pair(convertToKey(x, y, z), chunk));

        if (chunkLoaded(x, y + 1, z))
        {
            chunks[convertToKey(x, y + 1, z)].reloadSurfaces();
        }
        if (chunkLoaded(x, y - 1, z))
        {
            chunks[convertToKey(x, y - 1, z)].reloadSurfaces();
        }
        if (chunkLoaded(x - 1, y, z))
        {
            chunks[convertToKey(x - 1, y, z)].reloadSurfaces();
        }
        if (chunkLoaded(x + 1, y, z))
        {
            chunks[convertToKey(x + 1, y, z)].reloadSurfaces();
        }
        if (chunkLoaded(x, y, z + 1))
        {
            chunks[convertToKey(x, y, z + 1)].reloadSurfaces();
        }
        if (chunkLoaded(x, y, z - 1))
        {
            chunks[convertToKey(x, y, z - 1)].reloadSurfaces();
        }
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
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetSeed(rand());
    noise.SetFractalOctaves(3);
    // noise.SetFrequency();

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

int ChunkLoader::getNoise(int x, int z)
{
    return (int)round((noise.GetNoise((float)x, (float)z)+1) / 2 * (CHUNK_SIZE-1));
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
    return chunks.find(key) != chunks.end();
}

bool ChunkLoader::chunkLoaded(std::string key)
{
    return chunks.find(key) != chunks.end();
}

void ChunkLoader::loadChunksAround(float x, float y, float z, int renderDistance)
{
    int chunkX = floor(x / CHUNK_SIZE);
    int chunkY = floor(y / CHUNK_SIZE);
    int chunkZ = floor(z / CHUNK_SIZE);

    for (int x = chunkX - renderDistance; x <= chunkX + renderDistance; x++)
    {
        for (int z = chunkZ - renderDistance; z <= chunkZ + renderDistance; z++)
        {
            loadChunk(x, 0, z);
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
        if (abs(chunkCoord.x - chunkX) > renderDistance || abs(chunkCoord.z - chunkZ) > renderDistance)
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
        lights.push_back({Vec3(x + 0.5, y + 0.5, z + 0.5), Vec3((float)BLUE_LIGHT_BLOCK_LIGHT_COLOR_R / 256, 
                                                                (float)BLUE_LIGHT_BLOCK_LIGHT_COLOR_G / 256, 
                                                                (float)BLUE_LIGHT_BLOCK_LIGHT_COLOR_B / 256)});
    }
    if (blockType == YELLOW_LIGHT)
    {
        lights.push_back({Vec3(x + 0.5, y + 0.5, z + 0.5), Vec3((float)YELLOW_LIGHT_BLOCK_LIGHT_COLOR_R / 256, 
                                                                (float)YELLOW_LIGHT_BLOCK_LIGHT_COLOR_G / 256, 
                                                                (float)YELLOW_LIGHT_BLOCK_LIGHT_COLOR_B / 256)});
    }
    if (blockType == GREEN_LIGHT)
    {
        lights.push_back({Vec3(x + 0.5, y + 0.5, z + 0.5), Vec3((float)GREEN_LIGHT_BLOCK_LIGHT_COLOR_R / 256, 
                                                                (float)GREEN_LIGHT_BLOCK_LIGHT_COLOR_G / 256, 
                                                                (float)GREEN_LIGHT_BLOCK_LIGHT_COLOR_B / 256)});
    }
    if (blockType == RED_LIGHT)
    {
        lights.push_back({Vec3(x + 0.5, y + 0.5, z + 0.5), Vec3((float)RED_LIGHT_BLOCK_LIGHT_COLOR_R / 256, 
                                                                (float)RED_LIGHT_BLOCK_LIGHT_COLOR_G / 256, 
                                                                (float)RED_LIGHT_BLOCK_LIGHT_COLOR_B / 256)});
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