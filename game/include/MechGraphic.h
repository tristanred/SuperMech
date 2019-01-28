#pragma once

#include "Game/Game.h"

/**
 * Data class containing graphical properties for a Mech. This is used to
 * separate mech logic and properties for textures and asset loading.
 *
 */
class MechGraphicSettings
{
public:
    MechGraphicSettings();
    ~MechGraphicSettings();

    std::string IdleAnimation;
    std::string AttackAnimation;
};
