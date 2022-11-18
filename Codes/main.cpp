#include <iostream>
#include <chrono>
#include <thread>
#include "shaders.h"
#include "vectormath.h"
#include "chunkLoader.h"
#include "player.h"
#include "time.h"
#include "physics.h"
#include "globals.h"
#include "ui.h"
#include "raycast.h"

GLFWwindow* window = NULL;

float cameraRotationX = 0;
float cameraRotationY = 0;

float lastMousePosX = INIT_WINDOW_WIDTH / 2;
float lastMousePosY = INIT_WINDOW_HEIGHT / 2;
bool mouseInWindow = false;

Vec3 skyLightDir = {0.1, -1, 0.2};

bool F5Pressed = false;
bool MPressed = false;
bool FPressed = false;
bool ESCPressed = false;
bool leftMousePressed = false;
bool rightMousePressed = false;
bool LPressed = false;
bool BPressed = false;
bool YPressed = false;
bool RPressed = false;
bool GPressed = false;

void onMouseMove(GLFWwindow* window, double mousex, double mousey)
{
    float offsetx = mousex - lastMousePosX;
    float offsety = mousey - lastMousePosY;
    lastMousePosX = mousex;
    lastMousePosY = mousey;

    if (mouseInWindow)
    {
        cameraRotationX -= offsety * 0.002;
        if (glm::degrees(cameraRotationX) > 89.99)
        {
            cameraRotationX = glm::radians(89.99f);
        }
        else if (glm::degrees(cameraRotationX) < -89.99)
        {
            cameraRotationX = glm::radians(-89.99f);
        }
        cameraRotationY -= offsetx * 0.002;

        Vec3 lookDir = Vec3(0, 0, -1);
        lookDir.rotateX(cameraRotationX);
        lookDir.rotateY(cameraRotationY);
        ::lookDir = lookDir;

        Vec3 playerFrontDir = Vec3(0, 0, -1);
        playerFrontDir.rotateY(cameraRotationY);
        ::playerFrontDir = playerFrontDir;
    }
    else
    {
        mouseInWindow = true;
    }
}

void onWindowResize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    currentWindowWidth = width;
    currentWindowHeight = height;
}

void GLinit()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT, "Blocks", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, onWindowResize);
    glfwSetCursorPosCallback(window, onMouseMove);
    glfwSetWindowPos(window, INIT_WINDOW_POS_X, INIT_WINDOW_POS_Y);
    glfwShowWindow(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    defaultShader.init("./Shaders/defaultVertex.glsl", "./Shaders/defaultFragment.glsl", true);
}

int main()
{
    using namespace std::chrono;
    using namespace std::this_thread;

    srand(time(0));
    
    GLinit();

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE); 
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 

    glm::mat4 projectionMat = glm::mat4(1.0f);
    projectionMat = glm::perspective(glm::radians(70.0f), (float)INIT_WINDOW_WIDTH/(float)INIT_WINDOW_HEIGHT, 0.1f, 300.0f);

    int skyLightDirUniform = glGetUniformLocation(defaultShader.getShaderProgram(), "skyLightDir");
    int fragmentColorUniform = glGetUniformLocation(defaultShader.getShaderProgram(), "fragmentColor");
    glUseProgram(defaultShader.getShaderProgram());

    glUniformMatrix4fv(defaultShader.getProjectionMatUniformLocation(), 1, GL_FALSE, glm::value_ptr(projectionMat));
    glUniform3f(skyLightDirUniform, skyLightDir.x, skyLightDir.y, skyLightDir.z);
    glUniform3f(fragmentColorUniform, 1.0f, 0.97f, 0.8f);

    previousTime = glfwGetTime();

    Player::init();
    ChunkLoader::init();
    UI::init();
    Raycast::init();
    Raycast::setRange(5);

    int numberOfLights = 0;

    while (!glfwWindowShouldClose(window))
    {
        float frameStartTime = glfwGetTime();

        Vec3 playerLeftDir = cross(Vec3(0, 1, 0), playerFrontDir);
        Vec3 playerUpDir = cross(playerFrontDir, playerLeftDir);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            Physics::addMoveVelocity(MOVE_VELOCITY_ADD * playerFrontDir.x * deltaTime, 0, MOVE_VELOCITY_ADD * playerFrontDir.z * deltaTime, MOVE_SPEED_CAP);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            Physics::addMoveVelocity(MOVE_VELOCITY_ADD * playerLeftDir.x * deltaTime, 0, MOVE_VELOCITY_ADD * playerLeftDir.z * deltaTime, MOVE_SPEED_CAP);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            Physics::addMoveVelocity(MOVE_VELOCITY_ADD * -playerFrontDir.x * deltaTime, 0, MOVE_VELOCITY_ADD * -playerFrontDir.z * deltaTime, MOVE_SPEED_CAP);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            Physics::addMoveVelocity(MOVE_VELOCITY_ADD * -playerLeftDir.x * deltaTime, 0, MOVE_VELOCITY_ADD * -playerLeftDir.z * deltaTime, MOVE_SPEED_CAP);
        }
        if (flying)
        {
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            {
                Physics::addMoveVelocity(0, MOVE_VELOCITY_ADD * deltaTime, 0, MOVE_SPEED_CAP);
            }
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            {
                Physics::addMoveVelocity(0, -MOVE_VELOCITY_ADD * deltaTime, 0, MOVE_SPEED_CAP);
            }
        }
        else
        {
            Physics::addVelocity(0, -GRAVITY_ADD * deltaTime, 0, VELOCITY_CAP);
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && Physics::isColliding(BOTTOM))
            {
                Physics::addVelocity(0, JUMP_VELOCITY, 0, VELOCITY_CAP);
            }
        }

        if (glfwGetKey(window, GLFW_KEY_F5) == GLFW_PRESS)
        {
            if (!F5Pressed)
            {
                thirdPersonView = !thirdPersonView;
            }
            F5Pressed = true;
        }
        else
        {
            F5Pressed = false;
        }
        
        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        {
            if (!MPressed)
            {
                wireframeMode = !wireframeMode;
                if (wireframeMode)
                {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                }
                else
                {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                }
            }
            MPressed = true;
        }
        else
        {
            MPressed = false;
        }

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            if (!ESCPressed)
            {
                mouseLock = !mouseLock;
                if (mouseLock)
                {
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
                }
                else
                {
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); 
                }
            }
            ESCPressed = true;
        }
        else
        {
            ESCPressed = false;
        }

        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        {
            if (!FPressed)
            {
                flying = !flying;
            }
            FPressed = true;
        }
        else
        {
            FPressed = false;
        }

        Physics::move();
        Raycast::update();

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            if (!leftMousePressed)
            {
                if (Raycast::blockIsInRange())
                {
                    Pos selectedBlock = Raycast::getSelectedBlock();
                    ChunkLoader::breakBlock(selectedBlock.x, selectedBlock.y, selectedBlock.z);
                }
            }
            leftMousePressed = true;
        }
        else
        {
            leftMousePressed = false;
        }

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
            if (!rightMousePressed)
            {
                if (Raycast::blockIsInRange())
                {
                    Pos blockPlacingPosition = Raycast::getBlockPlacingPosition();
                    ChunkLoader::placeBlock(blockPlacingPosition.x, blockPlacingPosition.y, blockPlacingPosition.z, BLOCK);
                }
            }
            rightMousePressed = true;
        }
        else
        {
            rightMousePressed = false;
        }

        if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        {
            if (!YPressed)
            {
                if (Raycast::blockIsInRange())
                {
                    Pos blockPlacingPosition = Raycast::getBlockPlacingPosition();
                    ChunkLoader::placeBlock(blockPlacingPosition.x, blockPlacingPosition.y, blockPlacingPosition.z, YELLOW_LIGHT);
                }
            }
            YPressed = true;
        }
        else
        {
            YPressed = false;
        }

        if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
        {
            if (!BPressed)
            {
                if (Raycast::blockIsInRange())
                {
                    Pos blockPlacingPosition = Raycast::getBlockPlacingPosition();
                    ChunkLoader::placeBlock(blockPlacingPosition.x, blockPlacingPosition.y, blockPlacingPosition.z, BLUE_LIGHT);
                }
            }
            BPressed = true;
        }
        else
        {
            BPressed = false;
        }

        if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        {
            if (!GPressed)
            {
                if (Raycast::blockIsInRange())
                {
                    Pos blockPlacingPosition = Raycast::getBlockPlacingPosition();
                    ChunkLoader::placeBlock(blockPlacingPosition.x, blockPlacingPosition.y, blockPlacingPosition.z, GREEN_LIGHT);
                }
            }
            GPressed = true;
        }
        else
        {
            GPressed = false;
        }

        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        {
            if (!RPressed)
            {
                if (Raycast::blockIsInRange())
                {
                    Pos blockPlacingPosition = Raycast::getBlockPlacingPosition();
                    ChunkLoader::placeBlock(blockPlacingPosition.x, blockPlacingPosition.y, blockPlacingPosition.z, RED_LIGHT);
                }
            }
            RPressed = true;
        }
        else
        {
            RPressed = false;
        }

        glm::mat4 viewMat = glm::mat4(1.0f);
        if (!thirdPersonView)
        {
            viewMat = glm::lookAt(toGlmVec3(playerPos + Vec3(0, 0.5, 0)),
                                toGlmVec3(playerPos + Vec3(0, 0.5, 0) + lookDir),
                                glm::vec3(0.0f, 1.0f, 0.0f));
        }
        else
        {
            viewMat = glm::lookAt(toGlmVec3(playerPos + Vec3(0, 0.5, 0) - (lookDir * 20)),
                                toGlmVec3(playerPos + Vec3(0, 0.5, 0)),
                                glm::vec3(0.0f, 1.0f, 0.0f));
        }
                            
        glClearColor(0.31f, 0.31f, 0.32f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(defaultShader.getShaderProgram());
        glUniformMatrix4fv(defaultShader.getViewMatUniformLocation(), 1, GL_FALSE, glm::value_ptr(viewMat));

        ChunkLoader::loadChunksAround(playerPos.x, playerPos.y, playerPos.z, 4);
        ChunkLoader::unloadChunksFarFrom(playerPos.x, playerPos.y, playerPos.z, 4);
        ChunkLoader::draw();
        Player::draw();
        if (!thirdPersonView)
        {
            UI::drawCrosshair();
        }
        Raycast::drawBlockSelection();
 
        glfwSwapBuffers(window);
        glfwPollEvents();

        float frameTime = glfwGetTime() - frameStartTime;
        sleep_for(milliseconds((int)round((1/FPS_CAP - frameTime)* 1000)));

        deltaTime = glfwGetTime() - previousTime;
        previousTime = glfwGetTime();
    }

    Player::release();
    ChunkLoader::release();
    UI::release();
    Raycast::release();

    defaultShader.release();
    glfwTerminate();

    return 0;
}