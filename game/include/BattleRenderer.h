#pragma once

#include "Game/Game.h"

// To forward declare :
#include "Battle.h"
#include "BattleAbility.h"
#include "BattleActions.h"
#include "BattleEffect.h"
#include "Mech.h"
#include "Parts.h"
#include "Events/Event.h"

class BattleRenderer : public GameObject
{
public:
    ASprite* playerSprite;
    ASprite* opponentSprite;

    ASprite* attackButton;

    BattleRenderer(Battle* battle);
    ~BattleRenderer();


    void Setup(GameModule* currentModule) override;


    void Update(unsigned int deltaTime) override;
    void Draw() override;

private:
    // Event Handles
    
};
