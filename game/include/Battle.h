#pragma once

#include "Parts.h"
#include "Mech.h"

#include <queue>
#include <tuple>

class MechAbility;
class MechItem;

enum move_types
{
    MT_ATTACK,
    MT_HEAL,
    MT_FLEE,
    MT_ITEM
};

struct AbilityAttack
{
    move_types type = MT_ATTACK;

    MechAbility* ability;

    MechFrame* owner;
    MechFrame* target;
};

struct AbilityHeal
{
    move_types type = MT_HEAL;

    MechAbility* ability;

    MechFrame* owner;
    MechFrame* target;
};

struct AbilityFlee
{
    move_types type = MT_FLEE;
};

struct AbilityItem
{
    move_types type = MT_ITEM;

    MechItem* item;

    MechFrame* target;
};

/*

Move Types :
USE_ATTACK [Ability, Target]    ----v
REGEN_HEALTH [Ability, Target]  --> Could be the same
FLEE
USE_ITEM [Item, Target]


*/

enum battle_state
{
    BS_START,
    BS_ONGOING,
    BS_WIN,
    BS_LOSS,
    BS_END
};

enum turn_state
{
    TS_TURN_START,
    TS_WAIT_FOR_PLAYER,
    TS_OPPONENT_DECIDE,
    TS_RESOLVE,
    TS_END
};

class Battle
{
public:
    Battle(MechFrame* a, MechFrame* b);
    ~Battle();

    enum battle_state bs;
    enum turn_state ts;

    // Action latches
    bool playerActionDone;

    void Update();
    void Update_Turn();

    std::queue<std::tuple<move_types, void*>> q;

    MechFrame* Player;
    MechFrame* Opponent;

    // Player options
    void Attack(AbilityAttack* ability);
    
    // Checking methods
    bool IsWaitingForPlayer();
    bool IsBattleOver();


    // Battle phases
    void StartTurn();

    void WaitForPlayerAction(); // Push action in the q

    void DoOpponentChoice();

    void EndTurn(); // Applies effects
};
