// Preprocessor directives to prevent BaseCharacter being included multiple times 
// #ifndef = if not defined
// Defines BASE_CHARACTER_H on the first pass (main.cpp/#include "Character.h")
// Will not include the code again when #include "Enemy.h" is called
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getworldPos() {return worldPos;}
    void undoMovement();
    Rectangle getCollisionRec();
    // Creating a virtual function allows us to override functions within classes derived from BaseCharacter
    virtual void tick(float deltaTime);
    // = 0 makes getScreenPos a pure virtual function. Means it is not defined in BC.cpp, only in BC child classes, Enemy and Character.
    // Including a pure virtual function makes BaseCharacter an abstract class, meaning we cannot call an instance of it,
    // but only create children of it.
    virtual Vector2 getScreenPos() = 0;
    bool getAlive() { return alive;}
    void setAlive(bool isAlive) { alive = isAlive; }
// Protected allows us to access these variables in derived classes
protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    // 1 = facing right, -1 = facing left
    float rightLeft{1.f};
    // Animation variables
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.f / 12.f};
    float speed{4.f};
    float width{};
    float height{};
    float scale{4.0f};
    Vector2 velocity{};

private:
    bool alive{true};
};

#endif