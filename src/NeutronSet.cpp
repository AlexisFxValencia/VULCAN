#include "NeutronSet.h"

NeutronSet::NeutronSet(DataManager& dm) {
    this->x_canvas = dm.x_canvas;
    this->y_canvas = dm.y_canvas;

    mass_neutron = dm.mass_neutron;
    r_neutron = dm.r_neutron;
    reflexions_activated = dm.reflexions_activated;
    
    nb_neutrons_old = dm.nb_source;
    previous_time = 0;
    ppcm = dm.ppcm;

    nb_fissioned_neutrons = 0;
    nb_fled_neutrons = 0;
    nb_captured_neutrons = 0;
    nb_fission = 0;

    update_wall_positions(dm);
    keff = 0;
    averaged_keff = 0;
    sigma = 0.0;
    counter = 0;

    nb_alive_neutrons = 0;

    fill_neutrons_vector(dm);
}

NeutronSet::NeutronSet() {
}


void NeutronSet::fill_neutrons_vector(DataManager& dm) {
    Particle neutron = Particle(10, 10, 7.0, -8.0, r_neutron, mass_neutron, x_min, x_max, y_min, y_max);
    for (int i = 0; i < dm.max_nb_neutrons; i++) {
        neutrons_array.push_back(neutron);
    }
}

void NeutronSet::deactivate_neutrons_vector() {
    for (int i = 0; i < neutrons_array.size(); i++) {
        neutrons_array[i].is_source = false;
        neutrons_array[i].is_active = true;
        neutrons_array[i].free_path = 1.0;
        neutrons_array[i].containter_index = -1;
        neutrons_array[i].is_alive = false;
    }
    nb_alive_neutrons = 0;
}

void NeutronSet::add_source_neutrons(DataManager& dm) {
    cout << "Adding " << dm.nb_source << " source neutrons to the simulation" << endl;
    list<int> fissiles_list = dm.find_fissile_volumes();
    for (int i = 0; i < dm.nb_source; i++) {
        float x = 0;
        float y = 0;
        if (dm.type_source == "punctual") {
            x = dm.x_source;
            y = dm.y_source;
        }
        else if (dm.type_source == "uniform") {
            neutrons_array[i].set_random_position();
            x = neutrons_array[i].x;
            y = neutrons_array[i].y;
        }
        else if (dm.type_source == "fissile") {
            for (auto index : fissiles_list) {
                if (dm.volu_array[index].type == "rectangle") {
                    float alea_1 = (float)rand() / RAND_MAX;
                    x = alea_1 * dm.volu_array[index].param1 + (dm.volu_array[index].x - (dm.volu_array[index].param1 / 2));
                    float alea_2 = (float)rand() / RAND_MAX;
                    y = alea_2 * dm.volu_array[index].param2 + (dm.volu_array[index].y - (dm.volu_array[index].param2 / 2));
                }
                else if (dm.volu_array[index].type == "disk") {
                    float alea = (float)rand() / RAND_MAX;
                    float theta = alea * 2 * 3.14159265358979323846;
                    alea = (float)rand() / RAND_MAX;
                    float radius = alea * dm.volu_array[index].param1;
                    x = radius * cos(theta) + dm.volu_array[index].x;
                    y = radius * sin(theta) + dm.volu_array[index].y;
                }                
            }
        }
        add_one_active_neutron(x, y, dm);       
    }
}

int NeutronSet::add_one_active_neutron(float x, float y, DataManager& dm) {
    int index = -1;
    for (int i = 0; i < neutrons_array.size(); i++) {
        if (neutrons_array[i].is_alive == false) {
            index = i;
            neutrons_array[i].x = x;
            neutrons_array[i].y = y;
            neutrons_array[i].set_last_position();
            neutrons_array[i].set_random_velocity(dm.neutron_speed_magnitude);
            neutrons_array[i].set_as_source();
            neutrons_array[i].is_alive = true;
            neutrons_array[i].clock.restart();
            nb_alive_neutrons++;  
            //cout << "really adding a neutron" << endl;
            return index;
        }        
    }
    return index;
}


void NeutronSet::compute_neutron_lives(DataManager& dm) {
    //double t_start = omp_get_wtime();
    //omp_set_num_threads(1);
    
    #pragma omp parallel 
    {   
        #pragma omp for schedule(static, 200)
        for (int i = 0; i < neutrons_array.size(); i++) {
            if (neutrons_array[i].is_alive) {
                take_one_step(i);
                rebound_on_walls(i, dm);
                remove_fled_neutrons(i);
                compute_reactions(i, dm);
            }
        }
    }

    //double t_end = omp_get_wtime();
    //cout << "time spent for a full cycle of " << nb_alive_neutrons << " neutrons : " << t_end - t_start << endl;
}

void NeutronSet::take_one_step(int i) {   
    if (neutrons_array[i].is_active) {
        neutrons_array[i].take_one_step();
    }
    else {
        neutrons_array[i].clock.restart();
    }
}

void NeutronSet::rebound_on_walls(int i, DataManager& dm) {
    if (dm.reflexions_activated) {
        neutrons_array[i].rebound_on_walls();
    }
}

void NeutronSet::remove_fled_neutrons(int i) {
    float x = neutrons_array[i].x;
    float y = neutrons_array[i].y;
    if (x > x_max + r_neutron || x < x_min - r_neutron || y > y_max + r_neutron || y < y_min - r_neutron) {
        if (neutrons_array[i].is_source) {
            nb_fled_neutrons++;
            neutrons_array[i].is_source = false;
        }
        neutrons_array[i].is_alive = false;
        nb_alive_neutrons--;
    }
}

void NeutronSet::compute_reactions(int i, DataManager& dm) { 
    if (neutrons_array[i].is_active) {
        int container_index = search_container_volume(dm, neutrons_array[i]);
        if (container_index != -1 && container_index != neutrons_array[i].containter_index) {
            neutrons_array[i].free_path = sort_free_path(dm.volu_array[container_index].material);
            neutrons_array[i].containter_index = container_index;
        }
        if (container_index != -1) {
            compute_one_reaction(dm.volu_array[container_index], neutrons_array[i], i, dm);
        }
    }
}

int NeutronSet::search_container_volume(DataManager& dm, Particle& neutron) {
    int priority = -1;
    int container_index = -1;
    for (int v = 0; v < dm.volu_array.size(); v++) {
        if (dm.volu_array[v].contains(neutron)) {
            if (dm.volu_array[v].priority > priority) {
                priority = dm.volu_array[v].priority;
                container_index = v;
            }
        }
    }
    return container_index;
}

void NeutronSet::compute_one_reaction(Volume volume, Particle& neutron, int i, DataManager& dm) {
    float distance_to_last_reaction_squared = pow(neutron.x - neutron.x_old, 2) + pow(neutron.y - neutron.y_old, 2);

    if (distance_to_last_reaction_squared >= pow(neutron.free_path, 2)) { //cm
        neutron.set_last_position();
        float proba_s = volume.material.sigma_s_macro / volume.material.sigma_total_macro;
        float proba_c = volume.material.sigma_c_macro / volume.material.sigma_total_macro;
        float proba_f = volume.material.sigma_f_macro / volume.material.sigma_total_macro;

        float alea = (float)rand() / RAND_MAX;
        if (alea < proba_s) {
            scatter(i, volume.material, dm);
        }
        else if (proba_s < alea && alea < proba_s + proba_c) {
            capture(i);
        }
        else if (proba_s + proba_c < alea && alea < 1.0) {
            /*
            //cout << "fission" << endl;
            if (fissioned_neutrons_vector.size() < dm.nb_source) {
                Particle fissioned_neutron = Particle(neutron.x, neutron.y, 0, 0, r_neutron, mass_neutron, x_min, x_max, y_min, y_max);
                fissioned_neutrons_vector.push_back(fissioned_neutron);
            }
            else {
                fissioned_neutrons_vector[counter].setX(neutron.x);
                fissioned_neutrons_vector[counter].setY(neutron.y);
                counter++;
                if (dm.nb_source != 0) {
                    counter = counter % dm.nb_source;
                }
            }
            */
            fission(i, volume.material, dm);
        }
    }
}


void NeutronSet::scatter(int i, Material material, DataManager& dm) {
    neutrons_array[i].set_random_velocity(dm.neutron_speed_magnitude);
    neutrons_array[i].free_path = sort_free_path(material);
}

void NeutronSet::capture(int i) {
    if (neutrons_array[i].is_source) {
        nb_captured_neutrons++;
        neutrons_array[i].is_source = false;
    }
    neutrons_array[i].is_alive = false;
    nb_alive_neutrons--;
}

void NeutronSet::fission(int i, Material& material, DataManager& dm) {
    if (neutrons_array[i].is_source) {
        nb_fissioned_neutrons++;
        nb_fission = nb_fission + material.nu_bar; //a corriger sur le nu_bar qui n'est pas tjrs fixe
        neutrons_array[i].is_source = false;
    }

    neutrons_array[i].set_random_velocity(dm.neutron_speed_magnitude);
    neutrons_array[i].free_path = sort_free_path(material);
    choose_if_delayed_neutron(dm, neutrons_array[i]);

    if (dm.allow_neutron_creation) {
        int nu = compute_nu(material);
        for (int l = 0; l < nu - 1; l++) {
            int k = add_one_active_neutron(neutrons_array[i].x, neutrons_array[i].y, dm);
            if (k != -1) {
                neutrons_array[k].is_source = false;
                choose_if_delayed_neutron(dm, neutrons_array[k]);
                neutrons_array[k].free_path = sort_free_path(material);
            }            
        }
    }
}

int NeutronSet::compute_nu(Material& material) {
    float nu_bar = material.nu_bar;
    int nu_bar_floor = floor(nu_bar);
    int nu_bar_ceil = ceil(nu_bar);

    float alea = (float)rand() / RAND_MAX;
    if (alea < nu_bar - nu_bar_floor) {
        return nu_bar_floor;
    }
    else {
        return nu_bar_ceil;
    }
}

void NeutronSet::show_neutrons_array() {
    cout << "neutrons_array :" <<endl;
    cout << "nb neutrons :" << neutrons_array.size() << endl;
    for (int i = 0; i < neutrons_array.size(); i++) {
        cout << i << " | ";
        cout << neutrons_array[i].x << " | ";
        cout << neutrons_array[i].y << " | ";
        cout << neutrons_array[i].vx << " | ";
        cout << neutrons_array[i].vy << endl;
    }
    cout << endl;
}

int NeutronSet::get_nb_alive_neutrons() {
    int counter = 0;
    for (int i = 0; i < neutrons_array.size(); i++) {
        if (neutrons_array[i].is_alive == true) {
            counter++;
        }
    }
    return counter;
}




float NeutronSet::sort_free_path(Material& material) {
    float alea = (float)rand() / RAND_MAX;
    float sigma = material.sigma_total_macro;
    float p_x = alea * sigma;
    //p(x) = sigma * exp( - sigma * x)
    // ln(p(x)/sigma) = - sigma * x
    //x = -1/sigma(ln(p(x)/sigma))
    float sorted_free_path = (-1 / sigma) * log(p_x / sigma);
    return sorted_free_path;

}

void NeutronSet::check_delayed_neutrons_activation(DataManager& dm) {
    for (int i = 0; i < neutrons_array.size(); i++) {
        if (!neutrons_array[i].is_active) {
            if (neutrons_array[i].clock_reactions.getElapsedTime().asMilliseconds() > dm.delayed_neutrons_time) {
                neutrons_array[i].is_active = true;
            }
        }
    }
}


void NeutronSet::choose_if_delayed_neutron(DataManager& dm, Particle& neutron) {
    float alea_delayed_neutron = (float)rand() / RAND_MAX;
    if (alea_delayed_neutron < dm.delayed_neutrons_proportion) {
        neutron.is_active = false;
        neutron.clock_reactions.restart();
    }
}

void NeutronSet::restart_clocks() {
    for (int i = 0; i < neutrons_array.size(); i++) {
        neutrons_array[i].clock.restart();
    }
}


void NeutronSet::update_wall_positions(DataManager& dm) {
    x_min = r_neutron;
    x_max = x_canvas / dm.ppcm;
    y_min = r_neutron + (float)dm.height_menu / dm.ppcm;
    y_max = y_canvas / dm.ppcm;
    for (int i = 0; i < neutrons_array.size(); i++) {
        neutrons_array[i].x_min = x_min;
        neutrons_array[i].x_max = x_max;
        neutrons_array[i].y_min = y_min;
        neutrons_array[i].y_max = y_max;
    }
}


void NeutronSet::renormalize(DataManager& dm, int nb_source, bool activated, int elapsed_seconds, int renormalization_delay) {
    if (activated) {        
        if (elapsed_seconds % renormalization_delay == 0) {     
            cout << "renormalization " << endl ;
            cout << "elapsed_seconds " + to_string(elapsed_seconds) << endl << endl;
            if (neutrons_array.size() > nb_source) {
                std::vector<Particle> neutron_batch_vector;                
                for (int i = neutrons_array.size()-1; i >= (neutrons_array.size() - nb_source); --i) {
                    neutrons_array[i].set_as_source(); 
                    neutron_batch_vector.push_back(neutrons_array[i]);                    
                }                
                neutrons_array = neutron_batch_vector;
            }       
                      
        }
    }   
}

void NeutronSet::generate_new_batch(DataManager& dm) {
    //neutrons_array.clear();
    for (int j = 0; j < fissioned_neutrons_vector.size(); j++) {
        Particle fissioned_neutron = Particle(fissioned_neutrons_vector[j].x, fissioned_neutrons_vector[j].y, 0, 0, r_neutron, mass_neutron, x_min, x_max, y_min, y_max);
        fissioned_neutron.set_random_velocity(dm.neutron_speed_magnitude);
        fissioned_neutron.set_as_source();
        neutrons_array.push_back(fissioned_neutron);
    }
    fissioned_neutrons_vector.clear();

    while (neutrons_array.size() < dm.nb_source) {
        Particle fissioned_neutron = Particle(0, 0, 0, 0, r_neutron, mass_neutron, x_min, x_max, y_min, y_max);
        fissioned_neutron.set_random_velocity(dm.neutron_speed_magnitude);
        fissioned_neutron.set_random_position();
        fissioned_neutron.set_as_source();
        neutrons_array.push_back(fissioned_neutron);
    }    
}


void NeutronSet::compute_keff(DataManager& dm) {
    if (nb_captured_neutrons + nb_fissioned_neutrons + nb_fled_neutrons != 0) {
        keff = (float)(nb_fission)/(float)(nb_captured_neutrons + nb_fissioned_neutrons + nb_fled_neutrons);
    }    
}

void NeutronSet::compute_averaged_keff() {
    if (batch_keff_vector.size() == 0) {
        averaged_keff = 0.0;
    }
    else {
        averaged_keff = std::accumulate(batch_keff_vector.begin(), batch_keff_vector.end(), 0.0) / batch_keff_vector.size();
    }

}

void NeutronSet::compute_sigma() {
    int n = batch_keff_vector.size();
    if (n == 0) {
        sigma = 0.0;
    }
    else {
        float variance = 0.0;
        for (int i = 0; i < n; i++) {
            variance += (keff - averaged_keff) * (keff - averaged_keff);
        }
        float n_float = (float)n;
        variance = variance / (n_float - 1);

        sigma = sqrt(variance / n_float);
        sigma = sigma * 100000;
    }

}

void NeutronSet::reset_keff_counters() {
    nb_fissioned_neutrons = 0;
    nb_fled_neutrons = 0;
    nb_captured_neutrons = 0;
    nb_fission = 0;
}
