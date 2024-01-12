#pragma once
#ifndef PARTICLESSET_H
#define PARTICLESSET_H
#include "Particle.h"
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector> //Ne pas oublier !
#include "DataManager.h"



class ParticlesSet
{
public:
    std::vector<Particle> neutrons_array;
    float mean_velocity;
    ParticlesSet();
    void take_one_step();
    void rebound_on_walls(DataManager& dm);
    void init(DataManager& dm);
    void remove_fled_neutrons(DataManager& dm);
    void reset_array_as_new(DataManager& dm);
    void restart_clocks();

    void compute_mean_velocity();

};

#endif // PARTICLESSET_H
