#pragma once

#include <iostream>
#include <TGUI/TGUI.hpp>
#include "Material.h"
#include "NeutronSet.h"
#include "DataManager.h"
#include "ControlRod.h"



class GUIChemistry
{
public:
	int x_widget;

	int y_chemistry_panel;
	
	int height;

	int y_title_label;
	int y_capture_label;
	int y_capture_slider;
	int y_scattering_label;
	int y_scattering_slider;
	int y_fission_label;
	int y_fission_slider;
	int y_density_label;
	int y_density_slider;
	int y_nubar;
	int y_nubar_slider;
	int y_material_buckling;

	sf::Color text_color;

	GUIChemistry();
	GUIChemistry(DataManager& dm);

	void create_panel(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui);
	void update_y_positions(DataManager& dm);
	void delete_panel(tgui::GuiSFML& gui, tgui::Panel::Ptr panel);	
	void reset_panel(DataManager& dm, tgui::GuiSFML& gui);

	void create_title(DataManager& dm, tgui::Panel::Ptr panel);
	void create_capture_label(DataManager& dm, tgui::Panel::Ptr panel);
	void create_capture_slider(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML &gui);
	void create_scattering_label(DataManager& dm, tgui::Panel::Ptr panel);
	void create_scattering_slider(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML &gui);
	void create_fission_label(DataManager& dm, tgui::Panel::Ptr panel);
    void create_fission_slider(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui);
    void create_density_label(DataManager& dm, tgui::Panel::Ptr panel);
    void create_density_slider(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui);
    void create_nubar_label(DataManager& dm, tgui::Panel::Ptr panel);
    void create_nubar_slider(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui);
	void create_material_buckling_label(DataManager& dm, tgui::Panel::Ptr panel);
	void update_material_buckling(DataManager& dm, tgui::GuiSFML& gui);

};

