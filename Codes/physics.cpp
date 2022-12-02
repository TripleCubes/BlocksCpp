#include "physics.h"

Vec3 Physics::playerMoveVelocity(0, 0, 0);
Vec3 Physics::playerVelocity(0, 0, 0);

void Physics::slowDownVelocityReference(Vec3 &velocity, float velocitySlowDown)
{
    float directionaVelocity = sqrt(pow(velocity.x, 2) + pow(velocity.y, 2) + pow(velocity.z, 2));
	Vec3 axisVelocitySlowDown = {0, 0, 0};

	if (velocity.x != 0)
    {
		axisVelocitySlowDown.x = abs(velocity.x) / directionaVelocity * velocitySlowDown;
    }
	if (velocity.y != 0)
    {
		axisVelocitySlowDown.y = abs(velocity.y) / directionaVelocity * velocitySlowDown;
    }
	if (velocity.z != 0)
    {
		axisVelocitySlowDown.z = abs(velocity.z) / directionaVelocity * velocitySlowDown;
    }

	if (velocity.x > 0)
    {
		if (velocity.x - deltaTime * axisVelocitySlowDown.x > 0)
        {
			velocity.x -= deltaTime * axisVelocitySlowDown.x;
        }
		else
        {
			velocity.x = 0;
        }
    }
	else if (velocity.x < 0)
    {
		if (velocity.x + deltaTime * axisVelocitySlowDown.x < 0)
        {
			velocity.x += deltaTime * axisVelocitySlowDown.x;
        }
		else
        {
			velocity.x = 0;
        }
    }

	if (velocity.y > 0)
    {
		if (velocity.y - deltaTime * axisVelocitySlowDown.y > 0)
        {
			velocity.y -= deltaTime * axisVelocitySlowDown.y;
        }
		else
        {
			velocity.y = 0;
        }
    }
	else if (velocity.y < 0)
    {
		if (velocity.y + deltaTime * axisVelocitySlowDown.y < 0)
        {
			velocity.y += deltaTime * axisVelocitySlowDown.y;
        }
		else
        {
			velocity.y = 0;
        }
    }

	if (velocity.z > 0)
    {
		if (velocity.z - deltaTime * axisVelocitySlowDown.z > 0)
        {
			velocity.z -= deltaTime * axisVelocitySlowDown.z;
        }
		else
        {
			velocity.z = 0;
        }
    }
	else if (velocity.z < 0)
    {
		if (velocity.z + deltaTime * axisVelocitySlowDown.z < 0)
        {
			velocity.z += deltaTime * axisVelocitySlowDown.z;
        }
		else
        {
			velocity.z = 0;
        }
    }
}

void Physics::slowDownMoveVelocity(float velocitySlowDown)
{
    slowDownVelocityReference(playerMoveVelocity, velocitySlowDown);
}

void Physics::slowDownVelocity(float velocitySlowDown)
{
    slowDownVelocityReference(playerVelocity, velocitySlowDown);
}

Physics::Collision Physics::getCollision(Vec3 position)
{
	Physics::Collision collision;

	Pos startBlock = {
		(int)floor(position.x - PLAYER_WIDTH / 2),
		(int)floor(position.y - PLAYER_HEIGHT / 2),
		(int)floor(position.z - PLAYER_WIDTH / 2)
	};
	Pos endBlock = {
		(int)floor(position.x + PLAYER_WIDTH / 2 - 0.001),
		(int)floor(position.y + PLAYER_HEIGHT / 2 - 0.001),
		(int)floor(position.z + PLAYER_WIDTH / 2 - 0.001)
	};

	float minPush1 = 999999999;
	float minPush2 = 999999999;
	float maxColumnPush1 = 0;
	float maxColumnPush2 = 0;
	
	for (int x = startBlock.x; x <= endBlock.x; x++)
	{
		for (int z = startBlock.z; z <= endBlock.z; z++)
		{
			maxColumnPush1 = 0;
			maxColumnPush2 = 0;
			for (int y = startBlock.y; y <= endBlock.y; y++)
			{
				if (ChunkLoader::getBlock(x, y, z).blockType != AIR)
				{
					float push = (position.y + PLAYER_HEIGHT / 2) - y;
					if (push > maxColumnPush1)
					{
						maxColumnPush1 = push;
					}
					
					push = (y + 1) - (position.y - PLAYER_HEIGHT / 2);
					if (push > maxColumnPush2)
					{
						maxColumnPush2 = push;
					}
				}
			}
			if (maxColumnPush1 < minPush1 && maxColumnPush1 != 0)
			{
				minPush1 = maxColumnPush1;
			}
			if (maxColumnPush2 < minPush2 && maxColumnPush2 != 0)
			{
				minPush2 = maxColumnPush2;
			}
		}
	}
	if (minPush1 != 999999999)
	{
		collision.top = minPush1;
	}
	if (minPush2 != 999999999)
	{
		collision.bottom = minPush2;
	}

	minPush1 = 999999999;
	minPush2 = 999999999;
	for (int y = startBlock.y; y <= endBlock.y; y++)
	{
		for (int z = startBlock.z; z <= endBlock.z; z++)
		{
			maxColumnPush1 = 0;
			maxColumnPush2 = 0;
			for (int x = startBlock.x; x <= endBlock.x; x++)
			{
				if (ChunkLoader::getBlock(x, y, z).blockType != AIR)
				{
					float push = (x + 1) - (position.x - PLAYER_WIDTH / 2);
					if (push > maxColumnPush1)
					{
						maxColumnPush1 = push;
					}

					push = (position.x + PLAYER_WIDTH / 2) - x;
					if (push > maxColumnPush2)
					{
						maxColumnPush2 = push;
					}
				}
			}
			if (maxColumnPush1 < minPush1 && maxColumnPush1 != 0)
			{
				minPush1 = maxColumnPush1;
			}
			if (maxColumnPush2 < minPush2 && maxColumnPush2 != 0)
			{
				minPush2 = maxColumnPush2;
			}
		}
	}
	if (minPush1 != 999999999)
	{
		collision.left = minPush1;
	}
	if (minPush2 != 999999999)
	{
		collision.right = minPush2;
	}

	minPush1 = 999999999;
	minPush2 = 999999999;
	for (int x = startBlock.x; x <= endBlock.x; x++)
	{
		for (int y = startBlock.y; y <= endBlock.y; y++)
		{
			maxColumnPush1 = 0;
			maxColumnPush2 = 0;
			for (int z = startBlock.z; z <= endBlock.z; z++)
			{
				if (ChunkLoader::getBlock(x, y, z).blockType != AIR)
				{
					float push = (position.z + PLAYER_WIDTH / 2) - z;
					if (push > maxColumnPush1)
					{
						maxColumnPush1 = push;
					}

					push = (z + 1) - (position.z - PLAYER_WIDTH / 2);
					if (push > maxColumnPush2)
					{
						maxColumnPush2 = push;
					}
				}
			}
			if (maxColumnPush1 < minPush1 && maxColumnPush1 != 0)
			{
				minPush1 = maxColumnPush1;
			}
			if (maxColumnPush2 < minPush2 && maxColumnPush2 != 0)
			{
				minPush2 = maxColumnPush2;
			}
		}
	}
	if (minPush1 != 999999999)
	{
		collision.forward = minPush1;
	}
	if (minPush2 != 999999999)
	{
		collision.backward = minPush2;
	}
	
	if (collision.top > MAX_COLLISION_PUSH)
	{
		collision.top = 0;
	}
	if (collision.bottom > MAX_COLLISION_PUSH)
	{
		collision.bottom = 0;
	}
	if (collision.left > MAX_COLLISION_PUSH)
	{
		collision.left = 0;
	}
	if (collision.right > MAX_COLLISION_PUSH)
	{
		collision.right = 0;
	}
	if (collision.forward > MAX_COLLISION_PUSH)
	{
		collision.forward = 0;
	}
	if (collision.backward > MAX_COLLISION_PUSH)
	{
		collision.backward = 0;
	}

	return collision;
}

void Physics::push(Collision collision, PushAxis pushAxis, Vec3 velocity)
{
	if (pushAxis == PUSH_X)
	{
		if (velocity.x > 0)
		{
			playerPos.x -= collision.right;
		}
		else if (velocity.x < 0)
		{
			playerPos.x += collision.left;
		}
	}
	else if (pushAxis == PUSH_Y)
	{
		if (velocity.y > 0)
		{
			playerPos.y -= collision.top;
		}
		else if (velocity.y < 0)
		{
			playerPos.y += collision.bottom;
		}
	}
	else if (pushAxis == PUSH_Z)
	{
		if (velocity.z > 0)
		{
			playerPos.z -= collision.forward;
		}
		else if (velocity.z < 0)
		{
			playerPos.z += collision.backward;
		}
	}
}

float Physics::getPush(Collision collision, PushAxis pushAxis, Vec3 velocity)
{
	if (pushAxis == PUSH_X)
	{
		if (velocity.x > 0)
		{
			return collision.right;
		}
		else if (velocity.x < 0)
		{
			return collision.left;
		}
	}
	else if (pushAxis == PUSH_Y)
	{
		if (velocity.y > 0)
		{
			return collision.top;
		}
		else if (velocity.y < 0)
		{
			return collision.bottom;
		}
	}
	else if (pushAxis == PUSH_Z)
	{
		if (velocity.z > 0)
		{
			return collision.forward;
		}
		else if (velocity.z < 0)
		{
			return collision.backward;
		}
	}
	return 0;
}

bool Physics::willCollideAfterUnpush(Collision collision, PushAxis pushAxis, Vec3 velocity)
{
	if (collision.top != 0 || collision.bottom != 0 || collision.left != 0
	or collision.right != 0 || collision.forward != 0 || collision.backward != 0)
	{
		Vec3 unpushPosition = {
			playerPos.x,
			playerPos.y,
			playerPos.z
		};

		if (pushAxis == PUSH_X)
		{
			if (velocity.x > 0)
				unpushPosition.x += collision.right;
			else if (velocity.x < 0)
				unpushPosition.x -= collision.left;
		}
		else if (pushAxis == PUSH_Y)
		{
			if (velocity.y > 0)
				unpushPosition.y += collision.top;
			else if (velocity.y < 0)
				unpushPosition.y -= collision.bottom;
		}
		else if (pushAxis == PUSH_Z)
		{
			if (velocity.z > 0)
				unpushPosition.z += collision.forward;
			else if (velocity.z < 0)
				unpushPosition.z -= collision.backward;
		}

		Physics::Collision unpushCollision = getCollision(unpushPosition);
		if (unpushCollision.top != 0 || unpushCollision.bottom != 0 || unpushCollision.left != 0
		or unpushCollision.right != 0 || unpushCollision.forward != 0 || unpushCollision.backward != 0)
		{
			return true;
		}
	}
	return false;
}

void Physics::unpush(Collision collision, PushAxis pushAxis, Vec3 velocity)
{
	if (pushAxis == PUSH_X)
	{
		if (velocity.x > 0)
		{
			playerPos.x += collision.right;
		}
		else if (velocity.x < 0)
		{
			playerPos.x -= collision.left;
		}
	}
	else if (pushAxis == PUSH_Y)
	{
		if (velocity.y > 0)
		{
			playerPos.y += collision.top;
		}
		else if (velocity.y < 0)
		{
			playerPos.y -= collision.bottom;
		}
	}
	else if (pushAxis == PUSH_Z)
	{
		if (velocity.z > 0)
		{
			playerPos.z += collision.forward;
		}
		else if (velocity.z < 0)
		{
			playerPos.z -= collision.backward;
		}
	}
}

void Physics::addMoveVelocity(float x, float y, float z, float cap)
{
    playerMoveVelocity.x += x;
    playerMoveVelocity.y += y;
    playerMoveVelocity.z += z;

    float directionalVelocity = sqrt(pow(playerMoveVelocity.x, 2) + pow(playerMoveVelocity.y, 2) + pow(playerMoveVelocity.z, 2));
    if (directionalVelocity > cap)
    {
        playerMoveVelocity.x = cap / directionalVelocity * playerMoveVelocity.x;
		playerMoveVelocity.y = cap / directionalVelocity * playerMoveVelocity.y;
		playerMoveVelocity.z = cap / directionalVelocity * playerMoveVelocity.z;
    }
}

void Physics::addVelocity(float x, float y, float z, float cap)
{
    playerVelocity.x += x;
    playerVelocity.y += y;
    playerVelocity.z += z;

    float directionalVelocity = sqrt(pow(playerVelocity.x, 2) + pow(playerVelocity.y, 2) + pow(playerVelocity.z, 2));
    if (directionalVelocity > cap)
    {
        playerVelocity.x = cap / directionalVelocity * playerVelocity.x;
		playerVelocity.y = cap / directionalVelocity * playerVelocity.y;
		playerVelocity.z = cap / directionalVelocity * playerVelocity.z;
    }
}

bool Physics::isColliding(Dir dir)
{
	if (dir == TOP)
	{
		Vec3 position = playerPos;
		position.y += 0.001;

		Collision collision = getCollision(position);
		if (collision.top > 0)
		{
			return true;
		}
	}
	else if (dir == BOTTOM)
	{
		Vec3 position = playerPos;
		position.y -= 0.001;

		Collision collision = getCollision(position);
		if (collision.bottom > 0)
		{
			return true;
		}
	}
	else if (dir == LEFT)
	{
		Vec3 position = playerPos;
		position.x -= 0.001;

		Collision collision = getCollision(position);
		if (collision.left > 0)
		{
			return true;
		}
	}
	else if (dir == RIGHT)
	{
		Vec3 position = playerPos;
		position.x += 0.001;

		Collision collision = getCollision(position);
		if (collision.right > 0)
		{
			return true;
		}
	}
	else if (dir == FORWARD)
	{
		Vec3 position = playerPos;
		position.z += 0.001;

		Collision collision = getCollision(position);
		if (collision.forward > 0)
		{
			return true;
		}
	}
	else if (dir == BACKWARD)
	{
		Vec3 position = playerPos;
		position.z -= 0.001;

		Collision collision = getCollision(position);
		if (collision.backward > 0)
		{
			return true;
		}
	}

	return false;
}

void Physics::move()
{
    Vec3 playerCombinedVelocity = {
		playerVelocity.x + playerMoveVelocity.x,
		playerVelocity.y + playerMoveVelocity.y,
		playerVelocity.z + playerMoveVelocity.z
	};
	playerCombinedVelocity = playerCombinedVelocity / VELOCITY_DIVIDE;

	for (int i = 0; i < VELOCITY_DIVIDE; i++)
	{

		playerPos.x += playerCombinedVelocity.x * deltaTime;
		playerPos.y += playerCombinedVelocity.y * deltaTime;
		playerPos.z += playerCombinedVelocity.z * deltaTime;

		if (physics)
		{
			Vec3 position = {
				playerPos.x,
				playerPos.y,
				playerPos.z
			};
			Collision collision = getCollision(position);

			bool preserveVelocityX = true;
			bool preserveVelocityY = true;
			bool preserveVelocityZ = true;

			if (getPush(collision, PUSH_Y, playerCombinedVelocity) > 0)
			{
				preserveVelocityY = false;
			}
			if (getPush(collision, PUSH_X, playerCombinedVelocity) > 0)
			{
				preserveVelocityX = false;
			}
			if (getPush(collision, PUSH_Z, playerCombinedVelocity) > 0)
			{
				preserveVelocityZ = false;
			}

			push(collision, PUSH_X, playerCombinedVelocity);
			push(collision, PUSH_Y, playerCombinedVelocity);
			push(collision, PUSH_Z, playerCombinedVelocity);

			for (int i = 0; i < 3; i++)
			{
				if (isMax(getPush(collision, PUSH_X, playerCombinedVelocity), getPush(collision, PUSH_Y, playerCombinedVelocity), getPush(collision, PUSH_Z, playerCombinedVelocity)))
				{
					if (!willCollideAfterUnpush(collision, PUSH_X, playerCombinedVelocity))
					{
						unpush(collision, PUSH_X, playerCombinedVelocity);
						preserveVelocityX = true;
					}
					collision.left = 0;
					collision.right = 0;
				}
				else if (isMax(getPush(collision, PUSH_Y, playerCombinedVelocity), getPush(collision, PUSH_X, playerCombinedVelocity), getPush(collision, PUSH_Z, playerCombinedVelocity)))
				{
					if (!willCollideAfterUnpush(collision, PUSH_Y, playerCombinedVelocity))
					{
						unpush(collision, PUSH_Y, playerCombinedVelocity);
						preserveVelocityY = true;
					}
					collision.top = 0;
					collision.bottom = 0;
				}
				else
				{
					if (!willCollideAfterUnpush(collision, PUSH_Z, playerCombinedVelocity))
					{
						unpush(collision, PUSH_Z, playerCombinedVelocity);
						preserveVelocityZ = true;
					}
					collision.forward = 0;
					collision.backward = 0;
				}
			}
			
			if (!preserveVelocityX)
			{
				playerMoveVelocity.x = 0;
				playerVelocity.x = 0;
			}
			if (!preserveVelocityY)
			{
				playerMoveVelocity.y = 0;
				playerVelocity.y = 0;
			}
			if (!preserveVelocityZ)
			{
				playerMoveVelocity.z = 0;
				playerVelocity.z = 0;
			}
		}
	}

    slowDownMoveVelocity(MOVE_VELOCITY_SLOWDOWN);
    slowDownVelocity(VELOCITY_SLOWDOWN);
}