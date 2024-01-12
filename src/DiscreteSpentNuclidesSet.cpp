#include "DiscreteSpentNuclidesSet.h"

DiscreteSpentNuclidesSet::DiscreteSpentNuclidesSet() {

}

void DiscreteSpentNuclidesSet::init(DataManager& dm) {
    Particle noyau = Particle(10, 10, 0.0, 0.0, dm.r_nuclide/1.4142 , dm.mass_nuclide/2, dm.r_nuclide/1.4142, dm.x_canvas / dm.ppcm, dm.r_nuclide/1.4142, dm.y_canvas / dm.ppcm);
    for (int j = 0; j < dm.nb_spent_nuclide; j++) {
        noyau.set_random_position();
        nuclides_array.push_back(noyau);
    }
}

void DiscreteSpentNuclidesSet::take_one_step() {
    for (int j = 0; j < nuclides_array.size(); j++) {
        nuclides_array[j].take_one_step();
    }
}

void DiscreteSpentNuclidesSet::rebound_on_walls(DataManager& dm) {
    if (dm.reflexions_activated) {
        for (int j = 0; j < nuclides_array.size(); j++) {
            nuclides_array[j].rebound_on_walls();
        }
    }
}

void DiscreteSpentNuclidesSet::restart_clocks() {
    for (int i = 0; i < nuclides_array.size(); i++) {
        nuclides_array[i].clock.restart();
    }
}