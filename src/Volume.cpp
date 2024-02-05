#include "Volume.h"


Volume::Volume() {

}
Volume::Volume(string name, string type, float param1, float param2, float x, float y, Material material, int priority) {
	this->name = name;
	this->type = type;
	this->param1 = param1; // radius for a circle
	this->param2 = param2;
	this->x = x;
	this->y = y;
	this->material = material;
	this->priority = priority;
	is_selected = false;
	geometrical_buckling = 1.0;
	arrow_moves_allowed = false;
	
}


void Volume::compute_buckling() {	
	if (type == "disk") {
		geometrical_buckling = powf(3.1415926 / param1, 2);
	}
	else if (type == "rectangle") {
		geometrical_buckling = powf(3.1415926 / param1, 2) + powf(3.1415926 / param2, 2);
	}
}

bool Volume::contains(Particle particle) {
	if (type == "disk") {		
		if (powf((particle.x - x), 2) + powf((particle.y - y), 2) < powf(param1,2)) {
			return true;
		}
	}
	else if (type == "rectangle"){
		float xmin = x - param1 / 2;
		float xmax = x + param1 / 2;
		float ymin = y - param2 / 2;
		float ymax = y + param2 / 2;
		if (xmin < particle.x && particle.x < xmax && ymin < particle.y && particle.y < ymax) {
			return true;
		}
	}
	return false;	
}

bool Volume::contains(float x_test, float y_test) {
	if (type == "disk") {
		if (powf((x_test - x), 2) + powf((y_test - y), 2) < powf(param1, 2)) {
			return true;
		}
	}
	else if (type == "rectangle") {
		float xmin = x - param1 / 2;
		float xmax = x + param1 / 2;
		float ymin = y - param2 / 2;
		float ymax = y + param2 / 2;
		if (xmin < x_test && x_test < xmax && ymin < y_test && y_test < ymax) {
			return true;
		}
	}
	return false;
}