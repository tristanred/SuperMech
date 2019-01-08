#include "Battle.h"

#include <stdio.h>

Battle::Battle(MechFrame* a, MechFrame* b)
{
    this->Player = a;
    this->Opponent = b;

    this->bs = BS_START;
    this->ts = TS_TURN_START;
}

Battle::~Battle()
{

}

void Battle::Update()
{
    switch(bs)
    {
        case BS_START:
        {
            this->bs = BS_ONGOING;
            break;
        }
        case BS_ONGOING:
        {
            this->Update_Turn();

            break;
        }
        case BS_WIN:
        {
            break;
        }
        case BS_LOSS:
        {
            break;
        }
        case BS_END:
        {
            break;
        }
    }
}

void Battle::Update_Turn()
{
    switch(ts)
    {
        case TS_TURN_START:
        {
            // Check if there is anything to do before the turn start
            playerActionDone = false;

            this->ts = TS_WAIT_FOR_PLAYER;

            break;
        }
        case TS_WAIT_FOR_PLAYER:
        {
            // Stay hung there and when we call a player action we switch out of
            // that this state.
            if(playerActionDone)
            {
                this->ts = TS_OPPONENT_DECIDE;
                playerActionDone = false;
            }

            break;
        }
        case TS_OPPONENT_DECIDE:
        {
            // Play out the opponent turn.
            this->DoOpponentChoice();
            this->ts = TS_RESOLVE;

            break;
        }
        case TS_RESOLVE:
        {
            if(this->q.empty())
            {
                // No actions ?
                this->ts = TS_END;
                return;
            }
            
            // Do stuff, apply effects
            std::tuple<move_types, void*> nextAction;
            
            while(this->q.empty() == false)
            {
                nextAction = this->q.front();
                this->q.pop();
                switch(std::get<0>(nextAction))
                {
                    case MT_ATTACK:
                    {
                        AbilityAttack* ability = (AbilityAttack*)std::get<1>(nextAction);
                        ability->target->Health -= ability->owner->Attack;
                        
                        break;
                    }
                    case MT_HEAL:
                    {
                        break;
                    }
                    case MT_FLEE:
                    {
                        break;
                    }
                    case MT_ITEM:
                    {
                        break;
                    }
                }
            }
            
            break;
        }
        case TS_END:
        {
            // Check if the turn has won or loss the battle

            if(this->Player->Health == 0)
            {
                // Loss
                this->bs = BS_LOSS;

                printf("Battle lost !");
            }
            else if(this->Opponent->Health == 0)
            {
                // Win
                this->bs = BS_WIN;

                printf("Battle won !");
            }

            break;
        }
    }
}

void Battle::Attack(AbilityAttack* ability)
{
    if(this->ts == TS_WAIT_FOR_PLAYER)
    {
        this->playerActionDone = true;

        auto defaultAbility = new AbilityAttack();
        defaultAbility->ability = NULL;
        defaultAbility->owner = Player;
        defaultAbility->target = Opponent;
        defaultAbility->type = MT_ATTACK;

        std::tuple<move_types, void*> action = std::make_tuple(MT_ATTACK, defaultAbility);

        this->q.push(action);
    }
}

bool Battle::IsWaitingForPlayer()
{
    return this->ts == TS_WAIT_FOR_PLAYER;
}

void Battle::DoOpponentChoice()
{

}

bool Battle::IsBattleOver()
{
    return this->bs == BS_WIN || this->bs == BS_LOSS;
}
