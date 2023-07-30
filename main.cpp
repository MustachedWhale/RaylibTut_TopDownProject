#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    // Window dimensions
    const int windowWidth{384};  // Window x dimension
    const int windowHeight{384}; // Window y dimension

    // Initialise window
    InitWindow(windowHeight, windowWidth, "Jonathan's Top Down");

    // Load background texture
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0};

    Character knight{windowWidth, windowHeight};

    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/log.png")}
    };

    Enemy goblin{
        Vector2{800.f, 300.f}, 
        LoadTexture("characters/goblin_idle_spritesheet.png"), 
        LoadTexture("characters/goblin_run_spritesheet.png")
    };

    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")
    };

    Enemy* enemies[]{
        &goblin,
        &slime
    };

    for (auto enemy : enemies)
    {
        enemy -> setTarget(&knight);
    }

    // Passes in the address of knight (&). We use a pointer here because we want to refer to that specific knight, not a copy.
    goblin.setTarget(&knight);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getworldPos(), -1.f);

        // Draw the map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        // Draw the props
        for (auto prop : props)
        {
            prop.Render(knight.getworldPos());
        }

        if (!knight.getAlive()) // Character is alive 
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else // Character is not alive
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
            
        }

        knight.tick(GetFrameTime());

        // Check map bounds
        if (knight.getworldPos().x < 0.f || 
            knight.getworldPos().y < 0.f ||
            knight.getworldPos().x + windowWidth > map.width * mapScale ||
            knight.getworldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        // Check prop collisions
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getworldPos()), knight.getCollisionRec()))
                {
                    knight.undoMovement();
                }
        }

        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());

        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                    {
                        enemy->setAlive(false);
                    }
            }
            
        }

        // End drawing
        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();
}