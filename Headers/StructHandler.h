#ifndef STRUCTHANDLER_H
#define STRUCTHANDLER_H

//Instructions for types
// 0 => Slow Astroid - DONE 
// 1 => Kill Astroid - DONE
// 2 => Speed power up - DONE
// 3 => Sheild (Timed) - DONE
// 4 => Faster Fire rate - DONE
// 5 => Double Shoots
// 6 => Nuke (Kills all enemies on screen)
// 7 => Extra Live
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