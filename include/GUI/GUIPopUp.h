#pragma once
#include <iostream>
#include <TGUI/TGUI.hpp>
#include "Material.h"
#include "NeutronSet.h"
#include "DataManager.h"
#include "ControlRod.h"
class GUIPopUp
{
public:
		tgui::ListBox::Ptr modify_volume_menu;
		float x_shape;
		float y_shape;
		int user_shape_counter;
		int volume_to_modify_index;

		GUIPopUp();

		void create_new_volume_menu(DataManager& dm, int& x_popup, int& y_popup, NeutronSet& neutron_set, tgui::GuiSFML& gui);
		//void create_shape(DataManager& dm, tgui::GuiSFML& gui);
		void create_modify_volume_menu(DataManager& dm, NeutronSet& neutron_set, int& x_popup, int& y_popup, int& volume_index, tgui::GuiSFML& gui);
		void copy_shape(DataManager& dm, Volume& volume);
		void create_disk(DataManager& dm, tgui::GuiSFML& gui);
		void create_rectangle(DataManager& dm, tgui::GuiSFML& gui);

		
		void create_neutron(DataManager& dm, NeutronSet& neutron_set);
		void delete_previous_menus(tgui::GuiSFML& gui);


};

