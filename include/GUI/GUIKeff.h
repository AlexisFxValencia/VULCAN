#pragma once
#include <TGUI/TGUI.hpp>
#include "DataManager.h"
#include "NeutronSet.h"
class GUIKeff
{
	public :
		GUIKeff();
		GUIKeff(DataManager& dm);
		int y_keff_panel;
		int x_widget;	
		int text_size_mini;

		int height;

		int y_batch;
		int y_keff;
		int y_last_keff;
		int y_averaged_keff;
		int y_sigma;
		int y_keff_automatic_button;		

		void create_panel(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel, tgui::GuiSFML& gui);
		void delete_panel(tgui::GuiSFML& gui, tgui::Panel::Ptr panel);
		void reset_panel(DataManager& dm, tgui::GuiSFML& gui);
		void create_batch_label(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel);
		void create_keff_label(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel);
		void create_last_keff_label(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel);
		void create_averaged_keff_label(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel);
		void create_sigma_label(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel);
		void create_automatic_keff_button(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel, tgui::GuiSFML& gui);

		void update_keff(DataManager& dm, NeutronSet& neutron_set, tgui::GuiSFML& gui);
		void update_all(DataManager& dm, NeutronSet& neutron_set, tgui::GuiSFML& gui);
};

