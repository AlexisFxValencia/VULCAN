#include "DiscreteNuclidesSet.h"

DiscreteNuclidesSet::DiscreteNuclidesSet() {

}

void DiscreteNuclidesSet::init(DataManager& dm) {
    Particle nuclide = Particle(10, 10, 0.0, 0.0, dm.r_nuclide, dm.mass_nuclide, dm.r_nuclide, dm.x_canvas / dm.ppcm, dm.r_nuclide, dm.y_canvas / dm.ppcm);
    for (int j = 0; j < dm.nb_nuclide; j++) {
        nuclide.set_random_position();
        nuclide.set_random_velocity(dm.nuclide_speed_magnitude);
        nuclides_array.push_back(nuclide);
    }
}

void DiscreteNuclidesSet::take_one_step() {
    for (int j = 0; j < nuclides_array.size(); j++) {
        nuclides_array[j].take_one_step();
    }
}

void DiscreteNuclidesSet::rebound_on_walls(DataManager& dm) {
    if (dm.reflexions_activated) {
        for (int j = 0; j < nuclides_array.size(); j++) {
            nuclides_array[j].rebound_on_walls();
        }
    }
}

void DiscreteNuclidesSet::restart_clocks() {
    for (int i = 0; i < nuclides_array.size(); i++) {
        nuclides_array[i].clock.restart();
    }
}
