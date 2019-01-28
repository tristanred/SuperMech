#include "BattleRenderer.h"

#include "GameModule.h"

BattleRenderer::BattleRenderer(Battle* battle)
    : GameObject()
{
    auto x = this->Owner->CreateTexture("jump.png");
    
    this->playerSprite = NULL;
    this->opponentSprite = NULL;

    this->attackButton = NULL;
}

BattleRenderer::~BattleRenderer()
{
    this->Owner->DestroyObject(this->playerSprite);
    this->Owner->DestroyObject(this->opponentSprite);
    this->Owner->DestroyObject(this->attackButton);
}

void BattleRenderer::Setup(GameModule* currentModule)
{
    this->playerSprite = this->Owner->CreateSprite();
    this->playerSprite->SetTexture("player.png");

    this->opponentSprite = this->Owner->CreateSprite();
    this->opponentSprite->SetTexture("opponent.png");
}

void BattleRenderer::Update(unsigned int deltaTime)
{

}

void BattleRenderer::Draw()
{

}
