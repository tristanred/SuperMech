#include "Modules/MapGameModule.h"

#include <ResourceManager.h>
#include <Input/AKeyboard.h>

MapGameModule::MapGameModule(GameEngine* engine)
    : GameModule(engine)
{
    engine->ResManager->AddFile("assets/grass.png", "grass");
    engine->ResManager->AddFile("assets/player.png", "player");

    this->Player = engine->CreateSprite();
    this->Player->SetTexture("player");

    TilemapConfig config;
    config.width  = 10;
    config.height = 10;

    this->tilemap = new Tilemap(engine, &config);
    this->tilemap->Setup(engine->Renderer);

    this->AttachRenderable(this->tilemap);
    this->AttachRenderable(this->Player);
}

MapGameModule::~MapGameModule()
{

}

void MapGameModule::Update(unsigned int deltaTime)
{
    GameModule::Update(deltaTime);
    
    this->UpdatePlayerPosition();
}

void MapGameModule::Draw(ARenderer *renderer)
{
    GameModule::Draw(renderer);
}

void MapGameModule::UpdatePlayerPosition()
{
    FPosition pPos = this->Player->GetPosition();
    if(this->GetEngine()->Keyboard->IsKeyDown(Key::Right))
    {
        pPos.X++;
    }
    if(this->GetEngine()->Keyboard->IsKeyDown(Key::Down))
    {
        pPos.Y++;
    }
    if(this->GetEngine()->Keyboard->IsKeyDown(Key::Left))
    {
        pPos.X--;
    }
    if(this->GetEngine()->Keyboard->IsKeyDown(Key::Up))
    {
        pPos.Y--;
    }
    this->Player->SetPosition(pPos);
}
