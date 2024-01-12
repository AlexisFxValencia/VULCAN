#pragma once
#ifndef CONTROLROD_H
#define CONTROLROD_H
#include <vector>
#include "ParticlesSet.h"
#include "NeutronSet.h"
#include "DataManager.h"

class ControlRod
{
public:
    ControlRod(DataManager& dm);
    ControlRod();
    virtual ~ControlRod();

    void reset_parameters(DataManager& dm);

    float get_x();
    float get_y();
    float get_width();
    float get_height();
    void move_right(DataManager& dm);
    void move_left(DataManager& dm);
    void move_up(DataManager& dm);
    void move_down(DataManager& dm);
    void absorb_neutrons(ParticlesSet& particules_set);
    void absorb_neutrons(NeutronSet& neutron_set);

private:
    float x;
    float y;
    float width;
    float height;
    float delta;
};

#endif // CONTROLROD_H
