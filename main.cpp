// Steps of general use of OpenGL
// Create vars and load data into RAM
// Create a var to hold the ID
// Pass the var address to glGen... to get the ID
// Bind the ID to a target (Target Ex: GL_ARRAY_BUFFER, GL_TEXTURE_2D)
// Upload data to the GPU through that target, since the target is connected to the object via the previous step, it is like you're uploading data to the object that you created

#define STB_IMAGE_IMPLEMENTATION
#define MINIAUDIO_IMPLEMENTATION
#include <iostream>
#include <vector>
#include <random>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Headers/miniaudio.h"
#include "Headers/WindowHandler.h"
#include "Headers/ShaderHandler.h"
#include "Headers/MeshHandler.h"
#include "Headers/TextureHandler.h"
#include "Headers/ControlsHandler.h"
#include "Headers/ItemsHandler.h"
#include "Headers/StructHandler.h"

int joystickID = -1;

int main()
{
    GLFWwindow* mainWindow = createCenteredWindow();
    if(!mainWindow) return -1;

    // Turns on blending with BG for transparent pixelss
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 

    std::vector<Enemy> enemies;
    std::vector<Bullet> shipBullets;
    std::vector<Bullet> enemyBullets;
    std::vector<FallingObject> fallingObjects;
    std::vector<FallingObject> activeFallingObjects;

    float shipVerticies [] =
    {
        0.08f, 0.08f, 1.0f, 1.0f,
        0.08f, -0.08f, 1.0f, 0.0f,
        -0.08f, -0.08f, 0.0f, 0.0f,
        -0.08f, -0.08f, 0.0f, 0.0f,
        -0.08f, 0.08f, 0.0f, 1.0f,
        0.08f, 0.08f, 1.0f, 1.0f
    };
    float backgroundVerticies [] =
    {
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
    };
    float bulletVerticies [] =
    {
        0.04f, 0.04f, 1.0f, 1.0f,
        0.04f, -0.04f, 1.0f, 0.0f,
        -0.04f, -0.04f, 0.0f, 0.0f,
        -0.04f, -0.04f, 0.0f, 0.0f,
        -0.04f, 0.04f, 0.0f, 1.0f,
        0.04f, 0.04f, 1.0f, 1.0f
    };
    float enemyVerticies [] =
    {
        0.070f, 0.055f, 1.0f, 1.0f,
        0.070f, -0.055f, 1.0f, 0.0f,
        -0.070f, -0.055f, 0.0f, 0.0f,
        -0.070f, -0.055f, 0.0f, 0.0f,
        -0.070f, 0.055f, 0.0f, 1.0f,
        0.070f, 0.055f, 1.0f, 1.0f
    };
    
    float astroidSlowVerticies [] =
    {
        0.035f, 0.035f, 1.0f, 1.0f,
        0.035f, -0.035f, 1.0f, 0.0f,
        -0.035f, -0.035f, 0.0f, 0.0f,
        -0.035f, -0.035f, 0.0f, 0.0f,
        -0.035f, 0.035f, 0.0f, 1.0f,
        0.035f, 0.035f, 1.0f, 1.0f
    };
    float astroidKillVerticies [] =
    {
        0.059f, 0.059f, 1.0f, 1.0f,
        0.059f, -0.059f, 1.0f, 0.0f,
        -0.059f, -0.059f, 0.0f, 0.0f,
        -0.059f, -0.059f, 0.0f, 0.0f,
        -0.059f, 0.059f, 0.0f, 1.0f,
        0.059f, 0.059f, 1.0f, 1.0f
    };
    float powerupVerticies [] =
    {
        0.035f, 0.035f, 1.0f, 1.0f,
        0.035f, -0.035f, 1.0f, 0.0f,
        -0.035f, -0.035f, 0.0f, 0.0f,
        -0.035f, -0.035f, 0.0f, 0.0f,
        -0.035f, 0.035f, 0.0f, 1.0f,
        0.035f, 0.035f, 1.0f, 1.0f
    };
    float heartVerticies [] =
    {
        0.059f, 0.059f, 1.0f, 1.0f,
        0.059f, -0.059f, 1.0f, 0.0f,
        -0.059f, -0.059f, 0.0f, 0.0f,
        -0.059f, -0.059f, 0.0f, 0.0f,
        -0.059f, 0.059f, 0.0f, 1.0f,
        0.059f, 0.059f, 1.0f, 1.0f
    };

    ma_engine soundEffectsEngine;
    bool isShipDestroyed = false;
    bool isShipShielded = false;
    bool enemyFrameSwitch = false;
    bool isGameover = false;
    int row = 0;
    int col = 0;
    int shipLives = 3;
    int randomNumberEnemies = 0;
    int randomNumberFallingObject = 0;
    float rightLeftMove = 0.0f;
    float upDownMove = -0.5f;
    float previousFrame = 0.0f;
    float currentFrame = 0.0f;
    float backgroundScrollOffset = 0.0f;
    float shootCooldown = 0.0f;
    float shootCooldownReduced = 0.3f;
    float enemyRightLeft = 0.9f;
    float enemyUpDown = 0.2f;
    float spacing = 0.25f;
    float xBound = 1.0f;
    float yBound = 1.0f;
    float xEnemies = 0.0f;
    float yEnemies = 0.0f;
    float enemyDirection = 1.0f;
    float enemyMoveCooldown = 1.5f;
    float enemyShootCooldown = 0.75f;
    float fallingObjectCooldown = 1.5f;
    float shipSlowTimer = 3.0f;
    float shipFastTimer = 3.0f;
    float shipShieldTimer = 3.0f;
    float shipFirerateTimer = 3.0f;
    float shipSpeed = 0.9f;
    getAspectRatio(mainWindow, xBound, yBound); 

    glm::mat4 projectionMatrix = createProjectionMatrix(mainWindow);
    unsigned int textureShaderProgram = createTextureShaderProgram();
    unsigned int backgroundModel = createMeshTexture(backgroundVerticies, sizeof(backgroundVerticies));
    unsigned int backgroundTextureObject = createTextureToMesh("../Asset Packs/Background Asset.png", 0);
    unsigned int shipModel = createMeshTexture(shipVerticies, sizeof(shipVerticies));
    unsigned int shipTextureObject = createTextureToMesh("../Asset Packs/Ship/Red Space Ship.png", 1);
    unsigned int bulletModel = createMeshTexture(bulletVerticies, sizeof(bulletVerticies));
    unsigned int bulletTexture = createTextureToMesh("../Asset Packs/Ship/Bullet Normal.png", 2);
    unsigned int enemyModel = createMeshTexture(enemyVerticies, sizeof(enemyVerticies));
    unsigned int enemyTextureFrame1 = createTextureToMesh("../Asset Packs/Enemies/Red Enemy Frame 1.png", 3);
    unsigned int enemyTextureFrame2 = createTextureToMesh("../Asset Packs/Enemies/Red Enemy Frame 2.png", 10);
    unsigned int enemyBulletModel = createMeshTexture(bulletVerticies, sizeof(bulletVerticies));
    unsigned int enemyBulletTexture = createTextureToMesh("../Asset Packs/Enemies/Red Enemy Bullet.png", 4);
    unsigned int astroidSlowModel = createMeshTexture(astroidSlowVerticies, sizeof(astroidSlowVerticies));
    unsigned int astroidSlowTexture = createTextureToMesh("../Asset Packs/Falling Objects/Slow Object.png", 5);
    unsigned int astroidKillModel = createMeshTexture(astroidKillVerticies, sizeof(astroidKillVerticies));
    unsigned int astroidKillTexture = createTextureToMesh("../Asset Packs/Falling Objects/Kill Object.png", 6);
    unsigned int powerupSpeedModel = createMeshTexture(powerupVerticies, sizeof(powerupVerticies));
    unsigned int powerupSpeedTexture = createTextureToMesh("../Asset Packs/Falling Objects/Speed Power Up.png", 7);
    unsigned int powerupShieldModel = createMeshTexture(powerupVerticies, sizeof(powerupVerticies));
    unsigned int powerupShieldTexture = createTextureToMesh("../Asset Packs/Falling Objects/Shield Power Up.png", 8);
    unsigned int powerupFirerateModel = createMeshTexture(powerupVerticies, sizeof(powerupVerticies));
    unsigned int powerupFirerateTexture = createTextureToMesh("../Asset Packs/Falling Objects/Fire Rate Power Up.png", 9);
    unsigned int heartModel = createMeshTexture(heartVerticies, sizeof(heartVerticies));
    unsigned int heartTextureFull = createTextureToMesh("../Asset Packs/Hearts/Full Heart.png",11);
    unsigned int heartTextureHalf = createTextureToMesh("../Asset Packs/Hearts/Half Heart.png",12);
    unsigned int heartTextureZero = createTextureToMesh("../Asset Packs/Hearts/Zero Heart.png",13);


    // Setting Unifrom Vars within the Shader functions
    glUseProgram(textureShaderProgram); //Binds Shader Program
    int textureDataLocation = glGetUniformLocation(textureShaderProgram, "textureData");
    int projectionLocation = glGetUniformLocation(textureShaderProgram, "projectionMatrix");
    int newPosVerticiesLocation = glGetUniformLocation(textureShaderProgram, "newPosVerticies");
    int newPosTextureLocation = glGetUniformLocation(textureShaderProgram, "newPosTexture");

    ma_engine_init(NULL, &soundEffectsEngine); // Sets up the sound engine for use

    // Adds enemy count in vector
    for(int i = 0; i < 52; i++)
    {
        Enemy enemy;
        enemy.isAlive = true;
        enemies.push_back(enemy);
    }

    //Adds objects in vector (Currently kill/slow astroids/speed powerup)
    for(int i = 0; i < 9; i++)
    {
        if(i < 3)
        {
            FallingObject fallingObject;
            fallingObject.objectX = generateRandomNumber(-1, 1, 2);
            fallingObject.objectY = 1.0f;
            fallingObject.speed = generateRandomNumber(0.2, 1, 2);
            fallingObject.type = 0;
            fallingObjects.push_back(fallingObject);
        }
        if(i >= 3 && i < 6)
        {
            FallingObject fallingObject;
            fallingObject.objectX = generateRandomNumber(-1, 1, 2);
            fallingObject.objectY = 1.0f;
            fallingObject.speed = generateRandomNumber(0.2, 1, 2);
            fallingObject.type = 1;
            fallingObjects.push_back(fallingObject);
        }
        if(i == 7)
        {
            FallingObject fallingObject;
            fallingObject.objectX = generateRandomNumber(-1, 1, 2);
            fallingObject.objectY = 1.0f;
            fallingObject.speed = generateRandomNumber(0.2, 1, 2);
            fallingObject.type = 2;
            fallingObjects.push_back(fallingObject);
        }
        if(i == 8)
        {
            FallingObject fallingObject;
            fallingObject.objectX = generateRandomNumber(-1, 1, 2);
            fallingObject.objectY = 1.0f;
            fallingObject.speed = generateRandomNumber(0.2, 1, 2);
            fallingObject.type = 3;
            fallingObjects.push_back(fallingObject);
        }
            if(i == 9)
        {
            FallingObject fallingObject;
            fallingObject.objectX = generateRandomNumber(-1, 1, 2);
            fallingObject.objectY = 1.0f;
            fallingObject.speed = generateRandomNumber(0.2, 1, 2);
            fallingObject.type = 4;
            fallingObjects.push_back(fallingObject);
        }
    }

    glfwSetJoystickCallback(joyStickConnected); // Sets a callback function for controller
    previousFrame = glfwGetTime();
    yEnemies = yBound;

    while(!glfwWindowShouldClose(mainWindow))
    {
        // Calculate Delta Time (and other values)
        currentFrame = glfwGetTime();
        float deltaTime = currentFrame - previousFrame;
        previousFrame = currentFrame;
        backgroundScrollOffset = backgroundScrollOffset + (deltaTime * 0.6);
        randomNumberEnemies = generateRandomNumber(0, 52, 1);
        randomNumberFallingObject = generateRandomNumber(0, fallingObjects.size() - 1, 1);

        // Sets Active Objects from the Object Pool
        setRandomItem(activeFallingObjects, fallingObjects, fallingObjectCooldown, randomNumberFallingObject, deltaTime);

        // Set Controls
        for(int i = GLFW_JOYSTICK_1; i < GLFW_JOYSTICK_16; i++)
        {
            if(glfwJoystickPresent(i))
            {
                joystickID = i;
                break;
            }
        }
        if(joystickID != -1)
        {
            addJoystickMovement(mainWindow, soundEffectsEngine, shipBullets, joystickID, rightLeftMove, upDownMove, shootCooldown, shootCooldownReduced, shipSpeed, deltaTime);
        }
        addKeyboardMovement(mainWindow, soundEffectsEngine, shipBullets, rightLeftMove, upDownMove, shootCooldown, shootCooldownReduced, shipSpeed, isShipDestroyed, deltaTime);
        shootCooldown = shootCooldown - deltaTime;

        // Clears the screen for next frame
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw background model
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f))); // Send identy matrix to stretch bg
        glUniform1i(textureDataLocation, 0); // Sends slot used to the unifrom var in shader function
        glUniform2f(newPosVerticiesLocation, 0.0f , 0.0f); // Send no movement first to not move the bg
        glUniform2f(newPosTextureLocation, 0.0f, backgroundScrollOffset); // UV scrolling
        glBindVertexArray(backgroundModel); // Binds background VAO
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Draw the ship model
        if(isShipDestroyed != true)
        {
            glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
            glUniform1i(textureDataLocation, 1); // Sends slot used to the unifrom var in shader function
            glUniform2f(newPosVerticiesLocation, rightLeftMove, upDownMove); // Sends (new) movement location continously
            glUniform2f(newPosTextureLocation, 0.0f, 0.0f); // Sends zero movement to the texture of the ship
            glBindVertexArray(shipModel); // Binds ship VAO
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        // Draws the falling objects models
        for(int i = 0; i < activeFallingObjects.size(); i++)
        {
            glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
            glUniform2f(newPosVerticiesLocation, activeFallingObjects[i].objectX , activeFallingObjects[i].objectY); // Send coords
            glUniform2f(newPosTextureLocation, 0.0f, 0.0f); // Sends zero movement to the texture of the falling object
            if(activeFallingObjects[i].type == 0)
            {
                glUniform1i(textureDataLocation, 5); // Sends slot used to the unifrom var in shader function
                glBindVertexArray(astroidSlowModel);
            }
            else if(activeFallingObjects[i].type == 1)
            {
                glUniform1i(textureDataLocation, 6); // Sends slot used to the unifrom var in shader function
                glBindVertexArray(astroidKillModel);
            }
            else if(activeFallingObjects[i].type == 2)
            {
                glUniform1i(textureDataLocation, 7); // Sends slot used to the unifrom var in shader function;
                glBindVertexArray(powerupSpeedModel);
            }
            else if(activeFallingObjects[i].type == 3)
            {
                glUniform1i(textureDataLocation, 8); // Sends slot used to the unifrom var in shader function;
                glBindVertexArray(powerupShieldModel);
            }
            else if(activeFallingObjects[i].type == 4)
            {
                glUniform1i(textureDataLocation, 9); // Sends slot used to the unifrom var in shader function;
                glBindVertexArray(powerupFirerateModel);
            }
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        // Draw the enemy model
        for(int i = 0; i < enemies.size(); i++)
        {
            row = i / 13;
            col = i % 13;
            if(enemies[i].isAlive == false) continue;
            glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
            if(enemyFrameSwitch == false) glUniform1i(textureDataLocation, 3); // Sends slot used to the unifrom var in shader function (For Frame 1)
            else if(enemyFrameSwitch == true) glUniform1i(textureDataLocation, 10); // Sends slot used to the unifrom var in shader function (For Frame 2)
            glUniform2f(newPosVerticiesLocation, xEnemies + (-(12 * spacing) / 2) + (col * spacing), yEnemies - 0.2f - (row * spacing)); // Sends coords
            glUniform2f(newPosTextureLocation, 0.0f, 0.0f); // Sends zero movement to the texture of the enemy
            glBindVertexArray(enemyModel);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        // Draw the ship bullets model (when used)
        for(int i = 0; i < shipBullets.size(); i++)
        {
            glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
            glUniform1i(textureDataLocation, 2); // Sends slot used to the unifrom var in shader function;
            glUniform2f(newPosVerticiesLocation, shipBullets[i].bulletX, shipBullets[i].bulletY); // Send coord relative to ship
            glUniform2f(newPosTextureLocation, 0.0f, 0.0f); // Sends zero movement to the texture of the ship
            glBindVertexArray(bulletModel); // Binds background VAO
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
        

        // Draw the enemy bullets model (when used)
        for(int i = 0; i < enemyBullets.size(); i++)
        {
            
            glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
            glUniform1i(textureDataLocation, 4); // Sends slot used to the unifrom var in shader function;
            glUniform2f(newPosVerticiesLocation, enemyBullets[i].bulletX, enemyBullets[i].bulletY); // Send coord relative to enemy
            glUniform2f(newPosTextureLocation, 0.0f, 0.0f); // Sends zero movement to the texture of the bullet
            glBindVertexArray(enemyBulletModel); // Binds the enemy bullet VAO
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        // Draw heart model
        if(shipLives > 0)
        {
            glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix)); // Send identy matrix to stretch bg
            if(shipLives == 3) glUniform1i(textureDataLocation, 11); // Sends slot used to the unifrom var in shader function
            else if(shipLives == 2) glUniform1i(textureDataLocation, 12); // Sends slot used to the unifrom var in shader function
            else if(shipLives == 1) glUniform1i(textureDataLocation, 13); // Sends slot used to the unifrom var in shader function
            glUniform2f(newPosVerticiesLocation, (-xBound + 0.25f) , -0.8f); // Send no movement first to not move the bg
            glUniform2f(newPosTextureLocation, 0.0f, 0.0f); // UV scrolling
            glBindVertexArray(heartModel); // Binds heart VAO         
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
        else if(isGameover == false)
        {
            ma_engine_play_sound(&soundEffectsEngine, "../Asset Packs/Sound Effects/Game Over Sound Effectwav.wav", NULL);
            isGameover = true;
        }

        // Enemy Movement Timer (For blocky movement)
        enemyMoveCooldown = enemyMoveCooldown - deltaTime;
        if(enemyMoveCooldown <= 0.0f)
        {
            enemyMoveCooldown = 1.5f;
            enemyFrameSwitch = !enemyFrameSwitch;
            if(xEnemies + (12 * spacing) / 2 >= xBound - 0.15f)
            {
                enemyDirection = -1.0f;
                yEnemies = yEnemies - 0.06f;
            }
            if(xEnemies + -((12 * spacing) / 2) <= -xBound + 0.15f)
            {
                enemyDirection = 1.0f;
                yEnemies = yEnemies - 0.06f;
            }
            xEnemies = xEnemies + (0.05f * enemyDirection);
        }

        // Ship Bullet Movement and Removal Code
        shipBulletMovement(deltaTime, shipBullets);

        // Collison check for ship bullets
        shipBulletCollisionCheck(shipBullets, enemies, soundEffectsEngine, xEnemies, yEnemies, spacing);

        // Add enemy bullets (cooldown)
        enemyBulletSpawner(enemies, enemyBullets, soundEffectsEngine, xEnemies, yEnemies, spacing, enemyShootCooldown, randomNumberEnemies, deltaTime);

        // Enemy Bullet Movement and Removal Code
        enemyBulletMovement(enemyBullets, deltaTime);

        // Collison check for enemy bullets
        enemyBulletCollisionCheck(enemyBullets, soundEffectsEngine ,rightLeftMove, upDownMove, shipLives, isShipDestroyed, isShipShielded);

        // Collison check for enemies hitbox
        shipAndEnemyCollisionCheck(enemies, soundEffectsEngine, rightLeftMove, upDownMove, xEnemies, yEnemies, shipLives, spacing, isShipDestroyed);

        // Falling Objects Movement and Removal Code
        fallingObjectsMovement(activeFallingObjects, deltaTime);

        // Collison check for falling object
        fallingObjectCollisionCheck(activeFallingObjects, soundEffectsEngine, rightLeftMove, upDownMove, shipLives, shipSpeed, isShipDestroyed, isShipShielded, shipSlowTimer, shipFastTimer, shipShieldTimer, shipFirerateTimer, shootCooldownReduced, deltaTime);

        // Swaps the buffer to show img (this is to prevent stuttering)
        glfwSwapBuffers(mainWindow);

        // Manages and process events that are related to user actions (Keyboard hit, close window, etc)
        glfwPollEvents();
    }
}