#pragma once

#include <iostream>
#include <TGUI/TGUI.hpp>
#include "Material.h"
#include "NeutronSet.h"
#include "DataManager.h"
#include "ControlRod.h"

#include "GUIMinimal.h"
#include "GUIKeff.h"
#include "GUISource.h"
#include "GUIGeometry.h"
#include "GUIChemistry.h"
#include "GUIPopUp.h"

#include "GUIWindow.h"

#include <filesystem>

#include "ParticlesSet.h"
#include "DiscreteHydrogensSet.h"
#include "DiscreteNuclidesSet.h"
#include "DiscreteSpentNuclidesSet.h"


#include <sys/stat.h>




class GUICreator
{
public:
	GUIGeometry gui_geometry;
	GUIChemistry gui_chemistry;
	GUISource gui_source;
	GUIMinimal gui_minimal;
	GUIWindow gui_window;
	GUIPopUp gui_popup; 
	GUIKeff gui_keff;
	
	tgui::GuiSFML gui;
	tgui::ScrollablePanel::Ptr panel;
	tgui::GuiSFML loading_gui;


	int x_widget;
	string present_input_file;	
	bool fullscreen;
	int y_reset;
	
	GUICreator();
	GUICreator(sf::RenderWindow& window, DataManager& dm);

	void create_gui(DataManager& dm, sf::RenderWindow& window, NeutronSet& neutron_set, ControlRod& control_rod, sf::RectangleShape& control_rod_shape);
	void create_panels(DataManager& dm, NeutronSet& neutron_set);
	void create_menu(DataManager& dm, NeutronSet& neutron_set, ControlRod& control_rod, sf::RectangleShape& control_rod_shape);
	
	void create_menu_discrete(DataManager& dm, ParticlesSet& particle_set, DiscreteHydrogensSet& hydrogen_set, DiscreteNuclidesSet& nuclide_set, DiscreteSpentNuclidesSet& spent_nuclide_set, GeometryCreator& geometry_creator);
	void reset_discrete_input(DataManager& dm, ParticlesSet& particles_set, DiscreteHydrogensSet& hydrogen_set, DiscreteNuclidesSet& nuclide_set, DiscreteSpentNuclidesSet& spent_nuclide_set, GeometryCreator& geometry_creator, string input_name);

	void create_view_menu(DataManager& dm, NeutronSet& neutron_set, tgui::MenuBar::Ptr menu);
	void create_simulation_menu(DataManager& dm, NeutronSet& neutron_set, tgui::MenuBar::Ptr menu, ControlRod& control_rod, sf::RectangleShape& control_rod_shape);
	void create_loading_menu(DataManager& dm, NeutronSet& neutron_set, tgui::MenuBar::Ptr menu, ControlRod& control_rod, sf::RectangleShape& control_rod_shape);
	void create_help_menu(DataManager& dm, tgui::MenuBar::Ptr menu);

	void create_reset_button(DataManager& dm, NeutronSet& neutron_set, ControlRod& control_rod, sf::RectangleShape& control_rod_shape);
	void reset_gui(DataManager& dm);
	void reset_input(DataManager& dm, NeutronSet& neutron_set, ControlRod& control_rod, sf::RectangleShape& control_rod_shape, string input_name);

	inline bool file_exists(const std::string& name);
	void display_loading_window(DataManager& dm, NeutronSet& neutron_set, ControlRod& control_rod, sf::RectangleShape& control_rod_shape);

};

