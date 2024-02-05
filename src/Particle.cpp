#include "Particle.h"

const double PI = std::acos(-1.0);

Particle::Particle() {
    x = 0.0;
    y = 0.0;
    vx = 0.01;
    vy = 0.01;
    velocity = 0.0002;
    r = 20.0;
    mass = 1.0;
    x_min = r;
    y_min = r;
    x_max = 34.0 - r;
    y_max = 19.0 - r;
    x_old = 0.0;
    y_old = 0.0;

    vx_old = 0;
    vy_old = 0;
    is_source = false;
    was_detected = false;
    is_active = true;
    free_path = 1.0;
    containter_index = -1;
}


Particle::Particle(float x, float y, float vx, float vy, float r, float mass, float x_min, float x_max, float y_min, float y_max){
    //ctor
    this->x = x;
    this->y = y;
    this->theta = 0.0;
    this->vx = vx;
    this->vy = vy;
    compute_velocity();
    this->r = r;
    this->mass = mass;
    this->x_min = x_min;
    this->x_max = x_max;
    this->y_min = y_min;
    this->y_max = y_max;
    this->x_old = x;
    this->y_old = y;
    this->is_source = false;
    this->is_active = true;
    this->free_path = 1.0;
    this->containter_index = -1;
    this->is_alive = false;
}



Particle::~Particle()
{
    //dtor
}

void Particle::set_as_source() {
    is_source = true;
}

void Particle::setX(float x) {
    this->x = x;
    this->x_old = x;
}


void Particle::setY(float y) {
    this->y = y;
    this->y_old = y;
}


void Particle::setVx(float vx) {
    this->vx = vx;
}


void Particle::setVy(float vy) {
    this->vy = vy;
}

void Particle::set_last_position() {
    x_old = this->x;
    y_old = this->y;
    //cout << "x_old : " << x_old << "y_old : " << y_old << endl;
}



void Particle::set_random_position() {
    float alea_1 = (float)rand()/RAND_MAX;
    x = alea_1 * (x_max - x_min) + x_min;
    this->x_old = x;

    float alea_2 = (float)rand() / RAND_MAX;
    y = alea_2 * (y_max - y_min) + y_min;
    this->y_old = y;
}

void Particle::set_random_velocity(float speed_magnitude) {    
    float alea = (float)rand() / RAND_MAX;
    this-> theta = alea * 2 * PI;
    vx = speed_magnitude * cos(theta);
    vy = speed_magnitude * sin(theta);
    velocity = speed_magnitude;
}

void Particle::take_one_step() {    
    float dt = clock.restart().asSeconds(); // restart gives the amount of time passed and also restarts the clock allowing a constant looping
    x += vx * dt;
    y += vy * dt;
}

void Particle::rebound_on_walls() {
    if (x > x_max - r) {
        vx = -abs(vx);
    }
    else if (x < x_min + r) {
        vx = abs(vx);
    }
    if (y > y_max - r) {
        vy = -abs(vy);
    }
    else if (y < y_min + r) {
        vy = abs(vy);
    }
}

void Particle::cyclical_reflexion() {
    if (x > x_max) {
        x = x_min;
    }
    else if (x < x_min) {
        x = x_max;
    }
    if (y > y_max) {
        y = y_min;
    }
    else if (y < y_min) {
        y = y_max;
    }
}

void Particle::compute_velocity() {
    velocity = sqrt(pow(vx, 2) + pow(vy, 2));
}

