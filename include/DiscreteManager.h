#pragma once
#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

#include "Particle.h"
#include "ParticlesSet.h"
#include "DiscreteHydrogensSet.h"
#include "DiscreteNuclidesSet.h"
#include "DiscreteSpentNuclidesSet.h"

#include "ControlRod.h"
#include "GeometryCreator.h"
#include "NeutronSet.h"
#include "DiscreteReactionsManager.h"
#include "SceneManager.h"

#include "GUICreator.h"
#include "DataManager.h"
#include "ContinuousManager.h"


class DiscreteManager
{
public:
    sf::Text text;
    sf::Text text2;
    sf::Font font;

    SceneManager scene_manager;
    ParticlesSet particles_set;
    DiscreteHydrogensSet hydrogen_set;
    DiscreteNuclidesSet nuclide_set;
    DiscreteSpentNuclidesSet spent_nuclide_set;
    DiscreteReactionsManager reaction_manager;
    GeometryCreator geometry_creator;

	DiscreteManager(DataManager& dm);
    void draw_neutrons(sf::RenderWindow& window, ParticlesSet particles_set, DataManager& dm);
    void draw_nuclides(sf::RenderWindow& window, DiscreteNuclidesSet nuclide_set, DataManager& dm);
    void draw_spent_nuclides(sf::RenderWindow& window, DiscreteSpentNuclidesSet spent_nuclide_set, DataManager& dm);
    void draw_hydrogens(sf::RenderWindow& window, DiscreteHydrogensSet hydrogen_set, DataManager& dm);
    void create_k_eff(ParticlesSet particles_set, int counter, int& nActuel, int& nAncien, sf::Text& text, sf::RenderWindow& window);
    void set_one_text_parameters(sf::Text& text, sf::Font& font);
    void set_text_parameters();
    void draw_k_eff(ParticlesSet particles_set, int counter, int& nActuel, int& nAncien, sf::RenderWindow& window);
    void draw_nb_neutrons(ParticlesSet particles_set, sf::RenderWindow& window);
    void draw_neutron_speed(ParticlesSet& particles_set, sf::RenderWindow& window);

    void discrete_main(DataManager& dm);

};

