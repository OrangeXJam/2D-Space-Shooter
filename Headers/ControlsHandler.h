    #ifndef CONTROLSHANDLER_H
    #define CONTROLSHANDLER_H

    #include <iostream>
    #include <vector>
    #include <random>
    #include <GLFW/glfw3.h>
    #include "StructHandler.h"
    #include "WindowHandler.h"

    void addKeyboardMovement (GLFWwindow* window, ma_engine &soundEffectsEngine, std::vector<Bullet> &bullets, float &xAxisMovement, float &yAxisMovement, float &shootCooldown, float &shootCooldownReduced, float shipSpeed, bool &isShipDestroyed, float deltaTime)
    {
        float xBound = 1.0f;
        float yBound = 1.0f;
        getAspectRatio(window, xBound, yBound); 
        if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            xAxisMovement = xAxisMovement + (shipSpeed * deltaTime);
            if(xAxisMovement > xBound) xAxisMovement = xBound;
        }
            if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            xAxisMovement = xAxisMovement - (shipSpeed * deltaTime);
            if(xAxisMovement < -xBound) xAxisMovement = -xBound;
        }
            if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            yAxisMovement = yAxisMovement + (shipSpeed * deltaTime);
            if(yAxisMovement > yBound) yAxisMovement = yBound;
        }
            if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            yAxisMovement = yAxisMovement - (shipSpeed * deltaTime);
            if(yAxisMovement < -yBound) yAxisMovement = -yBound;
        }
            if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && isShipDestroyed == false)
        {
            if(shootCooldown <= 0.0f)
            {
                Bullet bullet;
                bullet.bulletX = xAxisMovement;
                bullet.bulletY = yAxisMovement + 0.1f;
                bullets.push_back(bullet);      
                shootCooldown = shootCooldownReduced;
                ma_engine_play_sound(&soundEffectsEngine, "../Asset Packs/Sound Effects/Player Shoot Sound Effect.wav", NULL);
            }
        }
    }

    void addJoystickMovement (GLFWwindow* window, ma_engine &soundEffectsEngine ,std::vector<Bullet> &bullets, int joystickID ,float &xAxisMovement, float &yAxisMovement, float &shootCooldown, float &shootCooldonwReduced, float shipSpeed, float deltaTime)
    {
        if(glfwJoystickPresent(joystickID))
        {
            int axesCount;
            int buttonCount;
            const float* axesData = glfwGetJoystickAxes(joystickID, &axesCount);
            const unsigned char* buttonData = glfwGetJoystickButtons(joystickID, &buttonCount);
            float xBound = 1.0f;
            float yBound = 1.0f;
            getAspectRatio(window, xBound, yBound); 
            if(axesCount > 2)
            {
                float deadzoneRange = 0.2;
                if(std::abs(axesData[0]) > deadzoneRange)
                {
                    xAxisMovement = xAxisMovement + (axesData[0] * (shipSpeed * deltaTime));
                    if(xAxisMovement > xBound) xAxisMovement = xBound;
                    if(xAxisMovement < -xBound) xAxisMovement = -xBound;
                }
                if(std::abs(axesData[1]) > deadzoneRange)
                {
                    yAxisMovement = yAxisMovement - (axesData[1] * (shipSpeed * deltaTime));
                    if(yAxisMovement > yBound) yAxisMovement = yBound;
                    if(yAxisMovement < -yBound) yAxisMovement = -yBound;
                }
                if(buttonData[1] == GLFW_PRESS  && shootCooldown <= 0.0f)
                {
                    Bullet bullet;
                    bullet.bulletX = xAxisMovement;
                    bullet.bulletY = yAxisMovement + 0.1f;
                    bullets.push_back(bullet);      
                    shootCooldown = shootCooldonwReduced;
                    ma_engine_play_sound(&soundEffectsEngine, "../Asset Packs/Sound Effects/Player Shoot Sound Effect.wav", NULL);
                }
            }
        }
    }

    extern int joystickID;
    void joyStickConnected(int callbackjoyStickID,int event)
    {
        if(event == GLFW_CONNECTED)
        {
            joystickID = callbackjoyStickID;
        }
        if(event == GLFW_DISCONNECTED)
        {
            joystickID = -1;
        }
    }

    float generateRandomNumber(float min, float max, int type)
    {
        static std::random_device seed;
        static std::mt19937 engine(seed());
        if(type == 1)
        {
            std::uniform_int_distribution<int> range(min, max);
            return range(engine);
        }
        if(type == 2)
        {
            std::uniform_real_distribution<float> range(min, max);
            return range(engine);
        }
        return -1;
    }

    #endif // CONTROLSHANDLER_H