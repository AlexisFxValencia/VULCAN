#pragma once
#include <string>
#include "Particle.h"
#include "Material.h"


using namespace std;

class Volume {
public:
	string name;
	string type;
	float param1;
	float param2;
	float x;
	float y;
	Material material;
	bool is_selected;
	sf::Vector2f decentering;
	float geometrical_buckling;
	bool arrow_moves_allowed;
	int priority;

	Volume();
	Volume(string name, string type, float param1, float param2, float x, float y, Material material, int priority);
	void compute_buckling();
	bool contains(Particle particle);
	bool contains(float x_test, float y_test);
};
