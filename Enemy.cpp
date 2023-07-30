#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;

    width = texture.width/maxFrames;
    height = texture.height;
    // Child speed variable
    speed = 2.f;
}

void Enemy::tick(float deltaTime)
{
    if (!getAlive()) return;

    // Get velocity
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if (Vector2Length(velocity) < radius) velocity = {};
    BaseCharacter::tick(deltaTime);

    if (CheckCollisionRecs(target->getCollisionRec(), getCollisionRec()))
    {
        target->takeDamage(damagePerSec * deltaTime);
    }
}

Vector2 Enemy::getScreenPos()
{
    // target is *Character - gets worldPos of specific character instance
    return Vector2Subtract(worldPos, target->getworldPos());
}