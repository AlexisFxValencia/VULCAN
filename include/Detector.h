#pragma once
#include <string>
#include "Particle.h"
#include <SFML/Graphics.hpp>
#include "NeutronSet.h"
#include "Volume.h"


class Detector : public Volume
{
	using Volume::Volume;
public:
	int nb_neutrons_detected;
	int detection_period;
	float intensity;


	Detector();
	void detects(NeutronSet &neutron_set);
	void update_intensity(NeutronSet& neutron_set);
	void init();
};

