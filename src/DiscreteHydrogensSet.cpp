#include "DiscreteHydrogensSet.h"

DiscreteHydrogensSet::DiscreteHydrogensSet() {

}

void DiscreteHydrogensSet::init(DataManager& dm) {
    Particle hydrogen = Particle(10, 10, 1.0, 1.0, dm.r_hydrogen, dm.mass_hydrogen, dm.r_hydrogen, dm.x_canvas / dm.ppcm, dm.r_hydrogen, dm.y_canvas / dm.ppcm);
    for (int k = 0; k < dm.nb_hydrogen; k++) {
        hydrogen.set_random_position();
        hydrogen.set_random_velocity(dm.hydrogen_speed_magnitude);
        hydrogens_array.push_back(hydrogen);
    }
}

void DiscreteHydrogensSet::take_one_step() {
    for (int k = 0; k < hydrogens_array.size(); k++) {
        hydrogens_array[k].take_one_step();
    }
}

void DiscreteHydrogensSet::rebound_on_walls(DataManager& dm) {
    if (dm.reflexions_activated) {
        for (int k = 0; k < hydrogens_array.size(); k++) {
            hydrogens_array[k].rebound_on_walls();
        }
    }
}

void DiscreteHydrogensSet::restart_clocks() {
    for (int i = 0; i < hydrogens_array.size(); i++) {
        hydrogens_array[i].clock.restart();
    }
}