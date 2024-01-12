#include "Detector.h"

Detector::Detector() {	
}

void Detector::init() {
	nb_neutrons_detected = 0;
	detection_period = 100; //in ms
	intensity = 0.0;
}

void Detector::detects(NeutronSet& neutron_set) {
	for (int i = 0; i < neutron_set.neutrons_array.size(); i++) {
		if (contains(neutron_set.neutrons_array[i]) && !neutron_set.neutrons_array[i].was_detected) {
			nb_neutrons_detected++;
			neutron_set.neutrons_array[i].was_detected = true;
			//cout << "nb_neutrons_detected : " << nb_neutrons_detected << endl;
			
		}
	}
}

void Detector::update_intensity(NeutronSet& neutron_set) {
		intensity = (float)nb_neutrons_detected / (float)detection_period;
		nb_neutrons_detected = 0;

		for (int i = 0; i < neutron_set.neutrons_array.size(); i++) {
			neutron_set.neutrons_array[i].was_detected = false;
		}
		//cout << "intensity : " << intensity << endl;	
}