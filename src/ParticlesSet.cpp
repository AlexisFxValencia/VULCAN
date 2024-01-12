#include "ParticlesSet.h"
#include <math.h>


/*idees :
- source de neutrons repartis, fission spontan�es
- creer une fonction qui va dire si la r�action est une fission, une diffusion ou une absorbtion. cela devrait rendre obsol�te "autorisationDeFissionner"
- moderation des neutrons, sections efficaces
- voir diff�rentes g�om�tries de mat�riaux, dont une al�atoire dans une boule
- cr�er interface graphique ou par texte ?
- voir si on peut g�rer la densit� du fuel. 
- creer des blocs d'eau. 
*/


ParticlesSet::ParticlesSet() {
    mean_velocity = 0.0;
}

void ParticlesSet::init(DataManager& dm) {
    Particle neutron = Particle(10.0, 10.0, 7.0, -8.0, dm.r_neutron, dm.mass_neutron, dm.r_neutron, dm.x_canvas/dm.ppcm, dm.r_neutron, dm.y_canvas/dm.ppcm);
    for (int i = 0; i < dm.nb_source; i++) {
        neutron.set_random_position();
        neutron.set_random_velocity(dm.neutron_speed_magnitude);
        neutrons_array.push_back(neutron);
    }
}


void ParticlesSet::take_one_step() {
    for (int i = 0; i < neutrons_array.size(); i++) {
        neutrons_array[i].take_one_step();
    }
}

void ParticlesSet::rebound_on_walls(DataManager& dm) {
    if (dm.reflexions_activated) {
        for (int i = 0; i < neutrons_array.size(); i++) {
            neutrons_array[i].rebound_on_walls();
        }
    }
}


void ParticlesSet::remove_fled_neutrons(DataManager& dm) {
    for (int i = 0; i < neutrons_array.size(); i++) {
        float x(neutrons_array[i].x);
        float y(neutrons_array[i].y);
        if (x > dm.x_canvas / dm.ppcm + dm.r_neutron || x < -dm.r_neutron || y > dm.y_canvas / dm.ppcm + dm.r_neutron || y < -dm.r_neutron) {
            //neutrons_array.erase(neutrons_array.begin() + i);
            swap(neutrons_array[i], neutrons_array.back());
            neutrons_array.pop_back();
            //std::cout << "un neutron a fui par un bord ! Nombre de neutrons restant : " << tableauNeutrons.size() << std::endl;
            break;
        }
    }
}

void ParticlesSet::restart_clocks(){
    for (int i = 0; i < neutrons_array.size(); i++) {
        neutrons_array[i].clock.restart();
    }
}

void ParticlesSet::compute_mean_velocity() {
    mean_velocity = 0.0;
    for (int i = 0; i < neutrons_array.size(); i++) {
        mean_velocity += neutrons_array[i].velocity;
    }
    mean_velocity /= neutrons_array.size();
}


