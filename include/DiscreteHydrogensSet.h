#pragma once
#include "Particle.h"
#include "ParticlesSet.h"
#include "DiscreteNuclidesSet.h"
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector> //Ne pas oublier !
#include "DataManager.h"

class DiscreteHydrogensSet
{
	public:
		std::vector<Particle> hydrogens_array;

        DiscreteHydrogensSet();
        void take_one_step();
        void rebound_on_walls(DataManager& dm);
        void init(DataManager& dm);
        void restart_clocks();
};

