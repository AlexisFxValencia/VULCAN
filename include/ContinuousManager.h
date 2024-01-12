#pragma once
#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "Particle.h"
#include "ControlRod.h"
#include "GeometryCreator.h"
#include "NeutronSet.h"
#include "SceneManager.h"
#include "GUICreator.h"

#include <SFML/System.hpp>
#include <cstdio> // popen
#include <cstring> // memset
#include "plot.h"
#include "Detector.h"
#include "DiscreteManager.h"

class ContinuousManager
{
public:
    sf::RenderWindow window;
    SceneManager scene_manager;
    NeutronSet neutron_set;
    GeometryCreator geometry_creator;
    ControlRod control_rod;
    sf::RectangleShape control_rod_shape;    
    sf::Clock clock;

    sf::plot::Plot plot_;
    Detector detector;
    sf::plot::Plot detector_plot;
    int detector_index = -1;
    int time_memorized_1;
    int time_memorized_2;

	ContinuousManager(DataManager& dm);
    void draw_neutrons(DataManager& dm);
    void draw_volumes(DataManager& dm);
    void draw_one_volume(DataManager& dm, Volume volume);
    void draw_legend(DataManager& dm);
    void draw_max_nb_neutrons_message(DataManager& dm);
    void draw_walls(DataManager& dm);

    void initialize_graph(DataManager& dm);
    void update_graph_curve(DataManager& dm);
    void initialize_detector_graph(DataManager& dm);
    void update_detector_graph_curve();
    void update_graphics(DataManager& dm, int time_ms);
    void draw_components(GUICreator& gui_creator, DataManager& dm);

    void continuous_main(DataManager& dm);

    //void pause_max_neutrons(DataManager& dm, NeutronSet& neutron_set, GUICreator& gui_creator);
    void generate_sources(DataManager& dm, int time, int delay, NeutronSet& neutron_set, GUICreator& gui_creator);
    void write_keff(ofstream& myfile);

};

