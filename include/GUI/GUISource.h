#pragma once
#include <iostream>
#include <TGUI/TGUI.hpp>
#include "Material.h"
#include "NeutronSet.h"
#include "DataManager.h"
#include "ControlRod.h"
#include "NeutronSet.h"

#include "GUIChemistry.h"
#include "GUIGeometry.h"


class GUISource
{

public:
	int y_source_panel;
	
	int height;

	int y_source_title;
	int y_type_source;
	int y_source_number_label;
	int y_source_coordinates;
	int y_source_automatic_button;
	int y_source_delay_label;
	int y_source_slider;
	int y_renormalization_label;
	int y_renormalization_slider;

	int y_neutrons_speed_label;
	int y_neutrons_speed_slider;
	int y_delayed_neutrons_proportion_label;
	int y_delayed_neutrons_proportion_slider;
	int y_delayed_neutrons_time_label;
	int y_delayed_neutrons_time_slider;

	int text_size;
	int text_size_mini;
	int x_widget;

	sf::Color text_color;


	GUISource(DataManager& dm);
	GUISource();

	void create_panel(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel, tgui::GuiSFML& gui);
	void update_y_positions(DataManager& dm);
	void delete_panel(tgui::GuiSFML& gui, tgui::Panel::Ptr panel);

	
	void create_source_title_label(DataManager& dm, tgui::Panel::Ptr panel);

	void create_type_source_buttons(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui);
	void create_source_number_label(DataManager& dm, tgui::Panel::Ptr panel);
	void create_sources_textbox(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui);

	void create_source_coordinates_label(DataManager& dm, tgui::Panel::Ptr panel);
	void create_x_source_textbox(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui);
	void create_y_source_textbox(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui);

	void create_automatic_sources_button(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui);
    void create_source_delay_label(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui);
    void create_source_slider(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui);
    void create_renormalization_label(DataManager& dm, tgui::Panel::Ptr panel);
    void create_renormalization_slider(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui);

	void reset_panel(DataManager& dm, tgui::GuiSFML& gui);

	void create_neutrons_speed_label(DataManager& dm, tgui::Panel::Ptr panel);
	void create_neutrons_speed_slider(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui, NeutronSet& neutron_set);

	void create_delayed_neutrons_proportion_label(DataManager& dm, tgui::Panel::Ptr panel);
	void create_delayed_neutrons_proportion_slider(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui);
	void create_delayed_neutron_time_label(DataManager& dm, tgui::Panel::Ptr panel);
	void create_delayed_neutron_time_slider(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui);
};

