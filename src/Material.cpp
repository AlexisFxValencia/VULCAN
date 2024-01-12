#include "Material.h"
using namespace std;

Material::Material(std::string name2, sf::Color color, float atomic_density, int nu_bar, float sigma_s, float sigma_c, float sigma_f){
	this->name = name2;
	this->color = color;
	this->atomic_density = atomic_density;
	this->nu_bar = nu_bar;
	this->sigma_s = sigma_s;
	this->sigma_c = sigma_c;
	this->sigma_f = sigma_f;
	this->mu_bar = 0;
	compute_macroscropic_sigma();
	compute_mean_free_path();
	material_buckling = 0;
	//cout << "sigma_s_macro : " << sigma_s_macro << endl;
	//cout << "sigma_c_macro : " << sigma_c_macro << endl;
	//cout << "sigma_f_macro : " << sigma_f_macro << endl;
}

Material::Material() {

}

void Material::compute_buckling() {
	float xs_tr = sigma_total_macro - mu_bar * sigma_s_macro;
	float D = 1 / (3 * xs_tr);

	this->material_buckling = (nu_bar * sigma_f_macro - (sigma_c_macro + sigma_f_macro)) / D;
}

void Material::set_xs_c(float xs_c) {
	this->sigma_c = xs_c;
}

void Material::set_xs_s(float xs_s) {
	this->sigma_s = xs_s;
}

void Material::set_xs_f(float xs_f) {
	this->sigma_f = xs_f;
}

void Material::set_ad(float ad) {
	this->atomic_density = ad;
}

void Material::set_nu_bar(float nu_bar) {
	this->nu_bar = nu_bar;
}

void Material::compute_macroscropic_sigma() {
	sigma_s_macro = atomic_density * sigma_s * 1e-24;
	sigma_c_macro = atomic_density * sigma_c * 1e-24;
	sigma_f_macro = atomic_density * sigma_f * 1e-24;
	sigma_total_macro = sigma_s_macro + sigma_c_macro + sigma_f_macro;
	//cout << "sigma_total_macro of material named " << name << " is : " << sigma_total_macro << "barn" << endl;
}

void Material::compute_mean_free_path() {
	mean_free_path = 1 / sigma_total_macro;
	cout << "mean_free_path of material named " << name << " is : " << mean_free_path << " cm." << endl;
}

