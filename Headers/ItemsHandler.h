#ifndef ITEMSHANDLER_H
#define ITEMSHANDLER_H

#include <vector>
#include "StructHandler.h"

void shipBulletMovement(float deltaTime, std::vector <Bullet> &bullets)
{
    for(int i = 0; i < bullets.size(); i++)
    {
        bullets[i].bulletY = bullets[i].bulletY + deltaTime;
    }
    for(int i = bullets.size() - 1; i >= 0; i--)
    {
        if(bullets[i].bulletY > 1.0f)
        {
            bullets.erase(bullets.begin() + i);
        }
    }
}

void shipBulletCollisionCheck(std::vector<Bullet> &shipBullets, std::vector<Enemy> &enemies, float &xEnemies, float &yEnemies, float spacing)
{
    for(int i = shipBullets.size() - 1; i >= 0; i--)
    {
        for(int j = enemies.size() - 1; j >= 0; j--)
        {
            if (enemies[j].isAlive == false) continue;
            int enemyRow = j / 13;
            int enemyCol = j % 13;
            float enemyCurrentX = xEnemies + (-(12 * spacing) / 2) + (enemyCol * spacing);
            float enemyCurrentY = yEnemies - 0.2f - (enemyRow * spacing);
            if(shipBullets[i].bulletX <= enemyCurrentX + 0.055f && shipBullets[i].bulletX >= enemyCurrentX - 0.055f && shipBullets[i].bulletY <= enemyCurrentY + 0.055f && shipBullets[i].bulletY >= enemyCurrentY - 0.055f)
            {
                shipBullets.erase(shipBullets.begin() + i);
                enemies[j].isAlive = false;
                break;
            }
        }
    }
}

void enemyBulletSpawner(std::vector <Enemy> &enemies, std::vector <Bullet> &enemyBullets, float xEnemies, float yEnemies, float spacing, float &enemyShootCooldown, int randomNumber, float deltaTime)
{
    if(enemyShootCooldown <= 0.0f)
    {
        if(enemies[randomNumber].isAlive == false) return;
        Bullet bullet;
        float enemyRow = randomNumber / 13;
        float enemyCol = randomNumber % 13;
        bullet.bulletX = xEnemies + (-(12 * spacing) / 2) + (enemyCol * spacing);
        bullet.bulletY = (yEnemies - 0.2f - (enemyRow * spacing)) - 0.07f;
        enemyBullets.push_back(bullet);
        enemyShootCooldown = 1.5f;
    }
    enemyShootCooldown = enemyShootCooldown - deltaTime;
}

void enemyBulletMovement(std::vector<Bullet> &enemyBullets, float deltaTime)
{
    for(int i = 0; i < enemyBullets.size(); i++)
    {
        enemyBullets[i].bulletY = enemyBullets[i].bulletY - (deltaTime * 0.8f);
    }
    for(int i = enemyBullets.size() - 1; i >= 0; i--)
    {
        if(enemyBullets[i].bulletY < -1.0f)
        {
            enemyBullets.erase(enemyBullets.begin() + i);
        }
    }
}

void enemyBulletCollisionCheck(std::vector<Bullet> &enemyBullets, float xAxis, float yAxis, bool &isShipDestroyed, bool &isShipShielded)
{
    for(int i = enemyBullets.size() - 1; i >= 0; i--)
    {
        if(isShipDestroyed == true) continue;
        if(enemyBullets[i].bulletX >= (xAxis - 0.08f) && enemyBullets[i].bulletX <= (xAxis + 0.08f) && enemyBullets[i].bulletY >= (yAxis - 0.08f) && enemyBullets[i].bulletY <= (yAxis + 0.08f) && isShipShielded == false)
        {
            enemyBullets.erase(enemyBullets.begin() + i);
            isShipDestroyed = true;
        }
    }
}

void shipAndEnemyCollisionCheck(std::vector<Enemy> &enemies, float &shipAxisX, float &shipAxisY, float enemyAxisX, float enemyAxisY, float spacing, bool &isShipDestroyed)
{
    for(int i = enemies.size() - 1; i >= 0; i--)
    {
        if(enemies[i].isAlive == false) continue;
        float enemyRow = i / 13;
        float enemyCol = i % 13;
        float enemyX = enemyAxisX + (-(12 * spacing) / 2) + (enemyCol * spacing);
        float enemyY = enemyAxisY - 0.2f - (enemyRow * spacing);
        if(enemyX <= (shipAxisX + 0.135f) && enemyX >= (shipAxisX - 0.135f) && enemyY <= (shipAxisY + 0.135f) && enemyY >= (shipAxisY - 0.135f))
        {
            isShipDestroyed = true;
        }
    }
}

void setRandomItem(std::vector<FallingObject> &activeFallingObjects, std::vector <FallingObject> fallingObjects, float &fallingObjectCooldown, int randomNumberFallingObject, float deltaTime)
{
    fallingObjectCooldown = fallingObjectCooldown - deltaTime;
    if(fallingObjectCooldown <= 0.0f)
    {
        FallingObject tempObject = fallingObjects[randomNumberFallingObject];
        tempObject.objectX = generateRandomNumber(-1, 1, 2);
        tempObject.objectY = 1.0f;
        tempObject.speed = generateRandomNumber(0.5, 1, 2);
        activeFallingObjects.push_back(tempObject);
        fallingObjectCooldown = 1.5f;
    }
}

void fallingObjectsMovement(std::vector<FallingObject> &activeFallingObjects, float deltaTime)
{
        for(int i = 0; i < activeFallingObjects.size(); i++)
        {
            activeFallingObjects[i].objectY = activeFallingObjects[i].objectY - (deltaTime * activeFallingObjects[i].speed);
        }
        for(int i = activeFallingObjects.size() - 1; i >= 0; i--)
        {
            if(activeFallingObjects[i].objectY < -1.0f)
            {
                activeFallingObjects.erase(activeFallingObjects.begin() + i);
            }
        }
}

void fallingObjectCollisionCheck(std::vector<FallingObject> &activeFallingObjects, float xAxis, float yAxis, float &shipSpeed, bool &isShipDestroyed, bool &isShipShielded, float &shipSlowTimer, float &shipFastTimer, float &shipShieldTimer, float &shipFirerateTimer, float &shootCooldownReduced, float deltaTime)
{
    for(int i = activeFallingObjects.size() - 1; i >= 0; i--)
    {
        if(activeFallingObjects[i].objectX >= (xAxis - 0.08f) && activeFallingObjects[i].objectX <= (xAxis + 0.08f) && activeFallingObjects[i].objectY >= (yAxis - 0.08f) && activeFallingObjects[i].objectY <= (yAxis + 0.08f) && activeFallingObjects[i].type == 0)
        {
            activeFallingObjects.erase(activeFallingObjects.begin() + i);
            shipSpeed = shipSpeed / 2;
            shipSlowTimer = 3.0f;
            continue;
        }

        if(activeFallingObjects[i].objectX >= (xAxis - 0.08f) && activeFallingObjects[i].objectX <= (xAxis + 0.08f) && activeFallingObjects[i].objectY >= (yAxis - 0.08f) && activeFallingObjects[i].objectY <= (yAxis + 0.08f) && activeFallingObjects[i].type == 1 && isShipShielded == false)
        {
            activeFallingObjects.erase(activeFallingObjects.begin() + i);
            isShipDestroyed = true;
            continue;
        }

        if(activeFallingObjects[i].objectX >= (xAxis - 0.08f) && activeFallingObjects[i].objectX <= (xAxis + 0.08f) && activeFallingObjects[i].objectY >= (yAxis - 0.08f) && activeFallingObjects[i].objectY <= (yAxis + 0.08f) && activeFallingObjects[i].type == 2)
        {
            activeFallingObjects.erase(activeFallingObjects.begin() + i);
            shipSpeed = shipSpeed * 2;
            shipFastTimer = 3.0f;
            continue;
        }
        if(activeFallingObjects[i].objectX >= (xAxis - 0.08f) && activeFallingObjects[i].objectX <= (xAxis + 0.08f) && activeFallingObjects[i].objectY >= (yAxis - 0.08f) && activeFallingObjects[i].objectY <= (yAxis + 0.08f) && activeFallingObjects[i].type == 3)
        {
            activeFallingObjects.erase(activeFallingObjects.begin() + i);
            isShipShielded = true;
            shipShieldTimer = 3.0f;
            continue;
        }
        if(activeFallingObjects[i].objectX >= (xAxis - 0.08f) && activeFallingObjects[i].objectX <= (xAxis + 0.08f) && activeFallingObjects[i].objectY >= (yAxis - 0.08f) && activeFallingObjects[i].objectY <= (yAxis + 0.08f) && activeFallingObjects[i].type == 4)
        {
            activeFallingObjects.erase(activeFallingObjects.begin() + i);
            shootCooldownReduced = 0.15f;
            shipFirerateTimer = 3.0f;
            continue;
        }
    }
    if(shipFastTimer <= 0.0f && shipSlowTimer <= 0.0f) shipSpeed = 0.9f;
    if(shipShieldTimer <= 0.0f) isShipShielded = false;
    if(shipFirerateTimer <= 0.0f) shootCooldownReduced = 0.3f;
    shipSlowTimer = shipSlowTimer - deltaTime;
    shipFastTimer = shipFastTimer - deltaTime;
    shipShieldTimer = shipShieldTimer - deltaTime;
    shipFirerateTimer = shipFirerateTimer - deltaTime;
}

#endif // ITEMSHANDLER_H