#include "GUIGeometry.h"


GUIGeometry::GUIGeometry() {
}

GUIGeometry::GUIGeometry(DataManager& dm) {
    y_geometry_panel = dm.y_geometry_panel;
    text_color = sf::Color(204, 255, 255);
    x_widget = 0.05 * dm.button_width;
    height = 9 * dm.dy;
}

void GUIGeometry::update_y_positions(DataManager& dm)
 {
    y_title_label = y_geometry_panel + 0 * dm.dy;

    y_param_1_label = y_geometry_panel + 1 * dm.dy;
    y_param_1_slider = y_geometry_panel + 2 * dm.dy;
    y_param_2_label = y_geometry_panel + 3 * dm.dy;
    y_param_2_slider = y_geometry_panel + 4 * dm.dy;

    y_geometrical_buckling = y_geometry_panel + 5 * dm.dy;
    y_ppcm_label = y_geometry_panel + 6 * dm.dy;
    y_ppcm_slider = y_geometry_panel + 7 * dm.dy;

    
}

void GUIGeometry::create_panel(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel, tgui::GuiSFML& gui) {
    update_y_positions(dm);
    create_title(dm, panel);
    create_param_1_label(dm, panel);
    create_param_1_slider(dm, panel, gui);
    create_param_2_label(dm, panel);
    create_param_2_slider(dm, panel, gui);    
    create_geometrical_buckling_label(dm, panel);
    create_ppcm_label(dm, panel);
    create_ppcm_slider(dm, neutron_set, panel, gui);
    
}


void GUIGeometry::delete_panel(tgui::GuiSFML& gui, tgui::Panel::Ptr panel) {
    if (auto title_label = gui.get<tgui::Label>("title_label")) {
        panel->remove(title_label);
    }
    if (auto param_1_label = gui.get<tgui::Label>("param_1_label")) {
        panel->remove(param_1_label);
    }
    if (auto param_1_slider = gui.get<tgui::Slider>("param_1_slider")) {
        panel->remove(param_1_slider);
    }
    if (auto param_2_label = gui.get<tgui::Label>("param_2_label")) {
        panel->remove(param_2_label);
    }
    if (auto param_2_slider = gui.get<tgui::Slider>("param_2_slider")) {
        panel->remove(param_2_slider);
    }
 
    if (auto geom_buckling_label = gui.get<tgui::Label>("geom_buckling_label")) {
        panel->remove(geom_buckling_label);
    }
    if (auto ppcm_label = gui.get<tgui::Label>("ppcm_label")) {
        panel->remove(ppcm_label);
    }
    if (auto ppcm_slider = gui.get<tgui::Slider>("ppcm_slider")) {
        panel->remove(ppcm_slider);
    }
}


void GUIGeometry::create_title(DataManager& dm, tgui::Panel::Ptr panel) {
    auto title_label = tgui::Label::create();
    title_label->setText(dm.geometry_panel_title);
    title_label->setPosition(x_widget, y_title_label);
    title_label->setTextSize(dm.text_size_mini);
    title_label->getRenderer()->setTextColor(text_color);
    panel->add(title_label, "title_label");
}


void GUIGeometry::create_param_1_label(DataManager& dm, tgui::Panel::Ptr panel) {
    string geom_param;
    if (dm.volu_array[0].type == "disk") {
        geom_param = dm.radius_text;
    }
    else if (dm.volu_array[0].type == "rectangle") {
        geom_param = dm.width_text;
    }
    auto param_1_label = tgui::Label::create();
    string dimension = std::to_string(dm.volu_array[0].param1);
    string rounded_dimension = dimension.substr(0, dimension.find(".") + 3);

    param_1_label->setText(geom_param + rounded_dimension);
    param_1_label->setPosition(x_widget, y_param_1_label);
    param_1_label->setTextSize(dm.text_size_mini);
    param_1_label->getRenderer()->setTextColor(text_color);
    panel->add(param_1_label, "param_1_label");
}

void GUIGeometry::update_labels(DataManager& dm, tgui::GuiSFML& gui) {
    if (dm.selected_volume_index != 999) {
        string geom_param;
        if (dm.volu_array[dm.selected_volume_index].type == "disk") {
            geom_param = dm.radius_text;
        }
        else if (dm.volu_array[dm.selected_volume_index].type == "rectangle") {
            geom_param = dm.width_text;
        }
        string dimension = std::to_string(dm.volu_array[dm.selected_volume_index].param1);
        string rounded_dimension = dimension.substr(0, dimension.find(".") + 3);
        gui.get<tgui::Label>("param_1_label")->setText(geom_param + rounded_dimension);
    }
}

void GUIGeometry::create_param_1_slider(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui) {
    auto param_1_slider = tgui::Slider::create();
    param_1_slider->setPosition(x_widget, y_param_1_slider);
    param_1_slider->setSize(dm.slider_width, dm.text_size_mini);
    param_1_slider->setMinimum(1);
    param_1_slider->setMaximum(250);
    param_1_slider->setValue(50);

    param_1_slider->onValueChange([&]() {
        if (dm.selected_volume_index != 999) {
            float slider_index = gui.get<tgui::Slider>("param_1_slider")->getValue();
            dm.volu_array[dm.selected_volume_index].param1 = slider_index / 10;

            string geom_param;
            if (dm.volu_array[dm.selected_volume_index].type == "disk") {
                geom_param = dm.radius_text;
            }
            else if (dm.volu_array[dm.selected_volume_index].type == "rectangle") {
                geom_param = dm.width_text;
            }

            string dimension = std::to_string(dm.volu_array[dm.selected_volume_index].param1);
            string rounded_dimension = dimension.substr(0, dimension.find(".") + 3);
            gui.get<tgui::Label>("param_1_label")->setText(geom_param + rounded_dimension);

            dm.volu_array[dm.selected_volume_index].compute_buckling();
            gui.get<tgui::Label>("geom_buckling_label")->setText(dm.geometrical_buckling_label_text + to_string(dm.volu_array[dm.selected_volume_index].geometrical_buckling));
        }
        });

    panel->add(param_1_slider, "param_1_slider");
}

void GUIGeometry::create_param_2_label(DataManager& dm, tgui::Panel::Ptr panel) {
    string geom_param = "";
    string rounded_dimension = "";
    auto param_2_label = tgui::Label::create();

    if (dm.selected_volume_index != 999) {
        if (dm.volu_array[dm.selected_volume_index].type == "rectangle") {
            geom_param = dm.height_text;            
            string dimension = std::to_string(dm.volu_array[dm.selected_volume_index].param2);
            rounded_dimension = dimension.substr(0, dimension.find(".") + 3);
            param_2_label->getRenderer()->setOpacity(1);
        } else if (dm.volu_array[dm.selected_volume_index].type == "disk") {
            geom_param = "N/A";
            param_2_label->getRenderer()->setOpacity(0);
        }
    }
    
    param_2_label->setText(geom_param + rounded_dimension);
    param_2_label->setPosition(x_widget, y_param_2_label);
    param_2_label->setTextSize(dm.text_size_mini);
    param_2_label->getRenderer()->setTextColor(text_color);
    panel->add(param_2_label, "param_2_label");
}

void GUIGeometry::create_param_2_slider(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui) {
    auto param_2_slider = tgui::Slider::create();
    param_2_slider->setPosition(x_widget, y_param_2_slider);
    param_2_slider->setSize(dm.slider_width, dm.text_size_mini);
    param_2_slider->setMinimum(1);
    param_2_slider->setMaximum(150);
    param_2_slider->setValue(50);

    if (dm.selected_volume_index != 999) {
        if (dm.volu_array[dm.selected_volume_index].type == "rectangle") {
            param_2_slider->getRenderer()->setOpacity(1);
        }
        else if (dm.volu_array[dm.selected_volume_index].type == "disk") {
            param_2_slider->getRenderer()->setOpacity(0);
        }
    }

    param_2_slider->onValueChange([&]() {
        if (dm.selected_volume_index != 999) {            
            if (dm.volu_array[dm.selected_volume_index].type == "rectangle") {
                float slider_index = gui.get<tgui::Slider>("param_2_slider")->getValue();
                dm.volu_array[dm.selected_volume_index].param2 = slider_index / 10;

                string dimension = std::to_string(dm.volu_array[dm.selected_volume_index].param2);
                string rounded_dimension = dimension.substr(0, dimension.find(".") + 3);
                gui.get<tgui::Label>("param_2_label")->setText(dm.height_text + rounded_dimension);

                dm.volu_array[dm.selected_volume_index].compute_buckling();
                gui.get<tgui::Label>("geom_buckling_label")->setText(dm.geometrical_buckling_label_text + to_string(dm.volu_array[dm.selected_volume_index].geometrical_buckling));
            }
            else if (dm.volu_array[dm.selected_volume_index].type == "disk") {
                gui.get<tgui::Label>("param_2_label")->getRenderer()->setOpacity(0);
                gui.get<tgui::Slider>("param_2_slider")->getRenderer()->setOpacity(0);
            }
        }        
     });

    panel->add(param_2_slider, "param_2_slider");
    
}


void GUIGeometry::create_geometrical_buckling_label(DataManager& dm, tgui::Panel::Ptr panel) {
    
    //GEOM BUCKLING
    auto geom_buckling_label = tgui::Label::create();
    string buckling = "999";
    if (dm.selected_volume_index != 999) {
        dm.volu_array[dm.selected_volume_index].compute_buckling();
        buckling = to_string(dm.volu_array[dm.selected_volume_index].geometrical_buckling);
    }
    

    geom_buckling_label->setText(dm.geometrical_buckling_label_text + buckling);
    geom_buckling_label->setPosition(x_widget, y_geometrical_buckling);
    geom_buckling_label->setTextSize(dm.text_size_mini);
    geom_buckling_label->getRenderer()->setTextColor(text_color);
    panel->add(geom_buckling_label, "geom_buckling_label");
}


void GUIGeometry::reset_panel(DataManager& dm, tgui::GuiSFML& gui) {
    if (dm.geometry_panel_is_visible) {
        if (dm.selected_volume_index != 999) {
            gui.get<tgui::Slider>("param_1_slider")->setValue(dm.volu_array[dm.selected_volume_index].param1 * 10);
            gui.get<tgui::Slider>("param_2_slider")->setValue(dm.volu_array[dm.selected_volume_index].param2 * 10);

            if (dm.volu_array[dm.selected_volume_index].type == "rectangle") {
                gui.get<tgui::Label>("param_2_label")->getRenderer()->setOpacity(1);
                gui.get<tgui::Slider>("param_2_slider")->getRenderer()->setOpacity(1);
            }
            else if (dm.volu_array[dm.selected_volume_index].type == "disk") {
                gui.get<tgui::Label>("param_2_label")->getRenderer()->setOpacity(0);
                gui.get<tgui::Slider>("param_2_slider")->getRenderer()->setOpacity(0);
            }

        }
        update_labels(dm, gui);
    }
}


void GUIGeometry::create_ppcm_label(DataManager& dm, tgui::Panel::Ptr panel) {
    auto ppcm_label = tgui::Label::create();
    ppcm_label->setText("ppcm :");
    ppcm_label->setPosition(x_widget, y_ppcm_label);
    ppcm_label->setTextSize(dm.text_size_mini);
    ppcm_label->getRenderer()->setTextColor(text_color);
    panel->add(ppcm_label, "ppcm_label");
}

void GUIGeometry::create_ppcm_slider(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel, tgui::GuiSFML& gui) {
    auto ppcm_slider = tgui::Slider::create();
    ppcm_slider->setPosition({ x_widget, y_ppcm_slider });
    ppcm_slider->setSize({ dm.slider_width, dm.text_size_mini });
    ppcm_slider->setMinimum(15);
    ppcm_slider->setMaximum(70);
    ppcm_slider->setValue(dm.ppcm);
    ppcm_slider->onValueChange([&] {
        float slider_index = gui.get<tgui::Slider>("ppcm_slider")->getValue();
        dm.ppcm = slider_index;
        string ppcm_text = std::to_string(dm.ppcm);
        cout << "Changing pixels per cm (ppcm) to " << dm.ppcm << endl;
        gui.get<tgui::Label>("ppcm_label")->setText(ppcm_text);
        neutron_set.update_wall_positions(dm);
        });
    panel->add(ppcm_slider, "ppcm_slider");
}

