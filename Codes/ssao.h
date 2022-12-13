#ifndef SSAO_H
#define SSAO_H

#include <array>
#include <random>
#include <string>

#include "frameBuffers.h"
#include "shaders.h"
#include "gbuffer.h"
#include "vectormath.h"

class SSAO
{
    private:
        static FrameBuffer unblurredAOFrameBuffer;
        static FrameBuffer horizontalBlurredAOFrameBuffer;
        static FrameBuffer verticalBlurredAOFrameBuffer;
        static Shader ssaoShader;
        static Shader blurShader;
        static unsigned int screenVAO;

        static std::array<Vec3, 20> randomPoints; 
        static std::array<Vec3, 16> randomDirs;

        static std::random_device randomDevice;
        static std::mt19937 randomNumberGenerator;
        static std::uniform_real_distribution<> randomDistribution;

    public:
        static void init();
        static void generateSSAOTexture();
        static unsigned int getSSAOTexture();
        static void release();
};

#endif