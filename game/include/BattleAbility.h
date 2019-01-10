#pragma once

#include <string>
#include <string.h>

class MechFrame;

/**
 * Abilities are actions that target an opponent (offence) or can target an ally
 * (defensive). All abilities have a target (or many targets, only 1 for now).
 * The target is determine when the time comes to use it.
 *
 * The class is meant to be overridden for complex effects.
 *
 * Below is a sample implementation that can be used for dummy testing.
 */
class BattleAbility
{
public:
    BattleAbility(MechFrame* owner);
    virtual ~BattleAbility();

    std::string Name;
    std::string Description;

    virtual void UseAbility(MechFrame* target) = 0;

protected:
    MechFrame* Owner;
};

class StrikeAbility : public BattleAbility
{
public:
    StrikeAbility(MechFrame* owner);
    void UseAbility(MechFrame* target) override;
};
