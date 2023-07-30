#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

// "public" allows you to access all the functions within a parent class
// Is set to private by default (if no modifier specified/left blank)
class Character : public BaseCharacter
{
public:
    // Constructor declaration
    Character(int winWidth, int winHeight);
    // Adding virtual and override to this functions shows us know that the function is virtual -
    // we don't need to go rooting through the BaseCharacter files to see whether it's virtual
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponCollisionRec() { return weaponCollisionRec; }
    // Basic getters like this are usually const - we know we'll never need to change any of the variables
    float getHealth() const { return health; }
    void takeDamage(float damage);
private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
    float health{100.f};
};

#endif