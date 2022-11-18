#include "raycast.h"

Shader Raycast::blockSelectionShader;
unsigned int Raycast::blockSelectionVAO;
unsigned int Raycast::blockSelectionEBO; 

void Raycast::init()
{
    blockSelectionShader.init("./Shaders/blockSelectionVertex.glsl", "./Shaders/blockSelectionFragment.glsl", true);
    glm::mat4 projectionMat = glm::mat4(1.0f);
    projectionMat = glm::perspective(glm::radians(70.0f), (float)INIT_WINDOW_WIDTH/(float)INIT_WINDOW_HEIGHT, 0.1f, 300.0f);
    glUseProgram(blockSelectionShader.getShaderProgram());
    glUniformMatrix4fv(blockSelectionShader.getProjectionMatUniformLocation(), 1, GL_FALSE, glm::value_ptr(projectionMat));

    float blockSelectionVerticies[24] = {
        -0.501,  0.501, -0.501, // A 0
         0.501,  0.501, -0.501, // B 1
         0.501,  0.501,  0.501, // C 2
        -0.501,  0.501,  0.501, // D 3
        -0.501, -0.501, -0.501, // E 4
         0.501, -0.501, -0.501, // F 5
         0.501, -0.501,  0.501, // G 6
        -0.501, -0.501,  0.501, // H 7
    };
    unsigned int blockSelectionIndicies[24] = {
        0, 1,
        1, 2,
        2, 3,
        3, 0,
        0, 4,
        1, 5,
        2, 6,
        3, 7,
        4, 5,
        5, 6,
        6, 7,
        7, 4
    };

    unsigned int blockSelectionVBO;
    glGenVertexArrays(1, &blockSelectionVAO);
    glGenBuffers(1, &blockSelectionVBO);
    glGenBuffers(1, &blockSelectionEBO);
    glBindVertexArray(blockSelectionVAO);

    glBindBuffer(GL_ARRAY_BUFFER, blockSelectionVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(blockSelectionVerticies), blockSelectionVerticies, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, blockSelectionEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(blockSelectionIndicies), blockSelectionIndicies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    glDeleteBuffers(1, &blockSelectionVBO);
}

void Raycast::drawBlockSelection()
{
    if (blockInRange)
    {    
        glm::mat4 modelMat = glm::mat4(1.0f);
        modelMat = glm::translate(modelMat, toGlmVec3(toVec3(selectedBlock) + Vec3(0.5, 0.5, 0.5)));

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

        glUseProgram(blockSelectionShader.getShaderProgram());
        glUniformMatrix4fv(blockSelectionShader.getModelMatUniformLocation(), 1, GL_FALSE, glm::value_ptr(modelMat));
        glUniformMatrix4fv(blockSelectionShader.getViewMatUniformLocation(), 1, GL_FALSE, glm::value_ptr(viewMat));

        glBindVertexArray(blockSelectionVAO);
        glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
    }
}



Pos Raycast::selectedBlock = {0, 0, 0};
Pos Raycast::blockPlacingPosition = {0, 0, 0};
float Raycast::raycastRange = 0;
bool Raycast::blockInRange = false;

void Raycast::setRange(float range)
{
    raycastRange = range;
}

bool Raycast::blockIsInRange()
{
    return blockInRange;
}

Pos Raycast::getSelectedBlock()
{
    return selectedBlock;
}

Pos Raycast::getBlockPlacingPosition()
{
    return blockPlacingPosition;
}

void Raycast::update()
{
    blockInRange = false;
    Vec3 cameraPos = playerPos + Vec3(0, 0.5, 0);

	Pos previousBlock = {(int)floor(cameraPos.x), (int)floor(cameraPos.y), (int)floor(cameraPos.z)};

	Vec3 currentPos = cameraPos;
	Vec3 dirSign = {0, 0, 0};
	if (lookDir.x > 0)
    {
		dirSign.x = 1;
    }
	else if (lookDir.x < 0)
    {
		dirSign.x = -1;	
    }
	if (lookDir.y > 0)
    {
		dirSign.y = 1;
    }
	else if (lookDir.y < 0)
    {
		dirSign.y = -1;	
    }
	if (lookDir.z > 0)
    {
		dirSign.z = 1;
    }
	else if (lookDir.z < 0)
    {
		dirSign.z = -1;	
    }

	int count = 0;
	while (distance(cameraPos, currentPos) <= raycastRange)
    {
		count += 1;
		Vec3 distanceToNextBlock = {-1, -1, -1};

		if (lookDir.x > 0)
        {
			distanceToNextBlock.x = ceil(currentPos.x) - currentPos.x + 0.001;
        }
		else if (lookDir.x < 0)
        {
			distanceToNextBlock.x = currentPos.x - floor(currentPos.x) + 0.001;
        }
		if (lookDir.y > 0)
        {
			distanceToNextBlock.y = ceil(currentPos.y) - currentPos.y + 0.001;
        }
		else if (lookDir.y < 0)
        {
			distanceToNextBlock.y = currentPos.y - floor(currentPos.y) + 0.001;
        }
		if (lookDir.z > 0)
        {
			distanceToNextBlock.z = ceil(currentPos.z) - currentPos.z + 0.001;
        }
		else if (lookDir.z < 0)
        {
			distanceToNextBlock.z = currentPos.z - floor(currentPos.z) + 0.001;
        }

		Vec3 distanceDivDir = {0, 0, 0};
		if (lookDir.x != 0)
        {
			distanceDivDir.x = abs(distanceToNextBlock.x / lookDir.x);
        }
		if (lookDir.y != 0)
        {
			distanceDivDir.y = abs(distanceToNextBlock.y / lookDir.y);
        }
		if (lookDir.z != 0)
        {
			distanceDivDir.z = abs(distanceToNextBlock.z / lookDir.z);
        }

		if (isMin(distanceDivDir.x, distanceDivDir.y, distanceDivDir.z))
        {
			currentPos.x += distanceToNextBlock.x * dirSign.x;
			if (lookDir.x != 0)
            {
				currentPos.y += distanceToNextBlock.x / abs(lookDir.x) * abs(lookDir.y) * dirSign.y;
				currentPos.z += distanceToNextBlock.x / abs(lookDir.x) * abs(lookDir.z) * dirSign.z;
            }
        }
		else if (isMin(distanceDivDir.y, distanceDivDir.x, distanceDivDir.z))
        {
			currentPos.y += distanceToNextBlock.y * dirSign.y;
			if (lookDir.y != 0)
            {
				currentPos.x += distanceToNextBlock.y / abs(lookDir.y) * abs(lookDir.x) * dirSign.x;
				currentPos.z += distanceToNextBlock.y / abs(lookDir.y) * abs(lookDir.z) * dirSign.z;
            }
        }
		else
        {
			currentPos.z += distanceToNextBlock.z * dirSign.z;
			if (lookDir.z != 0)
            {
				currentPos.x += distanceToNextBlock.z / abs(lookDir.z) * abs(lookDir.x) * dirSign.x;
				currentPos.y += distanceToNextBlock.z / abs(lookDir.z) * abs(lookDir.y) * dirSign.y;
            }
        }
		
		Pos currentBlock = {(int)floor(currentPos.x), (int)floor(currentPos.y), (int)floor(currentPos.z)};
		if (ChunkLoader::getBlock(currentBlock.x, currentBlock.y, currentBlock.z).blockType != AIR)
        {
			blockInRange = true;
			selectedBlock = currentBlock;
			blockPlacingPosition = previousBlock;
			break;
        }
		
		previousBlock = currentBlock;
    }
}

void Raycast::release()
{
    glDeleteVertexArrays(1, &blockSelectionVAO);
    glDeleteBuffers(1, &blockSelectionEBO);

    blockSelectionShader.release();
}