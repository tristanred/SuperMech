#include <stdio.h>

#include <GameEngine.h>
#include "Battle.h"
#include "Mech.h"
#include "Parts.h"
#include <libtech/queue.h>
#include <tuple>

#include "Modules/MapGameModule.h"

void CbActionResolved(std::tuple<battle_action_types, void*> param)
{
    printf("Action Resolved\n");
}

void CbTurnChanged(turn_state param)
{
    printf("Turn state changed to %i\n", param);
}

void CbBattleChanged(battle_state param)
{
    printf("Battle state changed to %i\n", param);
}

int main(int argc, char** argv)
{
    GameEngine* eng = new GameEngine();
    eng->Initialize();

    GameModule* mod = eng->CreateModule<MapGameModule>();
    eng->Play();

    return 0;


    auto test = eng->CreateTexture("jump.png");

    MechFrame* player = CreateDummy();
    MechFrame* opp = CreateDummy();

    Battle* battle = new Battle(player, opp);

    battle->OnTurnStateChanged.Listen(&CbTurnChanged);
    battle->OnBattleStateChanged.Listen(&CbBattleChanged);
    battle->OnActionResolved.Listen(&CbActionResolved);

    while(true)
    {
        battle->Update();

        if(battle->IsWaitingForPlayer())
        {
            battle->Attack(NULL);
        }

        if(battle->IsBattleOver())
        {
            break;
        }
    }

    //eng->Play();

    printf("Super Mech !\n");

    return 0;
}
