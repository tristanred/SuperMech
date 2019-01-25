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
            this->SwitchBattleState(BS_ONGOING);
            break;
        }
        case BS_ONGOING:
        {
            this->Update_Turn();

            break;
        }
        case BS_WIN:
        {
            // Award xp to the player

            this->SwitchBattleState(BS_END);

            break;
        }
        case BS_LOSS:
        {
            // Do some other stuff

            this->SwitchBattleState(BS_END);

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

            this->SwitchTurnState(TS_WAIT_FOR_PLAYER);

            break;
        }
        case TS_WAIT_FOR_PLAYER:
        {
            // Stay hung there and when we call a player action we switch out of
            // that this state.
            if(playerActionDone)
            {
                this->SwitchTurnState(TS_OPPONENT_DECIDE);
                playerActionDone = false;
            }

            break;
        }
        case TS_OPPONENT_DECIDE:
        {
            // Play out the opponent turn.
            this->DoOpponentChoice();
            this->SwitchTurnState(TS_RESOLVE);

            break;
        }
        case TS_RESOLVE:
        {
            if(this->q.empty())
            {
                // No actions ?
                this->SwitchTurnState(TS_END);
                return;
            }

            // Do stuff, apply effects
            std::tuple<battle_action_types, void*> nextAction;

            while(this->q.empty() == false)
            {
                nextAction = this->q.front();
                this->q.pop();
                switch(std::get<0>(nextAction))
                {
                    case BA_ATTACK:
                    {
                        ActionAttack* ability = (ActionAttack*)std::get<1>(nextAction);
                        ability->ability->UseAbility(this->Opponent);

                        break;
                    }
                    case BA_FLEE:
                    {
                        break;
                    }
                    case BA_ITEM:
                    {
                        break;
                    }
                }
                
                this->OnActionResolved.Dispatch(nextAction);
            }

            break;
        }
        case TS_END:
        {
            // Check if the turn has won or loss the battle
            this->turnNumber++;

            if(this->Player->CurrentHealth <= 0)
            {
                // Loss
                this->SwitchBattleState(BS_LOSS);

                printf("Battle lost !\n");
            }
            else if(this->Opponent->CurrentHealth <= 0)
            {
                // Win
                this->SwitchBattleState(BS_WIN);

                printf("Battle won !\n");
            }
            else
            {
                // Go back to start a new turn.
                this->SwitchTurnState(TS_TURN_START);
            }

            break;
        }
    }
}

void Battle::SwitchBattleState(battle_state newState)
{
    this->bs = newState;
    this->OnBattleStateChanged.Dispatch(this->bs);
}

void Battle::SwitchTurnState(turn_state newState)
{
    this->ts = newState;
    this->OnTurnStateChanged.Dispatch(this->ts);
}

void Battle::Attack(ActionAttack* ability)
{
    if(this->ts == TS_WAIT_FOR_PLAYER)
    {
        this->playerActionDone = true;

        auto defaultAbility = new ActionAttack();
        defaultAbility->ability = Player->MechAbilities->First();
        defaultAbility->owner = Player;
        defaultAbility->target = Opponent;
        defaultAbility->type = BA_ATTACK;

        std::tuple<battle_action_types, void*> action = std::make_tuple(BA_ATTACK, defaultAbility);

        this->q.push(action);
    }
}

bool Battle::IsWaitingForPlayer()
{
    return this->ts == TS_WAIT_FOR_PLAYER;
}

void Battle::DoOpponentChoice()
{
    // Do nothing
}

bool Battle::IsBattleOver()
{
    return this->bs == BS_WIN || this->bs == BS_LOSS;
}
