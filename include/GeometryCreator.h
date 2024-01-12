#pragma once
#ifndef GEOMETRYCREATOR_H
#define GEOMETRYCREATOR_H
#include <vector>
#include <stdlib.h> 
#include "ParticlesSet.h"
#include <math.h>
#include "Volume.h"
#include "DataManager.h"

class GeometryCreator
{
public:
    int x_window;
    int y_window;
    float ppcm;

    GeometryCreator();
    GeometryCreator(DataManager& dm);
    void set_nuclides_positions(std::vector<Particle>& nuclides_array, DataManager& dm);
    void set_nuclide_positions_randomly(std::vector<Particle>& nuclides_array);
    void form_a_square(float fuel_x, float fuel_y, float fuel_dx, float fuel_dy, std::vector<Particle>& nuclides_array);
    void form_a_disk(float x_c, float y_c, float radius, std::vector<Particle>& nuclides_array);
    float generate_random_angle();

    bool contains(float x, float y, DataManager& dm);  
};

#endif // GEOMETRYCREATOR_H
