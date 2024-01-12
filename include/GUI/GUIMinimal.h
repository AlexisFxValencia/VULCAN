#pragma once
#include <iostream>
#include <TGUI/TGUI.hpp>
#include "Material.h"
#include "NeutronSet.h"
#include "DataManager.h"
#include "ControlRod.h"

class GUIMinimal
{
public:
	//int y_reset;
	int x_widget;
	int y_minimal_panel;	
	
	int text_size_mini;

	int y_nb_neutrons;	
	int y_source_button;
	int y_pause_button;	
	int y_reflexion_button;	
	
	int height;
	
	bool simulationPaused;

	GUIMinimal();
	GUIMinimal(DataManager& dm);
	void update_y_positions(DataManager& dm);
	void create_panel(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel, tgui::GuiSFML& gui);
	void delete_panel(tgui::GuiSFML& gui, tgui::Panel::Ptr panel);
	void reset_panel(DataManager& dm, tgui::GuiSFML& gui);

	void create_nb_neutrons_label(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel);
    void create_sources_button(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel);
    void create_pause_button(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui);
    void create_reflexion_button(DataManager& dm, tgui::GuiSFML& gui, tgui::Panel::Ptr panel);
	void update_nb_neutrons(DataManager& dm, NeutronSet& neutron_set, tgui::GuiSFML& gui);


};

