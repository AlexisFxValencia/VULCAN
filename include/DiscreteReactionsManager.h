#pragma once
#include "Particle.h"
#include "ParticlesSet.h"
#include "DiscreteNuclidesSet.h"
#include "DiscreteHydrogensSet.h"
#include "DiscreteSpentNuclidesSet.h"
#include <cmath>

class DiscreteReactionsManager
{
public:
    DiscreteReactionsManager();
    void compute_reactions(DataManager& dm, ParticlesSet& particle_set, DiscreteNuclidesSet& nuclide_set, DiscreteSpentNuclidesSet& spent_nuclide_set, DiscreteHydrogensSet& hydrogen_set);
    void compute_elastic_collisions(std::vector<Particle>& tableauParticules1, std::vector<Particle>& tableauParticules2);
    void compute_one_collision(Particle& particules1, Particle& particules2);
    void compute_one_collision_simplified(Particle& particules1, Particle& particules2);
    
    void compute_realistic_collisions(std::vector<Particle>& tableauParticules1, std::vector<Particle>& tableauParticules2);
    void compute_one_potential_collision(Particle& particules1, Particle& particules2);
    float force_repulsion5(double distance, double D);

    void compute_fissions(DataManager& dm, std::vector<Particle>& neutrons_array, std::vector<Particle>& nuclide_array, std::vector<Particle>& spent_nuclide_array);
    bool fission_sorted(DataManager& dm); 
    void create_nu_neutrons(DataManager& dm, std::vector<Particle>& neutrons_array, Particle& nuclide);
    void split_nuclide(DataManager& dm, Particle& nuclide, Particle& neutron, std::vector<Particle>& spent_nuclide_array);
    
};

