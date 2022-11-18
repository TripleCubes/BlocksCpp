#ifndef PHYSICS_H
#define PHYSICS_H

#include "vectormath.h"
#include "player.h"
#include "time.h"
#include "globals.h"
#include "chunkLoader.h"

const float MOVE_VELOCITY_SLOWDOWN = 60;
const float MOVE_VELOCITY_ADD = 100;
const float MOVE_SPEED_CAP = 15;

const float VELOCITY_SLOWDOWN = 7;
const float GRAVITY_ADD = 50;
const float VELOCITY_CAP = 100;
const float JUMP_VELOCITY = 15;

const float MAX_COLLISION_PUSH = 0.9;

const float VELOCITY_DIVIDE = 4;

class Physics
{
    private:
        static Vec3 playerMoveVelocity;
        static Vec3 playerVelocity;
        
        enum PushAxis {
            PUSH_X,
            PUSH_Y,
            PUSH_Z
        };

        struct Collision {
            float top = 0;
            float bottom = 0;
            float left = 0;
            float right = 0;
            float forward = 0;
            float backward = 0;
        };

        static void slowDownVelocityReference(Vec3 &velocity, float velocitySlowDown);
        static void slowDownMoveVelocity(float velocitySlowDown);
        static void slowDownVelocity(float velocitySlowDown);
        static Collision getCollision(Vec3 position);
        static void push(Collision collision, PushAxis pushAxis, Vec3 velocity);
        static float getPush(Collision collision, PushAxis pushAxis, Vec3 velocity);
        static bool willCollideAfterUnpush(Collision collision, PushAxis pushAxis, Vec3 velocity);
        static void unpush(Collision collision, PushAxis pushAxis, Vec3 velocity);

    public:
        static void addMoveVelocity(float x, float y, float z, float cap);
        static void addVelocity(float x, float y, float z, float cap);
        static bool isColliding(Dir dir);
        static void move();
};

#endif