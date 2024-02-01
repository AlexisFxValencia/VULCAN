#include "ContinuousManager.h"

ContinuousManager::ContinuousManager(DataManager& dm) {
    scene_manager = SceneManager(dm); 
    neutron_set = NeutronSet(dm);  
    //cout << "dm.max_nb_neutrons = " << dm.max_nb_neutrons << endl;  
    //cout << "neutron_set = " << neutron_set.neutrons_array.size() << endl;  

    geometry_creator = GeometryCreator(dm);

    control_rod = ControlRod(dm);
    control_rod_shape = sf::RectangleShape(sf::Vector2f(control_rod.get_width() * dm.ppcm, control_rod.get_height() * dm.ppcm));
    control_rod_shape.setPosition(control_rod.get_x() * dm.ppcm, control_rod.get_y() * dm.ppcm);  

    float x_detector = 5.0;
    float y_detector = 6.0;
    float radius_detector = 3.0;
    Material vacuum = Material("void", sf::Color::Yellow, 1.0, 0, 0.0, 0.0, 0.0);
    dm.highest_volume_priority++;
    detector = Detector("detector", "disk", radius_detector, 0.0, x_detector, y_detector, vacuum, dm.highest_volume_priority);
    
    

    window.create(sf::VideoMode(dm.x_window, dm.y_window), "VULCAN :  A Pedagogical Monte Carlo neutronics simulator");
    window.setFramerateLimit(dm.fps);
}


void ContinuousManager::draw_neutrons(DataManager& dm) {
    for (int i = 0; i < neutron_set.neutrons_array.size(); i++) {
        if (neutron_set.neutrons_array[i].is_alive){
            sf::CircleShape neutron_disk(dm.r_neutron * dm.ppcm);
            neutron_disk.setFillColor(sf::Color::Red);
            int x_neutron = (neutron_set.neutrons_array[i].x - neutron_set.neutrons_array[i].r) * dm.ppcm;
            int y_neutron = (neutron_set.neutrons_array[i].y - neutron_set.neutrons_array[i].r) * dm.ppcm;
            neutron_disk.setPosition(x_neutron, y_neutron);
            window.draw(neutron_disk);
        }
    }
}


void ContinuousManager::draw_volumes(DataManager& dm) {
    for (int i = 0; i <dm.volu_array.size(); i++) {
        draw_one_volume(dm, dm.volu_array[i]);
    }
}


void ContinuousManager::draw_one_volume(DataManager& dm, Volume volume) {
    if (volume.type == "disk") {
        int radius = volume.param1 * dm.ppcm;        
        sf::CircleShape cercle(radius);
        int x_c = (volume.x - volume.param1) * dm.ppcm;
        int y_c = (volume.y - volume.param1) * dm.ppcm;
        cercle.setPosition(x_c, y_c);
        cercle.setFillColor(volume.material.color);   

        if (volume.is_selected) {
            cercle.setOutlineThickness(10);
            cercle.setOutlineColor(sf::Color::Green);
        }
        window.draw(cercle);
    }

    if (volume.type == "rectangle") {
        int width_r = volume.param1 * dm.ppcm;
        int height_r = volume.param2 * dm.ppcm;
        sf::RectangleShape rectangle(sf::Vector2f(width_r, height_r));
        int x_r = (volume.x - volume.param1 / 2) * dm.ppcm;
        int y_r = (volume.y - volume.param2 / 2) * dm.ppcm;
        rectangle.setPosition(x_r, y_r);
        rectangle.setFillColor(volume.material.color);

        if (volume.is_selected) {
            rectangle.setOutlineThickness(10);
            rectangle.setOutlineColor(sf::Color::Green);
        }

        window.draw(rectangle);
    }

}



void ContinuousManager::draw_max_nb_neutrons_message(DataManager& dm) {
    int x_message = (int)(0.15 * dm.x_canvas);
    int y_message = (int)(0.5 * dm.y_canvas);

    //blue  text
    sf::Font font;
    font.loadFromFile("themes/arial.ttf");
    sf::Text message;
    message.setFont(font);
    message.setCharacterSize(54);
    message.setFillColor(sf::Color::White);
    message.setString("The " + to_string(dm.max_nb_neutrons) + " neutrons limit has been reached ! ");
    message.setPosition(x_message, y_message);
    window.draw(message);
}


void ContinuousManager::draw_legend(DataManager& dm) {
    int x_neutron = (int)(0.1 * dm.x_canvas);
    int y_neutron = (int)(0.8 * dm.y_canvas);
    int r_neutron_pixel = dm.r_neutron * dm.ppcm;

    //neutron disk
    sf::CircleShape neutron_disk_legend(r_neutron_pixel);
    neutron_disk_legend.setFillColor(sf::Color::Red);
    neutron_disk_legend.setPosition(x_neutron, y_neutron);
    window.draw(neutron_disk_legend);

    //neutron text
    sf::Text neutron_legend;
    sf::Font font;
    font.loadFromFile("themes/arial.ttf");
    neutron_legend.setFont(font);
    neutron_legend.setCharacterSize(24);
    neutron_legend.setFillColor(sf::Color::Red);
    neutron_legend.setString(" : neutron");
    neutron_legend.setPosition(x_neutron + 3 * r_neutron_pixel, y_neutron - (r_neutron_pixel / 2));
    window.draw(neutron_legend);

    // green rectangle
    int width_r = 0.6 * dm.ppcm;
    int height_r = 0.4 * dm.ppcm;
    sf::RectangleShape rectangle(sf::Vector2f(width_r, height_r));
    int x_r = x_neutron;
    int y_r = y_neutron + 3 * r_neutron_pixel;
    rectangle.setPosition(x_r, y_r);
    rectangle.setFillColor(sf::Color::Green);
    window.draw(rectangle);

    //green rectangle text
    sf::Text rectangle_legend;
    rectangle_legend.setFont(font);
    rectangle_legend.setCharacterSize(24);
    rectangle_legend.setFillColor(sf::Color::Green);
    rectangle_legend.setString(dm.selected_shapetext);
    rectangle_legend.setPosition(x_neutron + 1.1 * width_r, y_r - (height_r / 4));
    window.draw(rectangle_legend);
}


void ContinuousManager::draw_walls(DataManager& dm) {
    // left wall
    int width = 0.2 * dm.ppcm;
    int height = dm.y_canvas - dm.height_menu;
    sf::Color color = sf::Color::Green;
    sf::RectangleShape left_wall(sf::Vector2f(width, height));
    left_wall.setPosition(0, dm.height_menu);
    left_wall.setFillColor(color);
    window.draw(left_wall);

    //right wall
    sf::RectangleShape right_wall(sf::Vector2f(width, height));
    right_wall.setPosition(dm.x_canvas-width, dm.height_menu);
    right_wall.setFillColor(color);
    window.draw(right_wall);


    //upper wall
    width = dm.x_canvas;
    height = 0.2 * dm.ppcm;    
    sf::RectangleShape upper_wall(sf::Vector2f(width, height));
    upper_wall.setPosition(0, dm.height_menu);
    upper_wall.setFillColor(color);
    window.draw(upper_wall);

    //lower wall
    sf::RectangleShape lower_wall(sf::Vector2f(width, height));
    lower_wall.setPosition(0, dm.y_canvas - height);
    lower_wall.setFillColor(color);
    window.draw(lower_wall);
}


void ContinuousManager::generate_sources( DataManager& dm, int time, int delay, NeutronSet& neutron_set) {
    if (dm.automatic_generated_sources) {        
        if (time % delay == 0) {
            neutron_set.add_source_neutrons(dm); 
        }
    }
}


void ContinuousManager::write_keff(ofstream& myfile) {
    string keff_estimator_coll_fiss = to_string(neutron_set.keff_estimator_coll_fiss);
    myfile.open("input_files/listing.ns", std::ios_base::app);//
    myfile << keff_estimator_coll_fiss << endl;
    myfile.close();
}


void ContinuousManager::initialize_graph(DataManager& dm) {
    float height_graph = 500.0;
    float width_graph = 400.0;
    sf::Vector2f location = sf::Vector2f(width_graph / 6, dm.y_window - 1.4 * height_graph);
    plot_.setSize(sf::Vector2f(width_graph, height_graph));
    plot_.setTitle("Nombre de neutrons");
    //plot_.setFont("./font.ttf");
    plot_.setFont("themes/arial.ttf");
    plot_.setXLabel("temps (s)");
    plot_.setYLabel("Nb neutrons");
    plot_.setBackgroundColor(sf::Color(255, 255, 255));
    plot_.setTitleColor(sf::Color::Black);
    plot_.setPosition(sf::Vector2f(location.x, location.y));
    sf::plot::Curve& curve = plot_.createCurve("nb_neutrons_curve", sf::Color::Red);
    curve.setFill(rand() % 2);
    curve.setThickness(3);
    curve.setColor(sf::Color(255, 87, 51));
    curve.setLimit(500);
}

void ContinuousManager::update_graph_curve(DataManager& dm) {
    sf::plot::Curve& curve = plot_.getCurve("nb_neutrons_curve");
    curve.addValue(neutron_set.nb_alive_neutrons);
    plot_.prepare();

    if (dm.reset_graph) {
        curve.reset();
        dm.reset_graph = false;
    }    
}


void ContinuousManager::initialize_detector_graph(DataManager& dm) {
    float height_graph = 500.0;
    float width_graph = 400.0;
    sf::Vector2f location = sf::Vector2f(width_graph / 6, dm.y_window - 1.4 * height_graph);
    detector_plot.setSize(sf::Vector2f(width_graph, height_graph));
    detector_plot.setTitle("Neutrons detector intensity");
    //plot_.setFont("./font.ttf");
    detector_plot.setFont("themes/arial.ttf");
    detector_plot.setXLabel("time (sec)");
    detector_plot.setYLabel("Intensity (neutrons/sec)");
    detector_plot.setBackgroundColor(sf::Color(255, 255, 255));
    detector_plot.setTitleColor(sf::Color::Black);
    detector_plot.setPosition(sf::Vector2f(location.x, location.y));
    sf::plot::Curve& detector_curve = detector_plot.createCurve("detector_curve", sf::Color::Blue);
    detector_curve.setFill(rand() % 2);
    detector_curve.setThickness(3);
    detector_curve.setColor(sf::Color(255, 87, 51));
    detector_curve.setLimit(500);
}

void ContinuousManager::update_detector_graph_curve() {
    sf::plot::Curve& detector_curve = detector_plot.getCurve("detector_curve");
    detector_curve.addValue(detector.intensity);
    detector_plot.prepare();

    /*
    if (dm.reset_graph) {
        curve.reset();
        dm.reset_graph = false;
    }
    */
    
}

void ContinuousManager::update_graphics(DataManager& dm, int time_ms) {
    if (dm.display_plot) {
        if ((time_ms - time_memorized_1) > 100) { // in ms
            time_memorized_1 = time_ms;
            update_graph_curve(dm);

        }
    }


    if (dm.display_detector_plot) {
        if (detector_index == -1) {
            detector_index = dm.volu_array.size();
            dm.volu_array.push_back(detector);
        }
        if (detector_index > -1) {
            detector.x = dm.volu_array[detector_index].x;
            detector.y = dm.volu_array[detector_index].y;
            detector.param1 = dm.volu_array[detector_index].param1;
            detector.param2 = dm.volu_array[detector_index].param2;
            detector.detects(neutron_set);

            if ((time_ms - time_memorized_2) > detector.detection_period) {
                time_memorized_2 = time_ms;
                detector.update_intensity(neutron_set);
                update_detector_graph_curve();
            }
        }

    }
    if (!dm.display_detector_plot && detector_index > -1) {
        dm.delete_one_volume("detector");
        detector_index = -1;
    }
}


void ContinuousManager::draw_components(GUICreator& gui_creator, DataManager& dm) {
    draw_volumes(dm);
    draw_neutrons(dm);

    
    if (neutron_set.nb_alive_neutrons >= dm.max_nb_neutrons) {
        draw_max_nb_neutrons_message(dm);
    }
    

    if (dm.display_legend) {
        draw_legend(dm);
    }

    if (dm.reflexions_activated) {
        draw_walls(dm);
    }

    if (dm.control_rod_exists) {
        window.draw(control_rod_shape);
    }


    gui_creator.gui.draw();



    if (dm.display_plot) {
        window.draw(plot_);
    }


    if (dm.display_detector_plot) {
        window.draw(detector_plot);
    }
}



void ContinuousManager::continuous_main(DataManager& dm) {
    detector.init();
    initialize_graph(dm);
    initialize_detector_graph(dm);
    

    GUICreator gui_creator(window, dm);
    if (dm.volu_array.size() > 0) {
        dm.volu_array[0].is_selected = true;
        dm.selected_volume_index = 0;
    }
    gui_creator.create_gui(dm, window, neutron_set, control_rod, control_rod_shape);

    ofstream myfile;
    myfile.open("input_files/listing.ns");//
    myfile << "Keff of the batches simulated:" << endl;
    myfile.close();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                dm.keep_window_closed = true;
                window.close();                
            }
            if (dm.control_rod_exists) {
                scene_manager.move_control_rod(event, control_rod, control_rod_shape, dm);
            }
            scene_manager.move_selected_volume(event, dm);
            scene_manager.move_volume_with_arrows(event, dm);
            scene_manager.select_several_volumes(event, dm, gui_creator);
            scene_manager.user_manages_volume(event, dm, geometry_creator, gui_creator, neutron_set);
            scene_manager.user_deletes_volume(event, dm);
            scene_manager.delete_pop_up_menus(event, dm, gui_creator);            

            if (dm.display_detector_plot) {
                scene_manager.drag_plot(event, dm, detector_plot);
            }
            if (dm.display_plot) {
                scene_manager.drag_plot(event, dm, plot_);
            }

            gui_creator.gui.handleEvent(event);
        }

       
        if (dm.reset_simulation && dm.display_detector_plot) {
            detector_index = dm.volu_array.size();
            dm.volu_array.push_back(detector);
            dm.reset_simulation = false;
        }
        


        if (!gui_creator.gui_minimal.simulationPaused) {
            
            neutron_set.check_delayed_neutrons_activation(dm);

            neutron_set.compute_neutron_lives(dm);

            if (dm.control_rod_exists) {
                control_rod.absorb_neutrons(neutron_set);
            }

            int time = static_cast<int>(clock.getElapsedTime().asSeconds() * 20);
            //int renormalization_delay = dm.renormalization_delay * 20; // a traiter car pose pb avec le nouveau mode
            //neutron_set.renormalize(dm, dm.nb_source, true, time, renormalization_delay);

            int source_delay = dm.add_source_delay * 20;
            generate_sources(dm, time, source_delay, neutron_set);
          


            //neutron_set.compute_keff(dm);
            gui_creator.gui_minimal.update_nb_neutrons(dm, neutron_set, gui_creator.gui);
            if (dm.keff_panel_is_visible) {
                gui_creator.gui_keff.update_keff(dm, neutron_set, gui_creator.gui);
                if ((neutron_set.nb_captured_neutrons + neutron_set.nb_fissioned_neutrons + neutron_set.nb_fled_neutrons) >= dm.nb_source) {
                    gui_creator.gui_keff.update_all(dm, neutron_set, gui_creator.gui);
                    write_keff(myfile);
                    neutron_set.reset_keff_counters();
                    if (gui_creator.gui_keff.automatic_computed_keff) {
                        neutron_set.generate_new_batch(dm);
                    }
                }
            }

            int time_ms = static_cast<int>(clock.getElapsedTime().asMilliseconds());

            update_graphics(dm, time_ms);
            

                       
        }
        else {
            neutron_set.restart_clocks();            
        }
        

        
        window.clear();
        draw_components(gui_creator, dm);
        window.display();
        
        if (dm.continuous_simulation == false) {
            window.close();
        }
    }
}

