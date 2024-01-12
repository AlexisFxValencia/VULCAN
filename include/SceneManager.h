#pragma once
#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "ControlRod.h"
#include "ParticlesSet.h"
#include "NeutronSet.h"
#include "DataManager.h"
#include "GUICreator.h"
#include "plot.h"

#include <vector>

using namespace std;

class SceneManager
{
public:
	sf::Text text;
	sf::Text text2;
	sf::Font font;
	sf::Color previous_color;

	bool mouseClicked;
	bool dragging;
	bool dragging_plot;
	float mouseX;
	float mouseY;
	sf::Vector2f decentering;
	sf::Vector2f decentering_plot;

	bool control_pressed;

	SceneManager(DataManager& dm);
	SceneManager();
	
	void move_control_rod(sf::Event event, ControlRod& control_rod, sf::RectangleShape& control_rod_shape, DataManager& dm);
	void select_volume(sf::Event event, DataManager& dm, GeometryCreator& geometry_creator, GUICreator& gui_creator);
	void move_selected_volume(sf::Event event, DataManager& dm);
	void move_volume_with_arrows(sf::Event event, DataManager& dm);

	void user_manages_volume(sf::Event event, DataManager& dm, GeometryCreator& geometry_creator, GUICreator& gui_creator, NeutronSet& neutron_set);
	void user_deletes_volume(sf::Event event, DataManager& dm);

	void drag_volume(sf::Event event, DataManager& dm, GUICreator& gui_creator);
	void drag_plot(sf::Event event, DataManager& dm, sf::plot::Plot& plot);

	void select_several_volumes(sf::Event event, DataManager& dm, GUICreator& gui_creator);

	void delete_pop_up_menus(sf::Event event, DataManager& dm, GUICreator& gui_creator);
};

