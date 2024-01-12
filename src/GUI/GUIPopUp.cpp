#include "GUIPopUp.h"

GUIPopUp::GUIPopUp() {
    user_shape_counter = 0;
}


void GUIPopUp::create_new_volume_menu(DataManager& dm, int& x_popup, int& y_popup, NeutronSet& neutron_set, tgui::GuiSFML& gui) {
    delete_previous_menus(gui);
    auto new_volume_menu = tgui::ListBox::create();
    new_volume_menu->addItem("Creer un Disque");
    new_volume_menu->addItem("Creer un Rectangle");
    new_volume_menu->addItem("Creer un Neutron");
    new_volume_menu->addItem("Annuler");
    new_volume_menu->setItemHeight(30);
    new_volume_menu->setPosition(x_popup, y_popup);
    new_volume_menu->setSize(160, new_volume_menu->getItemHeight() * new_volume_menu->getItemCount());

    this->x_shape = (float)x_popup / (float)(dm.ppcm);
    this->y_shape = (float)y_popup / (float)(dm.ppcm);
    new_volume_menu->onItemSelect([&] {
        tgui::String user_choice = gui.get<tgui::ListBox>("new_volume_menu")->getSelectedItem();
        if (user_choice == "Creer un Disque") {
            create_disk(dm, gui);
        }
        else if (user_choice == "Creer un Rectangle") {
            create_rectangle(dm, gui);
        }
        else if (user_choice == "Creer un Neutron") {
            create_neutron(dm, neutron_set);
        }
        else if (user_choice == "Annuler") {
        }
        delete_previous_menus(gui);

        });
    gui.add(new_volume_menu, "new_volume_menu");
}

void GUIPopUp::create_disk(DataManager& dm, tgui::GuiSFML& gui) {
    float atomic_density = 9.48e20; //cm2
    int nu_bar = 2;
    float sigma_s = 15.12;
    float sigma_c = 98.71;
    float sigma_f = 585.1;
    sf::Color color = dm.generate_random_color();
    Material material = Material("user_material", color, atomic_density, nu_bar, sigma_s, sigma_c, sigma_f);
    cout << "Creation d'un disque !" << endl;
    int radius = 3;
    dm.highest_volume_priority++;
    Volume user_disk = Volume("user_disk_" + user_shape_counter, "disk", radius, 0, x_shape, y_shape, material, dm.highest_volume_priority);    
    dm.volu_array.push_back(user_disk);
    user_shape_counter++;

    
}

void GUIPopUp::create_rectangle(DataManager& dm, tgui::GuiSFML& gui) {
    float atomic_density = 9.48e20; //cm2
    int nu_bar = 2;
    float sigma_s = 15.12;
    float sigma_c = 98.71;
    float sigma_f = 585.1;
    sf::Color color = dm.generate_random_color();
    Material material = Material("user_material", color, atomic_density, nu_bar, sigma_s, sigma_c, sigma_f);        
    cout << "Creation d'un rectangle !" << endl;
    float width = 2;
    float height = 4;
    dm.highest_volume_priority++;
    Volume user_rectangle = Volume("user_rectangle_" + user_shape_counter, "rectangle", width, height, x_shape, y_shape, material, dm.highest_volume_priority);
    dm.volu_array.push_back(user_rectangle);
    user_shape_counter++;
}


void GUIPopUp::create_modify_volume_menu(DataManager& dm, NeutronSet& neutron_set, int& x_popup, int& y_popup, int& volume_index, tgui::GuiSFML& gui) {
    delete_previous_menus(gui);

    modify_volume_menu = tgui::ListBox::create();
    modify_volume_menu->addItem("Nom du volume : " + dm.volu_array[volume_index].name);
    modify_volume_menu->addItem("Materiau : " + dm.volu_array[volume_index].material.name);
    modify_volume_menu->addItem("Supprimer Volume");
    modify_volume_menu->addItem("Dupliquer Volume");
    modify_volume_menu->addItem("Changer couleur");
    modify_volume_menu->addItem("Creer un Neutron");
    modify_volume_menu->addItem("Annuler");
    modify_volume_menu->setItemHeight(30);
    modify_volume_menu->setPosition(x_popup, y_popup);
    modify_volume_menu->setSize(230, modify_volume_menu->getItemHeight() * modify_volume_menu->getItemCount());

    this->x_shape = (float)x_popup / (float)(dm.ppcm);
    this->y_shape = (float)y_popup / (float)(dm.ppcm);
    this->volume_to_modify_index = volume_index;

    modify_volume_menu->onItemSelect([&] {
        tgui::String user_choice = gui.get<tgui::ListBox>("modify_volume_menu")->getSelectedItem();
        if (user_choice == "Supprimer Volume") {
            cout << "Supprimer un volume !" << endl;
            dm.volu_array.erase(dm.volu_array.begin() + volume_to_modify_index);
            dm.selected_volume_index = 999;
        }
        else if (user_choice == "Dupliquer Volume") {
            copy_shape(dm, dm.volu_array[volume_to_modify_index]);
        }
        else if (user_choice == "Creer un Neutron") {
            create_neutron(dm, neutron_set);
        }
        
        delete_previous_menus(gui);
        });
    gui.add(modify_volume_menu, "modify_volume_menu");
}

void GUIPopUp::copy_shape(DataManager& dm, Volume& volume) {
    if (volume.type == "disk") {
        cout << "Copie d'un volume de type disque." << endl;
        int radius = 3;
        dm.highest_volume_priority++;
        Volume user_disk = Volume("user_disk_" + user_shape_counter, "disk", volume.param1, 0, x_shape, y_shape, volume.material, dm.highest_volume_priority);
        dm.volu_array.push_back(user_disk);
        user_shape_counter++;

    }
    else if (volume.type == "rectangle") {
        cout << "Copie d'un volume de type rectangle." << endl;
        float width = 2;
        float height = 4;
        dm.highest_volume_priority++;
        Volume user_rectangle = Volume("user_rectangle_" + user_shape_counter, "rectangle", volume.param1, volume.param2, x_shape, y_shape, volume.material, dm.highest_volume_priority);
        dm.volu_array.push_back(user_rectangle);
        user_shape_counter++;
    }

}



void GUIPopUp::create_neutron(DataManager& dm, NeutronSet& neutron_set) {
    float x_min = dm.r_neutron;
    float x_max = dm.x_canvas / dm.ppcm;
    float y_min = dm.r_neutron + 1;
    float y_max = dm.y_canvas / dm.ppcm;
    /*
    Particle neutron = Particle(10, 10, 7.0, -8.0, dm.r_neutron, dm.mass_neutron, x_min, x_max, y_min, y_max);
    neutron.is_source = true;
    neutron.setX(x_shape);
    neutron.setY(y_shape);
    neutron.set_last_position();
    neutron.set_random_velocity(dm.neutron_speed_magnitude);
    neutron_set.neutrons_array.push_back(neutron);
    */
    neutron_set.add_one_active_neutron(x_shape, y_shape, dm);


}



void GUIPopUp::delete_previous_menus(tgui::GuiSFML& gui) {
    if (auto modify_volume_menu_previous = gui.get<tgui::ListBox>("modify_volume_menu")) {
        gui.remove(modify_volume_menu_previous);
    }

    if (auto popmenu_previous = gui.get<tgui::ListBox>("new_volume_menu")) {
        gui.remove(popmenu_previous);
    }
}

