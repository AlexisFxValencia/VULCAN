#include "GUICreator.h"



GUICreator::GUICreator(sf::RenderWindow& window, DataManager& dm) {
    present_input_file = "input_files/input.ns";
    gui.setTarget(window);
    gui_geometry = GUIGeometry(dm);
    gui_chemistry = GUIChemistry(dm);    
    gui_source = GUISource(dm);
    gui_minimal = GUIMinimal(dm);

    gui_keff = GUIKeff(dm);

    fullscreen = false;
    y_reset = 3 * dm.dy;
    x_widget = 0.05 * dm.button_width;
}

GUICreator::GUICreator() {

}


void GUICreator::create_gui(DataManager& dm, sf::RenderWindow& window, NeutronSet& neutron_set, ControlRod& control_rod, sf::RectangleShape& control_rod_shape) {
    panel = tgui::ScrollablePanel::create();
    panel->setPosition(dm.x_canvas, dm.y_up_margin);
    panel->setSize(dm.x_gui_panel, 900);
    panel->getRenderer()->setBackgroundColor(sf::Color(68, 59, 104));    
    gui.add(panel);
    panel->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    
    create_reset_button(dm, neutron_set, control_rod, control_rod_shape);    
    create_panels(dm, neutron_set);    
    create_menu(dm, neutron_set, control_rod, control_rod_shape);
}


void GUICreator::create_menu(DataManager& dm, NeutronSet& neutron_set, ControlRod& control_rod, sf::RectangleShape& control_rod_shape) {
    auto menu = tgui::MenuBar::create();
    menu->setHeight(dm.height_menu);
    create_loading_menu(dm, neutron_set, menu, control_rod, control_rod_shape);
    create_view_menu(dm, neutron_set, menu);
    create_simulation_menu(dm, neutron_set, menu, control_rod, control_rod_shape); 
    create_help_menu(dm, menu);
    gui.add(menu);
}

void GUICreator::create_menu_discrete(DataManager& dm, ParticlesSet& particles_set, DiscreteHydrogensSet& hydrogen_set, DiscreteNuclidesSet& nuclide_set, DiscreteSpentNuclidesSet& spent_nuclide_set, GeometryCreator& geometry_creator) {
    auto menu = tgui::MenuBar::create();
    menu->setHeight(dm.height_menu);
    menu->addMenuItem({ "File", "Load", "Discrete", "discrete.ns" });
    menu->connectMenuItem({ "File", "Load", "Discrete", "discrete.ns"}, [&]() {              
        reset_discrete_input(dm, particles_set, hydrogen_set, nuclide_set, spent_nuclide_set, geometry_creator, "input_files/discrete.ns");
        });
    menu->addMenuItem({ "File", "Load", "Discrete", "discrete_chain_reaction.ns" });
    menu->connectMenuItem({ "File", "Load", "Discrete", "discrete_chain_reaction.ns" }, [&]() {
        reset_discrete_input(dm, particles_set, hydrogen_set, nuclide_set, spent_nuclide_set, geometry_creator, "input_files/discrete_chain_reaction.ns");
        });
    menu->addMenuItem({ "File", "Load", "Discrete", "discrete_explosion.ns" });
    menu->connectMenuItem({ "File", "Load", "Discrete", "discrete_explosion.ns" }, [&]() {
        reset_discrete_input(dm, particles_set, hydrogen_set, nuclide_set, spent_nuclide_set, geometry_creator, "input_files/discrete_explosion.ns");
        });
    menu->addMenuItem({ "File", "Load", "Discrete", "discrete_small_and_big_particles.ns" });
    menu->connectMenuItem({ "File", "Load", "Discrete", "discrete_small_and_big_particles.ns" }, [&]() {
        reset_discrete_input(dm, particles_set, hydrogen_set, nuclide_set, spent_nuclide_set, geometry_creator, "input_files/discrete_small_and_big_particles.ns");
        }); 
    menu->addMenuItem({ "File", "Load", "Discrete", "discrete_potential.ns" });
    menu->connectMenuItem({ "File", "Load", "Discrete", "discrete_potential.ns" }, [&]() {
        reset_discrete_input(dm, particles_set, hydrogen_set, nuclide_set, spent_nuclide_set, geometry_creator, "input_files/discrete_potential.ns");
        });
    menu->addMenuItem({ "File", "Load", "Discrete", "Moderation", "discrete_moderation_mass_1.ns" });
    menu->connectMenuItem({ "File", "Load", "Discrete", "Moderation", "discrete_moderation_mass_1.ns" }, [&]() {
        reset_discrete_input(dm, particles_set, hydrogen_set, nuclide_set, spent_nuclide_set, geometry_creator, "input_files/discrete_moderation_mass_1.ns");
        });
    menu->addMenuItem({ "File", "Load", "Discrete", "Moderation", "discrete_moderation_mass_10.ns" });
    menu->connectMenuItem({ "File", "Load", "Discrete", "Moderation", "discrete_moderation_mass_10.ns" }, [&]() {
        reset_discrete_input(dm, particles_set, hydrogen_set, nuclide_set, spent_nuclide_set, geometry_creator, "input_files/discrete_moderation_mass_10.ns");
        });
    menu->addMenuItem({ "File", "Load", "Discrete", "Moderation", "discrete_moderation_mass_238.ns" });
    menu->connectMenuItem({ "File", "Load", "Discrete", "Moderation", "discrete_moderation_mass_238.ns" }, [&]() {
        reset_discrete_input(dm, particles_set, hydrogen_set, nuclide_set, spent_nuclide_set, geometry_creator, "input_files/discrete_moderation_mass_238.ns");
        });

    menu->addMenuItem({ "File", "Load", "Control Mode", "mass.ns" });
    menu->connectMenuItem({ "File", "Load", "Control Mode", "mass.ns" }, [&]() {
        dm.continuous_simulation = true; 
        dm.clear();
        dm.read("input_files/mass.ns");        
        });

    gui.add(menu);

    menu->addMenuItem({ "Settings", "Pause" });
    menu->connectMenuItem({ "Settings", "Pause" }, [&]() {
            if (dm.simulationPaused) {
                dm.simulationPaused = false;
            }
            else {
                dm.simulationPaused = true;         
            }
        });

    gui.add(menu);
}

void GUICreator::reset_discrete_input(DataManager& dm, ParticlesSet& particles_set, DiscreteHydrogensSet& hydrogen_set, DiscreteNuclidesSet& nuclide_set, DiscreteSpentNuclidesSet& spent_nuclide_set, GeometryCreator& geometry_creator, string input_name) {
    particles_set.neutrons_array.clear();
    nuclide_set.nuclides_array.clear();
    spent_nuclide_set.nuclides_array.clear();
    hydrogen_set.hydrogens_array.clear();
    dm.clear();
    dm.read(input_name);
    particles_set.init(dm);
    hydrogen_set.init(dm);
    nuclide_set.init(dm);
    spent_nuclide_set.init(dm);
    geometry_creator.set_nuclides_positions(nuclide_set.nuclides_array, dm);
}


void GUICreator::create_view_menu(DataManager& dm, NeutronSet& neutron_set, tgui::MenuBar::Ptr menu) {
    menu->addMenu("View");
    menu->addMenuItem({ "View", "Full Screen" });
    menu->addMenuItem({ "View", "Panel", "Keff Panel" });
    menu->addMenuItem({ "View", "Panel", "Source Panel" });
    menu->addMenuItem({ "View", "Panel", "Geometry Panel" });
    menu->addMenuItem({ "View", "Panel", "Chemistry Panel" });
    menu->addMenuItem({ "View", "Panel", "All Panel visibles" });

    menu->addMenuItem({ "View", "Plot", "Total neutrons plot" });
    menu->addMenuItem({ "View", "Plot", "Reset neutrons plot" });
    menu->addMenuItem({ "View", "Plot", "Detector plot" });

    menu->connectMenuItem({ "View", "Plot", "Total neutrons plot" }, [&]() {
        if (dm.display_plot) {
            dm.display_plot = false;
        }
        else {
            dm.display_plot = true;
        }
    });
    menu->connectMenuItem({ "View", "Plot", "Reset neutrons plot" }, [&]() {
        dm.reset_graph = true;        
    });
    menu->connectMenuItem({ "View", "Plot", "Detector plot" }, [&]() {
        if (dm.display_detector_plot) {
            dm.display_detector_plot = false;
        }
        else {
            dm.display_detector_plot = true;
        }
        });

    menu->connectMenuItem({ "View", "Full Screen" }, [&]() {
        if (fullscreen) {
            fullscreen = false;
            panel->getRenderer()->setOpacity(1);
            dm.x_canvas -= dm.x_gui_panel;
            neutron_set.x_canvas -= dm.x_gui_panel;
            for (int i = 0; i < neutron_set.neutrons_array.size(); i++) {
                neutron_set.neutrons_array[i].x_max -= dm.x_gui_panel / dm.ppcm;
            }
        }
        else {
            fullscreen = true;
            panel->getRenderer()->setOpacity(0);
            dm.x_canvas += dm.x_gui_panel;
            neutron_set.x_canvas += dm.x_gui_panel;
            for (int i = 0; i < neutron_set.neutrons_array.size(); i++) {
                neutron_set.neutrons_array[i].x_max += dm.x_gui_panel / dm.ppcm;
            }
        }
    });

    menu->connectMenuItem({ "View", "Panel", "Keff Panel" }, [&]() {
        if (dm.keff_panel_is_visible) {
            dm.keff_panel_is_visible = false;
        }
        else {
            dm.keff_panel_is_visible = true;
            fullscreen = false;
            panel->getRenderer()->setOpacity(1);
        }
        create_panels(dm, neutron_set);
        });
    
    menu->connectMenuItem({ "View", "Panel", "Source Panel" }, [&]() {
        if (dm.source_panel_is_visible) {
            dm.source_panel_is_visible = false;
        }
        else {
            dm.source_panel_is_visible = true;
            fullscreen = false;
            panel->getRenderer()->setOpacity(1);
        }
        create_panels(dm, neutron_set);
    });

    menu->connectMenuItem({ "View", "Panel", "Geometry Panel" }, [&]() {
        if (dm.geometry_panel_is_visible) {
            dm.geometry_panel_is_visible = false;
        }
        else {
            dm.geometry_panel_is_visible = true;
            fullscreen = false;
            panel->getRenderer()->setOpacity(1);
        }
        create_panels(dm, neutron_set);
    });

    menu->connectMenuItem({ "View", "Panel", "Chemistry Panel" }, [&, this]() {
        if (dm.chemistry_panel_is_visible) {
            dm.chemistry_panel_is_visible = false;
        }
        else {
            dm.chemistry_panel_is_visible = true;
            fullscreen = false;
            panel->getRenderer()->setOpacity(1);
        }
        create_panels(dm, neutron_set);
    });
    menu->connectMenuItem({ "View", "Panel", "All Panel visibles" }, [&, this]() {
        dm.source_panel_is_visible = true;
        dm.geometry_panel_is_visible = true;
        dm.chemistry_panel_is_visible = true;
        dm.keff_panel_is_visible = true;
        create_panels(dm, neutron_set);
    });
}

void GUICreator::create_simulation_menu(DataManager& dm, NeutronSet& neutron_set, tgui::MenuBar::Ptr menu, ControlRod& control_rod, sf::RectangleShape& control_rod_shape) {
    menu->addMenuItem({ "Simulation", "Reset Simulation (Reload current input file)" });
    menu->addMenuItem({ "Simulation", "Generate Source (Start Simulation)" });
    menu->addMenuItem({ "Simulation", "Enable/Disable neutrons creation" });
    menu->addMenuItem({ "Simulation", "Clear average keff" });

    menu->connectMenuItem({ "Simulation", "Reset Simulation (Reload current input file)" }, [&, this]() {
        dm.display_legend = true;
        gui_minimal.simulationPaused = false;
        dm.automatic_generated_sources = false;
        gui_keff.automatic_computed_keff = false;
        reset_input(dm, neutron_set, control_rod, control_rod_shape, present_input_file);
    });

    menu->connectMenuItem({ "Simulation", "Generate Source (Start Simulation)" }, [&, this]() {
        neutron_set.add_source_neutrons(dm);
        dm.display_legend = false;
    });

    menu->connectMenuItem({ "Simulation", "Enable/Disable neutrons creation" }, [&, this]() {
        if (dm.allow_neutron_creation) {
            dm.allow_neutron_creation = false;
        }
        else {
            dm.allow_neutron_creation = true;
        }
    });

    menu->connectMenuItem({ "Simulation", "Clear average keff" }, [&, this]() {
        if (neutron_set.batch_keff_vector.size() > 0) {
            neutron_set.batch_keff_vector.clear();
            neutron_set.averaged_keff = 0;
            string averaged_keff = to_string(neutron_set.averaged_keff);
            string rounded_averaged_keff = averaged_keff.substr(0, averaged_keff.find(".") + 3);
            gui.get<tgui::Label>("averaged_keff_label")->setText(dm.averaged_keff_label_text + rounded_averaged_keff);
        }         
        });
}

void GUICreator::create_loading_menu(DataManager& dm, NeutronSet& neutron_set, tgui::MenuBar::Ptr menu, ControlRod& control_rod, sf::RectangleShape& control_rod_shape) {
    menu->addMenu("File");
    menu->addMenuItem("Save"); 
    menu->addMenuItem({ "File", "Load", "input.ns" });

    menu->addMenuItem({ "File", "Load", "Control Mode", "mass.ns" });
    menu->addMenuItem({ "File", "Load", "Control Mode", "geometry_1.ns" });
    menu->addMenuItem({ "File", "Load", "Control Mode", "geometry_2.ns" });
    menu->addMenuItem({ "File", "Load", "Control Mode", "poison.ns" });
    menu->addMenuItem({ "File", "Load", "Control Mode", "concentration.ns" });

    menu->addMenuItem({ "File", "Load", "Environement Effect", "reflexions.ns" });
    menu->addMenuItem({ "File", "Load", "Environement Effect", "reflexions_disk.ns" });
    menu->addMenuItem({ "File", "Load", "Environement Effect", "infinite.ns" });
    menu->addMenuItem({ "File", "Load", "Environement Effect", "interactions.ns" });

    menu->addMenuItem({ "File", "Load", "Code Effect", "code_convergence.ns" });
    menu->addMenuItem({ "File", "Load", "Code Effect", "keff.ns" });
    menu->addMenuItem({ "File", "Load", "Code Effect", "stochastic.ns" });

    menu->addMenuItem({ "File", "Load", "Real Configuration", "maracas.ns" });
    menu->addMenuItem({ "File", "Load", "Real Configuration", "beam.ns" });

    menu->addMenuItem({ "File", "Load", "input_saved.ns" });
    menu->addMenuItem({ "File", "Load", "custom file to load" });

    menu->addMenuItem({ "File", "Load", "Discrete", "discrete.ns" });

    menu->connectMenuItem({ "File", "Load", "input.ns" }, [&]() {
        reset_input(dm, neutron_set, control_rod, control_rod_shape, "input_files/input.ns");
        });
    menu->connectMenuItem({ "File", "Load", "Control Mode", "mass.ns" }, [&]() {
        reset_input(dm, neutron_set, control_rod, control_rod_shape, "input_files/mass.ns");
        });
    menu->connectMenuItem({ "File", "Load", "Control Mode", "geometry_1.ns" }, [&]() {
        reset_input(dm, neutron_set, control_rod, control_rod_shape, "input_files/geometry_1.ns");
        });
    menu->connectMenuItem({ "File", "Load", "Control Mode", "geometry_2.ns" }, [&]() {
        reset_input(dm, neutron_set, control_rod, control_rod_shape, "input_files/geometry_2.ns");
        });
    menu->connectMenuItem({ "File", "Load", "Control Mode", "poison.ns" }, [&]() {
        reset_input(dm, neutron_set, control_rod, control_rod_shape, "input_files/poison.ns");
        });
    menu->connectMenuItem({ "File", "Load", "Control Mode", "concentration.ns" }, [&]() {
        reset_input(dm, neutron_set, control_rod, control_rod_shape, "input_files/concentration.ns");

        });

    menu->connectMenuItem({ "File", "Load", "Environement Effect", "reflexions.ns" }, [&]() {
        reset_input(dm, neutron_set, control_rod, control_rod_shape, "input_files/reflexions.ns");
        });
    menu->connectMenuItem({ "File", "Load", "Environement Effect", "reflexions_disk.ns" }, [&]() {
        reset_input(dm, neutron_set, control_rod, control_rod_shape, "input_files/reflexions_disk.ns");
        }); 
    menu->connectMenuItem({ "File", "Load", "Environement Effect", "interactions.ns" }, [&]() {
        reset_input(dm, neutron_set, control_rod, control_rod_shape, "input_files/interactions.ns");
        });
    menu->connectMenuItem({ "File", "Load", "Environement Effect", "infinite.ns" }, [&]() {
        reset_input(dm, neutron_set, control_rod, control_rod_shape, "input_files/infinite.ns");
        });

    menu->connectMenuItem({ "File", "Load", "Code Effect", "code_convergence.ns" }, [&]() {
        reset_input(dm, neutron_set, control_rod, control_rod_shape, "input_files/code_convergence.ns");
        });
    menu->connectMenuItem({ "File", "Load", "Code Effect", "keff.ns" }, [&]() {
        reset_input(dm, neutron_set, control_rod, control_rod_shape, "input_files/keff.ns");
        });
    menu->connectMenuItem({ "File", "Load", "Code Effect", "stochastic.ns" }, [&]() {
        reset_input(dm, neutron_set, control_rod, control_rod_shape, "input_files/stochastic.ns");
        });
    menu->connectMenuItem({ "File", "Load", "Real Configuration", "maracas.ns" }, [&]() {
        reset_input(dm, neutron_set, control_rod, control_rod_shape, "input_files/maracas.ns");
        });
    menu->connectMenuItem({ "File", "Load", "Real Configuration", "beam.ns" }, [&]() {
        reset_input(dm, neutron_set, control_rod, control_rod_shape, "input_files/beam.ns");
        });
    menu->connectMenuItem({ "File", "Load", "input_saved.ns" }, [&]() {
        reset_input(dm, neutron_set, control_rod, control_rod_shape, "input_files/input_saved.ns");
        });

    menu->connectMenuItem({ "File", "Load", "custom file to load" }, [&]() {
        display_loading_window(dm, neutron_set, control_rod, control_rod_shape);
        });

    menu->connectMenuItem({ "File", "Save" }, [&]() {
        dm.write("input_saved.ns");
        });

    menu->connectMenuItem({ "File", "Load", "Discrete", "discrete.ns" }, [&]() {
        reset_input(dm, neutron_set, control_rod, control_rod_shape, "input_files/discrete.ns");
        });
}

void GUICreator::create_help_menu(DataManager& dm, tgui::MenuBar::Ptr menu) {
    menu->addMenu("Help");
    menu->addMenu("About");

    menu->connectMenuItem({ "Help" }, [&]() {
        gui_window.display_help_window(dm);
        });
    menu->connectMenuItem({ "About" }, [&]() {
        gui_window.display_credits_window(dm);
        });
}



void GUICreator::create_panels(DataManager& dm, NeutronSet& neutron_set) {
    gui_minimal.delete_panel(gui, panel);
    gui_source.delete_panel(gui, panel);
    gui_geometry.delete_panel(gui, panel);
    gui_chemistry.delete_panel(gui, panel);
    gui_keff.delete_panel(gui, panel);

    gui_minimal.create_panel(dm, neutron_set, panel, gui);

    int y_current = 0;
    y_current += gui_minimal.height;
    if (dm.keff_panel_is_visible) {
        gui_keff.y_keff_panel = y_current;
        gui_keff.create_panel(dm, neutron_set, panel, gui);
        y_current += gui_keff.height;
    }
    if (dm.source_panel_is_visible) {
        gui_source.y_source_panel = y_current;
        gui_source.create_panel(dm, neutron_set, panel, gui);
        y_current += gui_source.height;
    }
    if (dm.geometry_panel_is_visible) {
        gui_geometry.y_geometry_panel = y_current;
        gui_geometry.create_panel(dm, neutron_set, panel, gui);
        y_current += gui_geometry.height;
    }
    if (dm.chemistry_panel_is_visible) {
        gui_chemistry.y_chemistry_panel = y_current;
        gui_chemistry.create_panel(dm, panel, gui);
        y_current += gui_chemistry.height;
    }

}



void GUICreator::create_reset_button(DataManager& dm, NeutronSet& neutron_set, ControlRod& control_rod, sf::RectangleShape& control_rod_shape) {
    //RESET BUTTON
    
    auto button_reset = tgui::Button::create(dm.reset_text);
    button_reset->setSize({ dm.button_width / 2, dm.button_height });
    button_reset->setPosition({ x_widget + (dm.button_width / 2), y_reset });
    button_reset->onPress([&]() {
        dm.display_legend = true;
        gui_minimal.simulationPaused = false;
        dm.automatic_generated_sources = false;
        gui_keff.automatic_computed_keff = false;
        
        
        reset_input(dm, neutron_set, control_rod, control_rod_shape, present_input_file);

        });
    panel->add(button_reset);
}

void GUICreator::reset_input(DataManager& dm, NeutronSet& neutron_set, ControlRod& control_rod, sf::RectangleShape& control_rod_shape, string input_name) {
    //dm.control_rod_exists = false;
    dm.clear();
    neutron_set.batch_keff_vector.clear(); 
    neutron_set.keff_estimator_coll_fiss = 0.0;
    neutron_set.averaged_keff = 0.0;
    neutron_set.sigma_keff = 0.0;
    neutron_set.reset_keff_counters();
    
    dm.read(input_name);


    present_input_file = input_name;
    //neutron_set.neutrons_array.clear();
    neutron_set.deactivate_neutrons_vector();
    
    control_rod = ControlRod(dm);
    control_rod_shape = sf::RectangleShape(sf::Vector2f(control_rod.get_width() * dm.ppcm, control_rod.get_height() * dm.ppcm));
    control_rod_shape.setPosition(control_rod.get_x() * dm.ppcm, control_rod.get_y() * dm.ppcm);

    create_panels(dm, neutron_set);

    if (dm.volu_array.size() > 0) {
        dm.volu_array[0].is_selected = true;
        dm.selected_volume_index = 0;
    }
    else {
        dm.selected_volume_index = 999;
    }

    reset_gui(dm);

    dm.display_legend = true;

    dm.reset_simulation = true;
}

void GUICreator::reset_gui(DataManager& dm) {    
    gui_minimal.reset_panel(dm, gui);
    gui_source.reset_panel(dm, gui);
    gui_chemistry.reset_panel(dm, gui);
    gui_geometry.reset_panel(dm, gui);
}


void GUICreator::display_loading_window(DataManager& dm, NeutronSet& neutron_set, ControlRod& control_rod, sf::RectangleShape& control_rod_shape) {

    sf::RenderWindow loading_window(sf::VideoMode(400, 300), "Loading file");
    
    loading_gui.setTarget(loading_window);

    auto loading_textbox = tgui::EditBox::create();
    loading_textbox->setDefaultText("nom du fichier, avec .ns");
    loading_textbox->setSize({ "66.67%", "12.5%" });
    loading_textbox->setPosition({ loading_window.getSize().x / 4 , loading_window.getSize().y / 4 });
    loading_gui.add(loading_textbox, "loading_textbox");

    auto loading_button = tgui::Button::create("charger le fichier .ns");
    loading_button->setSize({ "66.67%", "12.5%" });
    loading_button->setPosition({ loading_window.getSize().x / 4, loading_window.getSize().y / 4 + 30 });
    loading_button->onPress([&]() {
        tgui::String input_text = loading_gui.get<tgui::EditBox>("loading_textbox")->getText();
        cout << "loading : " << input_text << endl;

        if (file_exists("input_files/" + input_text.toStdString())) {
            reset_input(dm, neutron_set, control_rod, control_rod_shape, "input_files/" + input_text.toStdString());
            loading_gui.get<tgui::EditBox>("loading_textbox")->getRenderer()->setBackgroundColor(sf::Color::Green);
        }
        else {
            loading_gui.get<tgui::EditBox>("loading_textbox")->getRenderer()->setBackgroundColor(sf::Color::Red);
        }

      
        });
    loading_gui.add(loading_button, "loading_button");

    // run the program as long as the window is open
    while (loading_window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (loading_window.pollEvent(event))
        {
            loading_gui.handleEvent(event);
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                loading_gui.remove(loading_textbox);
                loading_gui.remove(loading_button);
                loading_window.close();
            }
        }
        loading_window.clear(sf::Color::White); //sf::Color(255, 255, 255)      
        loading_gui.draw();
        loading_window.display();
    }

}


inline bool GUICreator::file_exists(const std::string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}




