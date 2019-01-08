#include <stdio.h>

#include <GameEngine.h>
#include "Battle.h"
#include "Mech.h"
#include "Parts.h"

int main(int argc, char** argv)
{
    GameEngine* eng = new GameEngine();
    eng->Initialize();
    
    MechFrame* player = CreateDummy();
    MechFrame* opp = CreateDummy();
    
    Battle* battle = new Battle(player, opp);
    
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

    printf("Super Mech !");

    return 0;
}
