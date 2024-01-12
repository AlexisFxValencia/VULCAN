#pragma once
#include "Particle.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Material
{
public:
		Material(std::string name2, sf::Color color, float atomic_density, int nu_bar, float sigma_s, float sigma_c, float sigma_f);
		Material();
		std::string name;
		sf::Color color;
		float atomic_density;
		float sigma_s;
		float sigma_c;
		float sigma_f;
		float sigma_s_macro;
		float sigma_c_macro;
		float sigma_f_macro;
		float sigma_total_macro;
		float mean_free_path;
		float nu_bar;
		float mu_bar;
		float material_buckling;

		void set_xs_c(float xs_c);
		void set_xs_s(float xs_s);
		void set_xs_f(float xs_f);
		void set_ad(float ad);
		void set_nu_bar(float nu_bar);
		void compute_buckling();
		void compute_macroscropic_sigma();
		void compute_mean_free_path();
};

