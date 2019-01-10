#pragma once


/*
 *  Battle actions are the action you can do each turn like attacking, playing
 *  an item, fleeing, etc. New classes can be added as needed and they all need
 *  an entry in the battle_action_types so that the data can be converted to the
 *  correct type.
 *
 * Abilities such as Attack have an additional "Ability" field that contains
 * the object representing what the ability does.
*/

class BattleAbility;
class MechItem;
class MechFrame;

enum battle_action_types
{
    BA_ATTACK,
    BA_FLEE,
    BA_ITEM
};

struct ActionAttack
{
    battle_action_types type = BA_ATTACK;

    BattleAbility* ability;

    MechFrame* owner;
    MechFrame* target;
};

struct ActionFlee
{
    battle_action_types type = BA_FLEE;
};

struct ActionItem
{
    battle_action_types type = BA_ITEM;

    MechItem* item;

    MechFrame* target;
};
