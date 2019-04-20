#pragma once

#include <Game/Game.h>
#include <Game/Tilemap.h>

class MapGameModule : public GameModule
{
public:
    MapGameModule(GameEngine* engine);
    ~MapGameModule();

    ASprite* Player;
    Tilemap* tilemap;
    
    void Update(unsigned int deltaTime) override;
    void Draw(ARenderer* renderer) override;

private:
    void UpdatePlayerPosition();
};
