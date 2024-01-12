#include "ControlRod.h"

ControlRod::ControlRod(DataManager& dm)
{
    x = dm.x_rod;
    y = dm.y_rod;
    width = dm.width_rod;
    height = dm.height_rod;
    delta = dm.delta_rod;
}

ControlRod::ControlRod() {

}


ControlRod::~ControlRod()
{
    //dtor
}


void ControlRod::reset_parameters(DataManager& dm) {
    x = dm.x_rod;
    y = dm.y_rod;
    width = dm.width_rod;
    height = dm.height_rod;
    delta = dm.delta_rod;
}


float ControlRod::get_x(){
    return x;
}


float ControlRod::get_y(){
    return y;
}


float ControlRod::get_width(){
    return width;
}


float ControlRod::get_height(){
    return height;
}


void ControlRod::move_right(DataManager& dm) {
    x = x + delta;
    dm.x_rod = dm.x_rod + delta;
}


void ControlRod::move_left(DataManager& dm) {
    x = x - delta;
    dm.x_rod = dm.x_rod - delta;
}


void ControlRod::move_up(DataManager& dm) {
    y = y - delta;
    dm.y_rod = dm.y_rod - delta;
}


void ControlRod::move_down(DataManager& dm) {
    y = y + delta;
    dm.y_rod = dm.y_rod + delta;
}


void ControlRod::absorb_neutrons(ParticlesSet& particles_set) {
    float left_edge = x;
    float right_edge = x + width;
    float lower_edge = y;
    float upper_edge = y + height;
    float counter = 0;
    for (int i = particles_set.neutrons_array.size() - 1; i > -1; i--) {
        float x_neutron((particles_set.neutrons_array)[i].x);
        float y_neutron((particles_set.neutrons_array)[i].y);
        if (x_neutron > left_edge && x_neutron < right_edge && y_neutron > lower_edge && y_neutron < upper_edge) {
            counter++;
            (particles_set.neutrons_array).erase((particles_set.neutrons_array).begin() + i);
        }
        if (counter != 0) {
            //std::cout << "nombre de neutrons supprimé BCS : " << counter << std::endl;
        }
    }
}

void ControlRod::absorb_neutrons(NeutronSet& neutron_set) {
    float left_edge = x;
    float right_edge = x + width;
    float lower_edge = y;
    float upper_edge = y + height;
    float counter = 0;
    for (int i = neutron_set.neutrons_array.size() - 1; i > -1; i--) {
        float x_neutron((neutron_set.neutrons_array)[i].x);
        float y_neutron((neutron_set.neutrons_array)[i].y);
        if (x_neutron > left_edge && x_neutron < right_edge && y_neutron > lower_edge && y_neutron < upper_edge) {
            counter++;
            //(neutron_set.neutrons_array).erase((neutron_set.neutrons_array).begin() + i);
            neutron_set.neutrons_array[i].is_alive = false;
            
        }
    }
    if (counter != 0) {
        //std::cout << "nombre de neutrons supprimé BCS : " << counter << std::endl;
    }
    
}
