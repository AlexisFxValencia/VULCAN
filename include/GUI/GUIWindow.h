#pragma once
#include <iostream>
#include <TGUI/TGUI.hpp>
#include "Material.h"
#include "NeutronSet.h"
#include "DataManager.h"
#include "ControlRod.h"

class GUIWindow
{
public:
    GUIWindow();

    void display_credits_window(DataManager& dm);
    void display_help_window(DataManager& dm);
    void display_max_nb_neutrons_window(DataManager& dm);

    
};

