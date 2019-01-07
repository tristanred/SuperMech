#include "Battle.h"

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
            std::tuple<move_types, void*> nextAction = this->q.front();
            this->q.pop();
            
            while(this->q.empty() == false)
            {
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
                
                nextAction = this->q.front();
                this->q.pop();
            }
            
            break;
        }
        case TS_END:
        {
            // Check if the turn has won or loss the battle
            break;
        }
    }
}

void Battle::Attack(AbilityAttack* ability)
{
    if(this->ts == TS_WAIT_FOR_PLAYER)
    {
        this->playerActionDone = true;
        std::tuple<move_types, void*> action = std::make_tuple(MT_ATTACK, ability);

        this->q.push(action);
    }
}

void Battle::DoOpponentChoice()
{

}
