#ifndef STRUCTHANDLER_H
#define STRUCTHANDLER_H

//Instructions for types
// 0 => Slow Astroid - DONE 
// 1 => Kill Astroid - DONE
// 2 => Speed power up - DONE
// 3 => Sheild (Timed)
// 4 => Extra Live
// 5 => Faster Fire rate
// 6 => Double Shoots
// 7 => Nuke (Kills all enemies on screen)
struct FallingObject
{
    float objectX;
    float objectY;
    float speed;
    int type;
};

struct Bullet
{
    float bulletX;
    float bulletY;
    bool isEnemyBullet;
};

struct Enemy
{
    bool isAlive;
};



#endif // STRUCTHANDLER_H