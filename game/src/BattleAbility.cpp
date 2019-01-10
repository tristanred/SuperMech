#include "BattleAbility.h"

#include "Mech.h"
#include <math.h>

BattleAbility::BattleAbility(MechFrame* owner)
{
    this->Owner = owner;

    this->Name = "";
    this->Description = "";
}

BattleAbility::~BattleAbility()
{
}

StrikeAbility::StrikeAbility(MechFrame* owner)
    : BattleAbility(owner)
{
}

void StrikeAbility::UseAbility(MechFrame* target)
{
    int damageTotal = ceil(this->Owner->AttackPoints * 1.5);
    
    target->CurrentHealth -= damageTotal;
}
