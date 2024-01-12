#include "SceneManager.h"

SceneManager::SceneManager(DataManager& dm) {
    mouseClicked = false;
    dragging = false;
    control_pressed = false;    
}

SceneManager::SceneManager() {
}


void SceneManager::move_control_rod(sf::Event event, ControlRod& control_rod, sf::RectangleShape& control_rod_shape, DataManager& dm) {
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Up:
            control_rod.move_up(dm);
            break;
        case sf::Keyboard::Down:
            control_rod.move_down(dm);
            break;
        case sf::Keyboard::Right:
            control_rod.move_right(dm);
            break;
        case sf::Keyboard::Left:
            control_rod.move_left(dm);
            break;
        }

        control_rod_shape.setPosition(control_rod.get_x() * dm.ppcm, control_rod.get_y() * dm.ppcm);
    }
}

void SceneManager::select_volume(sf::Event event, DataManager& dm, GeometryCreator& geometry_creator, GUICreator& gui_creator) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && event.mouseButton.x < (dm.x_window - dm.x_gui_panel))    {
        dm.selected_volume_index = 999;
        for (int i = 0; i < dm.volu_array.size(); i++) {
            if (dm.volu_array[i].contains(event.mouseButton.x / dm.ppcm, event.mouseButton.y / dm.ppcm)) {                        
                dm.volu_array[i].is_selected = true; 
                dm.selected_volume_index = i;
                gui_creator.reset_gui(dm);                        
            }
            else {
                dm.volu_array[i].is_selected = false;
            }
        } 
    }
}

void SceneManager::move_selected_volume(sf::Event event, DataManager& dm) {
    for (int i = 0; i < dm.volu_array.size(); i++){
        if (dm.volu_array[i].is_selected) {
            if (event.type == sf::Event::KeyPressed){
                switch (event.key.code){
                case sf::Keyboard::Z:
                    dm.volu_array[i].y -= dm.delta_rod;
                    break;
                case sf::Keyboard::S:
                    dm.volu_array[i].y += dm.delta_rod;
                    break;
                case sf::Keyboard::D:
                    dm.volu_array[i].x += dm.delta_rod;
                    break;
                case sf::Keyboard::Q:
                    dm.volu_array[i].x -= dm.delta_rod;
                    break;
                }

            }
        }
    }    
}


void SceneManager::move_volume_with_arrows(sf::Event event, DataManager& dm) {
    for (int i = 0; i < dm.volu_array.size(); i++) {
        if (dm.volu_array[i].arrow_moves_allowed) {
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::Up:
                    dm.volu_array[i].y -= dm.delta_rod;
                    break;
                case sf::Keyboard::Down:
                    dm.volu_array[i].y += dm.delta_rod;
                    break;
                case sf::Keyboard::Right:
                    dm.volu_array[i].x += dm.delta_rod;
                    break;
                case sf::Keyboard::Left:
                    dm.volu_array[i].x -= dm.delta_rod;
                    break;
                }
            }
        }
    }
}


void SceneManager::user_deletes_volume(sf::Event event, DataManager& dm) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Delete) {
        for (int i = dm.volu_array.size() - 1; i > -1 ; i--) {
            if (dm.volu_array[i].is_selected) {
                if (dm.selected_volume_index = i) {
                    dm.selected_volume_index = 999;
                }
                dm.volu_array.erase(dm.volu_array.begin() + i);
            }
        }
        /*
        if (dm.selected_volume_index != 999) {
            cout << "erase a volume !" << endl;
            dm.volu_array.erase(dm.volu_array.begin() + dm.selected_volume_index);
            dm.selected_volume_index = 999;
        }
        */

    }
}

void SceneManager::user_manages_volume(sf::Event event, DataManager& dm, GeometryCreator& geometry_creator, GUICreator& gui_creator, NeutronSet& neutron_set) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
        int x = event.mouseButton.x;
        int y = event.mouseButton.y;

        for (int i = 0; i < dm.volu_array.size(); i++) {
            if (dm.volu_array[i].contains((float)x/dm.ppcm, (float)y/dm.ppcm)) {
                gui_creator.gui_popup.create_modify_volume_menu(dm, neutron_set, x, y, i, gui_creator.gui);
                return;
            }                
        }             
         gui_creator.gui_popup.create_new_volume_menu(dm, x, y, neutron_set, gui_creator.gui);
         return;        
    }
}


void SceneManager::drag_volume(sf::Event event, DataManager& dm, GUICreator& gui_creator) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && event.mouseButton.x < (dm.x_window - dm.x_gui_panel)) {
         dm.selected_volume_index = 999;
        for (int i = 0; i < dm.volu_array.size(); i++) {
            if (dm.volu_array[i].contains(event.mouseButton.x / dm.ppcm, event.mouseButton.y / dm.ppcm)) {
                dm.volu_array[i].is_selected = true;
                dm.selected_volume_index = i;
                gui_creator.reset_gui(dm);

                dragging = true;
                mouseClicked = true;
                mouseX = (float)event.mouseButton.x / (float)dm.ppcm;
                mouseY = (float)event.mouseButton.y / (float)dm.ppcm;
                decentering.x = mouseX - dm.volu_array[dm.selected_volume_index].x;
                decentering.y = mouseY - dm.volu_array[dm.selected_volume_index].y;
                
            }
            else {
                dm.volu_array[i].is_selected = false;
                
                

            }
        }
        
    }
    //LMB released
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){
        mouseClicked = false;
        dragging = false;        
    }


 
    if (event.type == sf::Event::MouseMoved){       
        if (dragging == true){
            
            mouseX = (float)event.mouseMove.x / (float)dm.ppcm;
            mouseY = (float)event.mouseMove.y / (float)dm.ppcm;

            dm.volu_array[dm.selected_volume_index].x = mouseX - (decentering.x);
            dm.volu_array[dm.selected_volume_index].y = mouseY - (decentering.y);
            
        }
    }

    

}



void SceneManager::drag_plot(sf::Event event, DataManager& dm, sf::plot::Plot& plot) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        //cout << "trying to move graph" << endl;

        if (plot.getPosition().x < event.mouseButton.x && event.mouseButton.x < plot.getPosition().x + plot.getSize().x) {
            if (plot.getPosition().y < event.mouseButton.y && event.mouseButton.y < plot.getPosition().y + plot.getSize().y) {
                cout << "click in the middle of the graph" << endl;
                dragging_plot = true;
                mouseClicked = true;
                decentering_plot.x = event.mouseButton.x - plot.getPosition().x;
                decentering_plot.y = event.mouseButton.y - plot.getPosition().y;
            }
        }        
    }
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        //cout << "release button" << endl;
        mouseClicked = false;
        dragging_plot = false;
    }

    if (event.type == sf::Event::MouseMoved) {        
        if (dragging_plot == true) {
            //cout << "dragging graph" << endl;
            sf::Vector2f location = sf::Vector2f(event.mouseMove.x - decentering_plot.x, event.mouseMove.y - decentering_plot.y);
            plot.setPosition(sf::Vector2f(location.x, location.y));

        }
    }
}







void SceneManager::select_several_volumes(sf::Event event, DataManager& dm, GUICreator& gui_creator) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        control_pressed = false;
        dragging = false;
        for (int i = 0; i < dm.volu_array.size(); i++) {
            dm.volu_array[i].is_selected = false;
            sf::Vector2f v1(0, 0);
            dm.volu_array[i].decentering = v1;
            dm.selected_volume_index = 999;
        }
    }


    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::LControl) {
        control_pressed = true;
    }
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::LControl) {
        control_pressed = false;              
    }

    
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && event.mouseButton.x < (dm.x_window - dm.x_gui_panel)) {
        dragging = true; 
        dm.selected_volume_index = 999;
        for (int i = 0; i < dm.volu_array.size(); i++) {
            if (dm.volu_array[i].contains(event.mouseButton.x / dm.ppcm, event.mouseButton.y / dm.ppcm)) {
                mouseX = (float)event.mouseButton.x / (float)dm.ppcm;
                mouseY = (float)event.mouseButton.y / (float)dm.ppcm;
                sf::Vector2f v1(mouseX - dm.volu_array[i].x, mouseY - dm.volu_array[i].y);
                dm.volu_array[i].decentering = v1;
                if (!control_pressed && dm.selected_volume_index != 999) {
                    dm.volu_array[dm.selected_volume_index].is_selected = false;
                }
                dm.selected_volume_index = i;
                dm.volu_array[i].is_selected = true;
            }
            else {
                if (!control_pressed) {
                    dm.volu_array[i].is_selected = false;
                }
            }     
        }
        gui_creator.reset_gui(dm);
    }
    

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        dragging = false;
    }


    if (event.type == sf::Event::MouseMoved) {
        if (dragging == true) {
            mouseX = (float)event.mouseMove.x / (float)dm.ppcm;
            mouseY = (float)event.mouseMove.y / (float)dm.ppcm;        

            for (int i = 0; i < dm.volu_array.size(); i++) {
                if (dm.volu_array[i].is_selected) {
                    //cout << " dm.volu_array[i].decentering.x " << dm.volu_array[i].decentering.x << " dm.volu_array[i].decentering.y " << dm.volu_array[i].decentering.y << endl;
                    dm.volu_array[i].x = mouseX - dm.volu_array[i].decentering.x;
                    dm.volu_array[i].y = mouseY - dm.volu_array[i].decentering.y;
                }
            }
        }
    }
    
    
}


void SceneManager::delete_pop_up_menus(sf::Event event, DataManager& dm, GUICreator& gui_creator) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        gui_creator.gui_popup.delete_previous_menus(gui_creator.gui);
    }

    /*
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && event.mouseButton.x < (dm.x_window - dm.x_gui_panel)) {
        
        bool none_volume_selected = true;
        for (int i = 0; i < dm.volu_array.size(); i++) {
            if (dm.volu_array[i].is_selected) {
                none_volume_selected = false;
            }
        }
        if (none_volume_selected) {
            gui_creator.delete_previous_menus(gui_creator.gui);
        }
        
        
    }
    */
}
