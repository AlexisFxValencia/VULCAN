#pragma once
#include <string>
using namespace std;
#include "Particle.h"
#include <SFML/Graphics.hpp>

#include <iostream>
//#include <vector> 
#include "Material.h"
#include "GeometryCreator.h"
#include "DataManager.h"
#include <TGUI/TGUI.hpp>

#include <numeric>
#include <cmath>
#include <omp.h>


class NeutronSet {
public:
    int x_canvas;
    int y_canvas;
    std::vector<Particle> neutrons_array;
    std::vector<Particle> fissioned_neutrons_vector;
    int mass_neutron;
    float r_neutron;
    bool reflexions_activated;
    
    int nb_neutrons_old;
    float previous_time;
    float ppcm;
    float keff;
    float averaged_keff;
    float sigma; 
    std::vector<float> batch_keff_vector;

    int nb_fission;
    int nb_fissioned_neutrons;
    int nb_fled_neutrons;
    int nb_captured_neutrons;

    float x_min;
    float x_max;
    float y_min;
    float y_max;

    int counter;

    int nb_alive_neutrons;

    NeutronSet();
    NeutronSet(DataManager& dm);

    void fill_neutrons_vector(DataManager& dm);
    void deactivate_neutrons_vector();
    void add_source_neutrons(DataManager& dm);
    int add_one_active_neutron(float x, float y, DataManager& dm);

    void compute_neutron_lives(DataManager& dm);
    void take_one_step(int i);
    void rebound_on_walls(int i, DataManager& dm);
    void remove_fled_neutrons(int i);
    
    void compute_reactions(int i, DataManager& dm);
    void compute_one_reaction(Volume volume, Particle& neutron, int i, DataManager& dm);
    void scatter(int i, Material material, DataManager& dm);
    void capture(int i);
    void fission(int i, Material& material, DataManager& dm);
    int compute_nu(Material& material);
    float sort_free_path(Material& material);
    void check_delayed_neutrons_activation(DataManager& dm);
    void choose_if_delayed_neutron(DataManager& dm, Particle& neutron);
    
    int search_container_volume(DataManager& dm, Particle& neutron);
    void show_neutrons_array();
    int get_nb_alive_neutrons();
    void restart_clocks();
    void update_wall_positions(DataManager& dm);


    void renormalize(DataManager& dm, int nb_source, bool activated, int elapsed_seconds, int renormalization_delay);    
    void generate_new_batch(DataManager& dm);
    void compute_keff(DataManager& dm);
    void reset_keff_counters();
    void compute_averaged_keff();
    void compute_sigma();

    

};
