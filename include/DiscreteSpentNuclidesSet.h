#pragma once

#include "Particle.h"
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector> //Ne pas oublier !
#include "DataManager.h"
#include "ParticlesSet.h"

class DiscreteSpentNuclidesSet
{
public:
    std::vector<Particle> nuclides_array;

    DiscreteSpentNuclidesSet();
    void init(DataManager& dm);
    void take_one_step();
    void rebound_on_walls(DataManager& dm);
    void restart_clocks();
};