#include "GeometryCreator.h"
# define M_PI           3.14159265358979323846


GeometryCreator::GeometryCreator(DataManager& dm) {
    this->x_window = dm.x_window;
    this->y_window = dm.y_window;
    this->ppcm = dm.ppcm;
}


GeometryCreator::GeometryCreator() {
}

void GeometryCreator::set_nuclides_positions(std::vector<Particle>& nuclides_array, DataManager& dm) {
    int fuel_x = x_window / (2 * ppcm);
    int fuel_y = y_window / (2 * ppcm) + 2;
    int fuel_dx = 16;
    int fuel_dy = 16;
    //form_a_square(fuel_x, fuel_y, fuel_dx, fuel_dy, nuclides_array);

     
    float radius = 3.0;
    float x_c = x_window / (2 * ppcm);
    float y_c = y_window / (2 * ppcm);
    
    
    if (dm.nuclides_distribution == "square") {
        form_a_square(fuel_x, fuel_y, fuel_dx, fuel_dy, nuclides_array);
    } else if (dm.nuclides_distribution =="disk") {
        form_a_disk(x_c, y_c, radius, nuclides_array);
    } else if (dm.nuclides_distribution == "random") {
        set_nuclide_positions_randomly(nuclides_array);
    }
    
    


   
    
}

void GeometryCreator::set_nuclide_positions_randomly(std::vector<Particle>& nuclides_array) {
    for (int j = 0; j < nuclides_array.size(); j++) {
        nuclides_array[j].set_random_position();
    }
}

void GeometryCreator::form_a_square(float fuel_x, float fuel_y, float fuel_dx, float fuel_dy, std::vector<Particle>& nuclides_array) {
    float mX = fuel_x - fuel_dx / 2;
    float mY = fuel_y - fuel_dy / 2;
    int nb_nuclide = nuclides_array.size();
    int n_col = (int)round(sqrt(nb_nuclide));
    int n_lin = n_col + 2;
    float pasL = fuel_dx / n_col;
    float pasl = fuel_dy / n_lin;
    for (int lin = 0; lin < n_lin; lin++) {
        for (int col = 0; col < n_col; col++) {
            //cout << "lin : " << lin << endl;
            int nuclide_rank = lin * n_col + col;
            //cout << "nuclide_rank : " << nuclide_rank << endl;
            if (nuclide_rank < nb_nuclide) {
                float x_fuel = mX + (col * pasL);
                float y_fuel = mY + (lin * pasl);
                nuclides_array[nuclide_rank].setX(x_fuel);
                nuclides_array[nuclide_rank].setY(y_fuel);
                //cout << "x_fuel : " << x_fuel << "y_fuel : " << y_fuel << endl;
            }
        }
    }
}


void GeometryCreator::form_a_disk(float x_c, float y_c, float radius, std::vector<Particle>& nuclides_array) {
   
    for (int j = 0; j < nuclides_array.size(); j++) {
        float alea = (float)rand() / RAND_MAX;
        float random_radius = radius*alea;
        float theta = generate_random_angle();
        nuclides_array[j].x = x_c + random_radius * cos(theta);
        nuclides_array[j].y = y_c + random_radius * sin(theta);
    }
    
}

float GeometryCreator::generate_random_angle() {
    float alea = (float)rand() / RAND_MAX;
    float theta = alea * 2 * M_PI;
    return theta;
}



bool GeometryCreator::contains(float x, float y, DataManager& dm) {
    for (int i = 0; i < dm.volu_array.size(); i++) {
        if (dm.volu_array[i].contains(x, y)) {
            return true;
        }
    }
    return false;
}


