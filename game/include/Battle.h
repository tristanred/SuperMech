#pragma once

#include "Parts.h"
#include "Mech.h"
#include "BattleActions.h"
#include "BattleAbility.h"

#include "Events/Event.h"

#include <queue>
#include <tuple>

class MechAbility;
class MechItem;

// Battle playing and turn sequences
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

/**
 * This class is used to play out a battle. Implemented as a state machine with
 * latches to wait on the player to make an action. The battle has two
 * states components. The Battle State is the state of the battle such as
 * "battle over" or "battle ongoing" or maybe "battle interrupted".
 *
 * A battle plays out over a sequence of turns, each turn plays out using the
 * Turn State field. Each turn goes through the states in order and when a
 * turn is over we evaluate if the battle has ended. If yes, the turn is over
 * and the Battle State will switch to "Ended" and then the game can decide
 * what to do next.
 */
class Battle
{
public:
    Battle(MechFrame* a, MechFrame* b);
    ~Battle();

    enum battle_state bs;
    enum turn_state ts;

    int turnNumber = 0;

    // Action latches
    bool playerActionDone;

    void Update();
    void Update_Turn();
    
    void SwitchBattleState(battle_state newState);
    void SwitchTurnState(turn_state newState);
    
    std::queue<std::tuple<battle_action_types, void*>> q;

    MechFrame* Player;
    MechFrame* Opponent;

    // Player options
    void Attack(ActionAttack* ability);

    // Checking methods
    bool IsWaitingForPlayer();
    bool IsBattleOver();
    
    // Battle phases
    void StartTurn();

    void WaitForPlayerAction(); // Push action in the q

    void DoOpponentChoice();

    void EndTurn(); // Applies effects

    // Events
    Event<battle_state> OnBattleStateChanged;
    Event<turn_state> OnTurnStateChanged;
    Event<std::tuple<battle_action_types, void*>> OnActionResolved;
};
