#include "DiscreteReactionsManager.h"
# define M_PI           3.14159265358979323846

DiscreteReactionsManager::DiscreteReactionsManager() {

}

void DiscreteReactionsManager::compute_reactions(DataManager& dm, ParticlesSet& particle_set, DiscreteNuclidesSet& nuclide_set, DiscreteSpentNuclidesSet& spent_nuclide_set, DiscreteHydrogensSet& hydrogen_set) {
    
    
    compute_fissions(dm, particle_set.neutrons_array, nuclide_set.nuclides_array, spent_nuclide_set.nuclides_array);

    if (dm.collision_type == "elastic") {
        compute_elastic_collisions(hydrogen_set.hydrogens_array, hydrogen_set.hydrogens_array); 
        compute_elastic_collisions(hydrogen_set.hydrogens_array, particle_set.neutrons_array);
        compute_elastic_collisions(hydrogen_set.hydrogens_array, nuclide_set.nuclides_array);
        compute_elastic_collisions(hydrogen_set.hydrogens_array, spent_nuclide_set.nuclides_array);

        compute_elastic_collisions(particle_set.neutrons_array, nuclide_set.nuclides_array);
        compute_elastic_collisions(nuclide_set.nuclides_array, nuclide_set.nuclides_array);

    
        compute_elastic_collisions(nuclide_set.nuclides_array, spent_nuclide_set.nuclides_array);
        compute_elastic_collisions(spent_nuclide_set.nuclides_array, spent_nuclide_set.nuclides_array);
    }
    else if (dm.collision_type == "potential") {
        compute_elastic_collisions(hydrogen_set.hydrogens_array, nuclide_set.nuclides_array);
        compute_realistic_collisions(nuclide_set.nuclides_array, nuclide_set.nuclides_array);
    }

}


void DiscreteReactionsManager::compute_elastic_collisions(std::vector<Particle>& tableauParticules1, std::vector<Particle>& tableauParticules2) {
    for (int i = 0; i < tableauParticules1.size(); i++) {
        for (int j = 0; j < tableauParticules2.size(); j++) {
            float distanceMinCarree = pow(tableauParticules1[i].r + tableauParticules2[j].r, 2);
            float distanceParticulesCarree = pow(tableauParticules1[i].x - tableauParticules2[j].x, 2) + pow(tableauParticules1[i].y - tableauParticules2[j].y, 2);
            
            if (distanceParticulesCarree <= distanceMinCarree) {
                compute_one_collision(tableauParticules1[i], tableauParticules2[j]);
                
                tableauParticules1[i].compute_velocity();
                tableauParticules2[j].compute_velocity();
            }
        }


    }
}

void DiscreteReactionsManager::compute_one_collision(Particle& particules1, Particle& particules2) {
    float r1 = particules1.r;
    float m1 = particules1.mass;
    float x1 = particules1.x;
    float y1 = particules1.y;
    float vx1 = particules1.vx;
    float vy1 = particules1.vy;

    float r2 = particules2.r;
    float m2 = particules2.mass;
    float x2 = particules2.x;
    float y2 = particules2.y;
    float vx2 = particules2.vx;
    float vy2 = particules2.vy;

    double R = 1;
    //     ***initialize some variables ****
    double  r12, m21, d, gammav, gammaxy, dgamma, dr, dc, sqs, t,
        dvx2, a, x21, y21, vx21, vy21, pi2, vx_cm, vy_cm;
    pi2 = 2 * acos(-1.0E0);
    r12 = r1 + r2;
    m21 = m2 / m1;
    x21 = x2 - x1;
    y21 = y2 - y1;
    vx21 = vx2 - vx1;
    vy21 = vy2 - vy1;

    vx_cm = (m1 * vx1 + m2 * vx2) / (m1 + m2);
    vy_cm = (m1 * vy1 + m2 * vy2) / (m1 + m2);


    //     *** calculate relative velocity angle
    gammav = atan2(-vy21, -vx21);

    //******** this block only if initial positions are given *********
    d = sqrt(x21 * x21 + y21 * y21);

    //     *** calculate relative position angle and normalized impact parameter ***
    gammaxy = atan2(y21, x21);
    dgamma = gammaxy - gammav;
    if (dgamma > pi2) { dgamma = dgamma - pi2; }
    else if (dgamma < -pi2) { dgamma = dgamma + pi2; }
    dr = d * sin(dgamma) / r12;

    //**** calculate impact angle if balls do collide ***
    double alpha = asin(dr);

    //     ***  update velocities ***

    a = tan(gammav + alpha);

    dvx2 = -2 * (vx21 + a * vy21) / ((1 + a * a) * (1 + m21));

    vx2 = vx2 + dvx2;
    vy2 = vy2 + a * dvx2;
    vx1 = vx1 - m21 * dvx2;
    vy1 = vy1 - a * m21 * dvx2;

    /*
    //     ***  velocity correction for inelastic collisions ***

    vx1=(vx1-vx_cm)*R + vx_cm;
    vy1=(vy1-vy_cm)*R + vy_cm;
    vx2=(vx2-vx_cm)*R + vx_cm;
    vy2=(vy2-vy_cm)*R + vy_cm;
    */


    particules1.setVx(vx1);
    particules1.setVy(vy1);
    particules2.setVx(vx2);
    particules2.setVy(vy2);


    float Ix = (x1 + x2) / 2;
    float Iy = (y1 + y2) / 2;
    float reducteurDistance = 0.10;
    int deltaAx = (x1 - Ix) * reducteurDistance;
    int deltaAy = (y1 - Iy) * reducteurDistance;
    int deltaBx = (x2 - Ix) * reducteurDistance;
    int deltaBy = (y2 - Iy) * reducteurDistance;


    particules1.setX(x1 + deltaAx);
    particules1.setY(y1 + deltaAy);
    particules2.setX(x2 + deltaBx);
    particules2.setY(y2 + deltaBy);

}


void DiscreteReactionsManager::compute_one_collision_simplified(Particle& particules1, Particle& particules2) {
    float r1 = particules1.r;
    float r2 = particules2.r;
    float x1 = particules1.x;
    float y1 = particules1.y;
    float x2 = particules2.x;
    float y2 = particules2.y;
    float distanceParticulesCarree = (float)(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    float vx1 = particules1.vx;
    float vy1 = particules1.vy;
    float OM = sqrt(distanceParticulesCarree);
    float ubx = (x1 - x2) / OM;
    float uby = (y1 - y2) / OM;
    float uax = uby;
    float uay = -ubx;

    float ps_vinit_ua = vx1 * uax + vy1 * uay;
    float ps_vinit_ub = vx1 * ubx + vy1 * uby;

    float vxfinal = ps_vinit_ua * uax - ps_vinit_ub * ubx;
    float vyfinal = ps_vinit_ua * uay - ps_vinit_ub * uby;


    particules1.setVx(vxfinal);
    particules1.setVy(vyfinal);

    float Ix = (x1 + x2) / 2;
    float Iy = (y1 + y2) / 2;
    float reducteurDistance = 0.15;
    int deltaAx = (int)((x1 - Ix) * reducteurDistance);
    int deltaAy = (int)((y1 - Iy) * reducteurDistance);
    int deltaBx = (int)((x2 - Ix) * reducteurDistance);
    int deltaBy = (int)((y2 - Iy) * reducteurDistance);

    particules1.setX(x1 + deltaAx);
    particules1.setY(y1 + deltaAy);

}



void DiscreteReactionsManager::compute_realistic_collisions(std::vector<Particle>& tableauParticules1, std::vector<Particle>& tableauParticules2) {
    if (tableauParticules1.size() > 0 && tableauParticules2.size() > 0) {
        for (int i = 0; i < tableauParticules1.size() - 1; i++) {
            for (int j = i + 1; j < tableauParticules2.size(); j++) {
                compute_one_potential_collision(tableauParticules1[i], tableauParticules2[j]);
                tableauParticules1[i].compute_velocity();
                tableauParticules2[j].compute_velocity();
                
            }
        }
    }    
}

void DiscreteReactionsManager::compute_one_potential_collision(Particle& particules1, Particle& particules2) {
    float dt = 0.001;
    float D = particules1.r + particules2.r;
    float dx2 = pow((particules2.x - particules1.x),2);
    float dy2 = pow((particules2.y - particules1.y), 2);
    float distance_carree = dx2 + dy2;
    
    if (distance_carree < 3 * D) {
        float distance = sqrt(distance_carree);

        float xa = (particules2.x - particules1.x) / distance;
        float ya = (particules2.y - particules1.y) / distance;
        float xb = -ya;
        float yb = xa;

        float PsV1a = particules1.vx * xa + particules1.vy * ya;
        float PsV1b = particules1.vx * xb + particules1.vy * yb;
        float PsV2a = particules2.vx * xa + particules2.vy * ya;
        float PsV2b = particules2.vx * xb + particules2.vy * yb;

        /*
        if (distance_carree < 2*D) {
            PsV1b = PsV1b*0.99;
            PsV2b = PsV2b*0.99;
        }
        */

        particules1.vx = (PsV1a + (force_repulsion5(distance, D)) * dt) * xa + PsV1b * xb;
        particules1.vy = (PsV1a + (force_repulsion5(distance, D)) * dt) * ya + PsV1b * yb;

        particules2.vx = (PsV2a - (force_repulsion5(distance, D)) * dt) * xa + PsV2b * xb;
        particules2.vy = (PsV2a - (force_repulsion5(distance, D)) * dt) * ya + PsV2b * yb;

        //cout << "distance_carree = " << distance_carree << endl;
        //cout << "particules1.vx = " << particules1.vx << endl;

        
    }
    
}

float DiscreteReactionsManager::force_repulsion5(double distance, double D) {
    float x = distance / D;
    float a = (2 * exp(-2 * x) * ((50 * x * x * x) - 160) - 10 * exp(-2 * x) * x * x);//-
    return a;
}



bool DiscreteReactionsManager::fission_sorted(DataManager& dm) {
    int alea = rand();
    int x = alea % 1000;
    if (x < dm.fission_probability) {
        return true;
    }
    else {
        return false;
    }
}

void DiscreteReactionsManager::compute_fissions(DataManager& dm, std::vector<Particle>& neutrons_array, std::vector<Particle>& nuclides_array, std::vector<Particle>& spent_nuclide_array) {
    for (int i = 0; i < neutrons_array.size(); i++) {
        for (int j = 0; j < nuclides_array.size(); j++) {
            float distanceMinCarree = pow(neutrons_array[i].r + nuclides_array[j].r, 2);
            float distanceParticulesCarree = pow(neutrons_array[i].x - nuclides_array[j].x, 2) + pow(neutrons_array[i].y - nuclides_array[j].y, 2);
            if (distanceParticulesCarree <= distanceMinCarree) {
                if (fission_sorted(dm)) {                    
                    split_nuclide(dm, nuclides_array[j], neutrons_array[i], spent_nuclide_array);
                    create_nu_neutrons(dm, neutrons_array, nuclides_array[j]);
                    neutrons_array[i].set_random_velocity(dm.neutron_speed_magnitude);
                    neutrons_array[i].x = nuclides_array[j].x;
                    neutrons_array[i].y = nuclides_array[j].y;
                    swap(nuclides_array[j], nuclides_array.back());
                    nuclides_array.pop_back();
                }
            }
            
        }
    }
}

void DiscreteReactionsManager::split_nuclide(DataManager& dm, Particle& nuclide, Particle& neutron, std::vector<Particle>& spent_nuclide_array) {
    float speed_magnitude = pow(neutron.mass * (pow(neutron.vx, 2) + pow(neutron.vy, 2)) / nuclide.mass, 0.5);
    Particle spent_nuclide_1 = Particle(nuclide.x, nuclide.y, 0, 0, dm.r_nuclide / 1.4142, dm.mass_nuclide / 2, dm.r_nuclide / 1.4142, dm.x_canvas / dm.ppcm, dm.r_nuclide / 1.4142, dm.y_canvas / dm.ppcm);
    spent_nuclide_1.set_random_velocity(speed_magnitude);
    spent_nuclide_array.push_back(spent_nuclide_1);
    Particle spent_nuclide_2 = Particle(nuclide.x, nuclide.y, -spent_nuclide_1.vx, -spent_nuclide_1.vy, dm.r_nuclide / 1.4142, dm.mass_nuclide / 2, dm.r_nuclide / 1.4142, dm.x_canvas / dm.ppcm, dm.r_nuclide / 1.4142, dm.y_canvas / dm.ppcm);
    spent_nuclide_array.push_back(spent_nuclide_2);
}


void DiscreteReactionsManager::create_nu_neutrons(DataManager& dm, std::vector<Particle>& neutrons_array, Particle& nuclide) {
    for (int i = 0; i < dm.nu_bar_discrete - 1; i++) {
        Particle induced_neutron = Particle(nuclide.x, nuclide.y, 0.0, 0.0, dm.r_neutron, dm.mass_neutron, dm.r_neutron, dm.x_canvas / dm.ppcm, dm.r_neutron, dm.y_canvas / dm.ppcm);
        induced_neutron.set_random_velocity(dm.neutron_speed_magnitude);
        neutrons_array.push_back(induced_neutron);
    }


}



