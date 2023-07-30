#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
    virtual void tick(float deltaTime) override;
    // Adding { } after the input parameters works if your function is only one statement
    // Semi-colon goes at the end of the statement, not the end of the function
    void setTarget(Character* character) { target = character; }
    virtual Vector2 getScreenPos() override;
private:
    // Pointer to character
    Character* target;
    float damagePerSec{10.f};
    float radius{25.f};
};