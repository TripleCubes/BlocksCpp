#ifndef CHUNKLOADER_H
#define CHUNKLOADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <FastNoiseLite.h>

#include <vector>
#include <array>
#include <stdlib.h>
#include <time.h>
#include <unordered_map>
#include <string>
#include <thread>
#include <mutex>

#include "shaders.h"
#include "globals.h"
#include "textures.h"
#include "vectormath.h"
#include "player.h"
#include "gbuffer.h"

const int CHUNK_SIZE = 16;
const int MAX_NUMBER_OF_LIGHTS = 20;
const int RENDER_DISTANCE = 6;

static std::mutex chunkLoadMutex;

enum BlockType
{
    AIR,
    BLOCK,
    BLUE_LIGHT,
    YELLOW_LIGHT,
    GREEN_LIGHT,
    RED_LIGHT
};

enum BlockTexturePos
{
    DEFAULT_BLOCK_X = 0,
    DEFAULT_BLOCK_Y = 0,
    BLUE_LIGHT_BLOCK_X = 1,
    BLUE_LIGHT_BLOCK_Y = 0,
    YELLOW_LIGHT_BLOCK_X = 2,
    YELLOW_LIGHT_BLOCK_Y = 0,
    GREEN_LIGHT_BLOCK_X = 3,
    GREEN_LIGHT_BLOCK_Y = 0,
    RED_LIGHT_BLOCK_X = 4,
    RED_LIGHT_BLOCK_Y = 0
};

enum BlockLightColor
{
    BLUE_LIGHT_BLOCK_LIGHT_COLOR_R = 142,
    BLUE_LIGHT_BLOCK_LIGHT_COLOR_G = 232,
    BLUE_LIGHT_BLOCK_LIGHT_COLOR_B = 255,

    YELLOW_LIGHT_BLOCK_LIGHT_COLOR_R = 255,
    YELLOW_LIGHT_BLOCK_LIGHT_COLOR_G = 237,
    YELLOW_LIGHT_BLOCK_LIGHT_COLOR_B = 140,

    GREEN_LIGHT_BLOCK_LIGHT_COLOR_R = 150,
    GREEN_LIGHT_BLOCK_LIGHT_COLOR_G = 255,
    GREEN_LIGHT_BLOCK_LIGHT_COLOR_B = 142,

    RED_LIGHT_BLOCK_LIGHT_COLOR_R = 255,
    RED_LIGHT_BLOCK_LIGHT_COLOR_G = 99,
    RED_LIGHT_BLOCK_LIGHT_COLOR_B = 94,
};

struct Block
{
    BlockType blockType = AIR;
};

struct Light
{
    Vec3 pos;
    Vec3 color;
};

enum ChunkLoadStatus
{
    NOT_LOADED,
    LOADED,
    LOADING
};

class Chunk
{
    private:
        std::array<std::array<std::array<Block, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> blocks;
        std::vector<float> surfaces;
        Pos chunkCoord;

        unsigned int VAO;
        bool VAOgenerated = false;

        ChunkLoadStatus chunkLoadStatus = LOADING;
        bool VAOReloadRequest = false;
        bool reloadingSurfaces = false;

        void addBlockSurface(float x, float y, float z, Dir dir, BlockTexturePos blockTexturePosX, BlockTexturePos blockTexturePosY);

        struct NearbyBlocks 
        {
            bool top = false;
            bool bottom = false;
            bool left = false;
            bool right = false;
            bool forward = false;
            bool backward = false;
        };
        void addBlock(int x, int y, int z, NearbyBlocks nearbyBlocks, BlockTexturePos blockTextureCoordX, BlockTexturePos blockTextureCoordY);
        
    public:
        void init(int x, int y, int z);
        void load();

        void reloadSurfaces();
        void draw();
        void drawGBuffer();
        Pos getCoord();
        Block getBlock(int x, int y, int z);
        std::array<std::array<std::array<Block, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> getChunkBlocks();
        void placeBlock(int x, int y, int z, BlockType blockType);
        void breakBlock(int x, int y, int z);
        ChunkLoadStatus getChunkLoadStatus();
        void setChunkLoadStatus(ChunkLoadStatus status);
        bool VAOReloadRequested();
        void reloadVAO();
        bool isReloadingSurfaces();

        void release();
};

class ChunkLoader
{
    private:
        static std::unordered_map<std::string, Chunk> chunks;

        static FastNoiseLite terrainHeightNoise;
        static FastNoiseLite terrainHeightNoise2;
        static FastNoiseLite terrainNoise3d;
        static FastNoiseLite cheeseCaveNoise;
        static FastNoiseLite noodleCaveNoise1;
        static FastNoiseLite noodleCaveNoise2;

        static void loadChunk(int x, int y, int z);
        static std::unordered_map<std::string, Chunk>::iterator unloadChunk(int x, int y, int z);

        static Texture blockTextures;
        static Texture blockLightTextures;

        static std::vector<Light> lights;

        static std::thread chunkLoadThread;
        static bool chunkLoadThreadStopped;
        static void chunkLoadThreadFunction();

    public:
        static void init();
        static void draw();
        static void drawGBuffer();
        static void update();

        static float getTerrainHeight1(int x, int z);
        static float convertTerrainHeight1(float normalizedTerrainHeight);
        static float getTerrainHeight2(int x, int z);
        static float convertToBlockHeight(float terrainHeight);
        static float getTerrainAlphaValue(int x, int y, int z);
        static float getCheeseCaveAlphaValue(int x, int y, int z);
        static float getNoodleCaveAlphaValue1(int x, int y, int z);
        static float getNoodleCaveAlphaValue2(int x, int y, int z);

        static std::string convertToKey(int x, int y, int z);
        static void loadChunksAround(float x, float y, float z, int renderDistance);
        static void unloadChunksFarFrom(float x, float y, float z, int renderDistance);

        static bool chunkLoaded(int x, int y, int z);
        static bool chunkLoaded(std::string key);
        static bool chunkLoading(int x, int y, int z);
        static bool chunkLoading(std::string key);
        static ChunkLoadStatus getChunkLoadStatus(int x, int y, int z);
        static ChunkLoadStatus getChunkLoadStatus(std::string key);

        static bool getChunkBlocks(int x, int y, int z, std::array<std::array<std::array<Block, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> &blocks);
        static Block getBlock(int x, int y, int z);
        static void placeBlock(int x, int y, int z, BlockType blockType);
        static void breakBlock(int x, int y, int z);
        static Texture getBlockTextures();
        static Texture getBlockLightTextures();

        static void stopChunkLoadThread();
        static void waitAsyncsToFinish();

        static void release();
};

#endif