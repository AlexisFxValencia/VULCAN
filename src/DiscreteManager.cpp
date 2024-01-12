#include "DiscreteManager.h"


DiscreteManager::DiscreteManager(DataManager& dm) {
    scene_manager = SceneManager(dm);
    geometry_creator = GeometryCreator(dm);
    particles_set.init(dm);
    hydrogen_set.init(dm);
    nuclide_set.init(dm);
    spent_nuclide_set.init(dm);
    geometry_creator.set_nuclides_positions(nuclide_set.nuclides_array, dm);
}


void DiscreteManager::draw_neutrons(sf::RenderWindow& window, ParticlesSet particles_set, DataManager& dm) {
    for (int i = 0; i < particles_set.neutrons_array.size(); i++) {
        sf::CircleShape neutron_disk(dm.r_neutron * dm.ppcm);
        neutron_disk.setFillColor(sf::Color::Red);
        int x_neutron = (particles_set.neutrons_array[i].x - dm.r_neutron) * dm.ppcm;
        int y_neutron = (particles_set.neutrons_array[i].y - dm.r_neutron) * dm.ppcm;
        neutron_disk.setPosition(x_neutron, y_neutron);
        window.draw(neutron_disk);
    }
}

void DiscreteManager::draw_nuclides(sf::RenderWindow& window, DiscreteNuclidesSet nuclide_set, DataManager& dm) {
    for (int j = 0; j < nuclide_set.nuclides_array.size(); j++) {
        sf::CircleShape nuclide_disk(dm.r_nuclide * dm.ppcm);
        nuclide_disk.setFillColor(sf::Color::Green);
        

        int x_nuclide = (nuclide_set.nuclides_array[j].x - dm.r_nuclide) * dm.ppcm;
        int y_nuclide = (nuclide_set.nuclides_array[j].y - dm.r_nuclide) * dm.ppcm;
        nuclide_disk.setPosition(x_nuclide, y_nuclide);
        window.draw(nuclide_disk);
    }
}

void DiscreteManager::draw_spent_nuclides(sf::RenderWindow& window, DiscreteSpentNuclidesSet spent_nuclide_set, DataManager& dm) {
    for (int j = 0; j < spent_nuclide_set.nuclides_array.size(); j++) {
        float radius = spent_nuclide_set.nuclides_array[j].r;
        sf::CircleShape spent_nuclide_disk(radius * dm.ppcm);
        spent_nuclide_disk.setFillColor(sf::Color::Blue);        

        int x_spent_nuclide = (spent_nuclide_set.nuclides_array[j].x - radius) * dm.ppcm;
        int y_spent_nuclide = (spent_nuclide_set.nuclides_array[j].y - radius) * dm.ppcm;
        spent_nuclide_disk.setPosition(x_spent_nuclide, y_spent_nuclide);
        window.draw(spent_nuclide_disk);
    }
}


void DiscreteManager::draw_hydrogens(sf::RenderWindow& window, DiscreteHydrogensSet hydrogen_set, DataManager& dm) {
    for (int k = 0; k < hydrogen_set.hydrogens_array.size(); k++) {
        sf::CircleShape hydrogen_disk(dm.r_hydrogen * dm.ppcm);
        hydrogen_disk.setFillColor(sf::Color::Yellow);
        int x_h = (hydrogen_set.hydrogens_array[k].x - dm.r_hydrogen) * dm.ppcm;
        int y_h = (hydrogen_set.hydrogens_array[k].y - dm.r_hydrogen) * dm.ppcm;
        hydrogen_disk.setPosition(x_h, y_h);
        window.draw(hydrogen_disk);
    }
}


void DiscreteManager::set_text_parameters() {
    set_one_text_parameters(text, font);
    set_one_text_parameters(text2, font);
}

void DiscreteManager::set_one_text_parameters(sf::Text& text, sf::Font& font) {
    if (!font.loadFromFile("themes/arial.ttf"))
    {
        // error...
        cout << "Not loading the font !" << endl;
    }
    text.setFont(font); // font is a sf::Font
    // set the character size
    text.setCharacterSize(24); // in pixels, not points!
    // set the color
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
}

void DiscreteManager::draw_k_eff(ParticlesSet particles_set, int counter, int& nActuel, int& nAncien, sf::RenderWindow& window) {
    if (counter % 20 == 0) {
        nAncien = nActuel;
        nActuel = particles_set.neutrons_array.size();
    }
    float keff((float)nActuel / (float)nAncien);
    string keffText("keff = " + std::to_string(keff));
    text.setString(keffText);
    text.setPosition(100, 50);
    window.draw(text);
}


void DiscreteManager::draw_nb_neutrons(ParticlesSet particles_set, sf::RenderWindow& window) {
    text2.setPosition(100, 75);
    text2.setString("Nb neutrons = " + std::to_string(particles_set.neutrons_array.size()));
    text2.setFillColor(sf::Color::Red);
    window.draw(text2);
}

void DiscreteManager::draw_neutron_speed(ParticlesSet& particles_set, sf::RenderWindow& window) {
    particles_set.compute_mean_velocity();
    string mean_velocity("mean_velocity = " + std::to_string(particles_set.mean_velocity));
    text.setString(mean_velocity);
    text.setPosition(100, 100);
    window.draw(text);
}

void DiscreteManager::discrete_main(DataManager& dm) {    
    ControlRod control_rod = ControlRod(dm);
    sf::RectangleShape control_rod_shape(sf::Vector2f(control_rod.get_width() * dm.ppcm, control_rod.get_height() * dm.ppcm));
    control_rod_shape.setPosition(control_rod.get_x() * dm.ppcm, control_rod.get_y() * dm.ppcm);
    control_rod_shape.setFillColor(sf::Color(100, 100, 10));

    sf::RenderWindow window(sf::VideoMode(dm.x_window, dm.y_window), "VULCAN :  A Pedagogical Monte Carlo neutronics simulator");
    set_text_parameters();

    GUICreator gui_creator(window, dm);
    gui_creator.gui.setTarget(window);
    gui_creator.create_menu_discrete(dm, particles_set, hydrogen_set, nuclide_set, spent_nuclide_set, geometry_creator);

    int counter(0);
    int nb_neutrons_now = particles_set.neutrons_array.size();
    int nb_neutrons_old = nb_neutrons_now;

    while (window.isOpen()){  
        if (dm.continuous_simulation) {
            window.close();
        }
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                dm.keep_window_closed = true;
                window.close();
            }
            if (dm.control_rod_exists) {
                scene_manager.move_control_rod(event, control_rod, control_rod_shape, dm);
            }            
            gui_creator.gui.handleEvent(event);
        }        

        if (!dm.simulationPaused) {
            particles_set.rebound_on_walls(dm);
            hydrogen_set.rebound_on_walls(dm);
            nuclide_set.rebound_on_walls(dm);
            spent_nuclide_set.rebound_on_walls(dm);

            particles_set.remove_fled_neutrons(dm);

            reaction_manager.compute_reactions(dm, particles_set, nuclide_set, spent_nuclide_set, hydrogen_set);

            particles_set.take_one_step();
            hydrogen_set.take_one_step();
            nuclide_set.take_one_step();
            spent_nuclide_set.take_one_step();

            if (dm.control_rod_exists) {
                control_rod.absorb_neutrons(particles_set);
            }            
            counter++;
        } else {
            
            particles_set.restart_clocks();
            hydrogen_set.restart_clocks();
            nuclide_set.restart_clocks();
            spent_nuclide_set.restart_clocks();
        }
        window.clear();
        draw_neutrons(window, particles_set, dm);
        draw_nuclides(window, nuclide_set, dm);

        draw_spent_nuclides(window, spent_nuclide_set, dm);

        draw_hydrogens(window, hydrogen_set, dm);
        draw_k_eff(particles_set, counter, nb_neutrons_now, nb_neutrons_old, window);
        draw_nb_neutrons(particles_set, window);
        draw_neutron_speed(particles_set, window);
        gui_creator.gui.draw();
        if (dm.control_rod_exists) {
            window.draw(control_rod_shape);
        }
        window.display();
        
    }

    



}

