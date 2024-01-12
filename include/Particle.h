#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H

#include <string>
#include <SFML/Graphics.hpp>




using namespace std;

class Particle
{
public:
    float x;
    float y;
    float theta;
    float vx;
    float vy;
    float velocity;
    float r;
    float mass;
    float free_path;
    int containter_index;

    float x_min = x_min;
    float x_max = x_max;
    float y_min = y_min;
    float y_max = y_max;

    float x_old;
    float y_old;

    float vx_old;
    float vy_old;

    bool is_source;
    bool was_detected;

    bool is_active;

    bool is_alive;

    sf::Clock clock;
    sf::Clock clock_reactions;

    Particle();
    Particle(float x, float y, float vx, float vy, float r, float mass, float x_min, float x_max, float y_min, float y_max);
    virtual ~Particle(); 
    void set_as_source();
    void setX(float x);
    void setY(float y);
    void setVx(float vx);
    void setVy(float vy);
    void set_last_position();

    void take_one_step();
    void rebound_on_walls();
    void cyclical_reflexion();
    void set_random_position();
    void set_random_velocity(float speed_magnitude);


    void compute_velocity();

    
};

#endif // PARTICLE_H
