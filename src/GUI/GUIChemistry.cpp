#include "GUIChemistry.h"

GUIChemistry::GUIChemistry() {
}

GUIChemistry::GUIChemistry(DataManager& dm) {
    y_chemistry_panel = dm.y_chemistry_panel;
    text_color = sf::Color(204, 204, 255);   
    x_widget = 0.05 * dm.button_width;
    height = 12 * dm.dy;
}

void GUIChemistry::create_panel(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui) {    
    update_y_positions(dm);
    create_title(dm, panel);
    create_capture_label(dm, panel);    
    create_capture_slider(dm, panel, gui);
    create_scattering_label(dm, panel);
    create_scattering_slider(dm, panel, gui);
    create_fission_label(dm, panel);
    create_fission_slider(dm, panel, gui);
    create_density_label(dm, panel);
    create_density_slider(dm, panel, gui);
    create_nubar_label(dm, panel);
    create_nubar_slider(dm, panel, gui);
    create_material_buckling_label(dm, panel);
}

void GUIChemistry::update_y_positions(DataManager& dm) {
    y_title_label = y_chemistry_panel + 0 * dm.dy;
    y_material_buckling = y_chemistry_panel + 1 * dm.dy;
    y_capture_label = y_chemistry_panel + 2 * dm.dy;
    y_capture_slider = y_chemistry_panel + 3 * dm.dy;
    y_scattering_label = y_chemistry_panel + 4 * dm.dy;
    y_scattering_slider = y_chemistry_panel + 5 * dm.dy;
    y_fission_label = y_chemistry_panel + 6 * dm.dy;
    y_fission_slider = y_chemistry_panel + 7 * dm.dy;
    y_density_label = y_chemistry_panel + 8 * dm.dy;
    y_density_slider = y_chemistry_panel + 9 * dm.dy;
    y_nubar = y_chemistry_panel + 10 * dm.dy;
    y_nubar_slider = y_chemistry_panel + 11 * dm.dy;
}

void GUIChemistry::delete_panel(tgui::GuiSFML& gui, tgui::Panel::Ptr panel) {
    if (auto title_label = gui.get<tgui::Label>("title_label")) {
        panel->remove(title_label);
    }
    if (auto xs_c_label = gui.get<tgui::Label>("xs_c_label")) {
        panel->remove(xs_c_label);
    }
    if (auto xs_c_slider = gui.get<tgui::Slider>("xs_c_slider")) {
        panel->remove(xs_c_slider);
    }
    if (auto xs_s_label = gui.get<tgui::Label>("xs_s_label")) {
        panel->remove(xs_s_label);
    }
    if (auto xs_s_slider = gui.get<tgui::Slider>("xs_s_slider")) {
        panel->remove(xs_s_slider);
    }
    if (auto xs_f_label = gui.get<tgui::Label>("xs_f_label")) {
        panel->remove(xs_f_label);
    }
    if (auto xs_f_slider = gui.get<tgui::Slider>("xs_f_slider")) {
        panel->remove(xs_f_slider);
    }

    if (auto ad_label = gui.get<tgui::Label>("ad_label")) {
        panel->remove(ad_label);
    }
    if (auto ad_slider = gui.get<tgui::Slider>("ad_slider")) {
        panel->remove(ad_slider);
    }
    if (auto nubar_label = gui.get<tgui::Label>("nubar_label")) {
        panel->remove(nubar_label);
    }
    if (auto nubar_slider = gui.get<tgui::Slider>("nubar_slider")) {
        panel->remove(nubar_slider);
    }

    if (auto buckling_label = gui.get<tgui::Label>("buckling_label")) {
        panel->remove(buckling_label);
    }
}

void GUIChemistry::create_title(DataManager& dm, tgui::Panel::Ptr panel) {
    auto title_label = tgui::Label::create();
    title_label->setText(dm.chemistry_panel_title);
    title_label->setPosition(x_widget, y_title_label);
    title_label->setTextSize(dm.text_size_mini);
    title_label->getRenderer()->setTextColor(text_color);
    panel->add(title_label, "title_label");
}

void GUIChemistry::create_capture_label(DataManager& dm, tgui::Panel::Ptr panel) {
    auto xs_c_label = tgui::Label::create();
    xs_c_label->setText(dm.xs_c_text + std::to_string(dm.volu_array[0].material.sigma_c));
    xs_c_label->setPosition(x_widget, y_capture_label);
    xs_c_label->setTextSize(dm.text_size_mini);
    xs_c_label->getRenderer()->setTextColor(text_color);
    panel->add(xs_c_label, "xs_c_label");
}

void GUIChemistry::create_capture_slider(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML &gui) {
    auto xs_c_slider = tgui::Slider::create();
    xs_c_slider->setPosition(x_widget, y_capture_slider);
    xs_c_slider->setSize(dm.slider_width, dm.text_size_mini);
    //int minimum_c = 0.2 * dm.volu_array[0].material.sigma_c;
    //int maximum_c = 5 * dm.volu_array[0].material.sigma_c;
    xs_c_slider->setMinimum(0);
    xs_c_slider->setMaximum(1000);
    xs_c_slider->setValue(dm.volu_array[0].material.sigma_c);

    xs_c_slider->onValueChange([&]() {
        if (dm.selected_volume_index != 999) {
            float slider_index = gui.get<tgui::Slider>("xs_c_slider")->getValue();
            gui.get<tgui::Label>("xs_c_label")->setText(dm.xs_c_text + std::to_string(slider_index));
            dm.volu_array[dm.selected_volume_index].material.set_xs_c(slider_index);
            update_material_buckling(dm, gui);
        }
        });
    panel->add(xs_c_slider, "xs_c_slider");
}

void GUIChemistry::create_scattering_label(DataManager& dm, tgui::Panel::Ptr panel) {
    //SIGMA SCATTERING LABEL
    auto xs_s_label = tgui::Label::create();
    xs_s_label->setText(dm.xs_s_text + std::to_string(dm.volu_array[0].material.sigma_s));
    xs_s_label->setPosition(x_widget, y_scattering_label);
    xs_s_label->setTextSize(dm.text_size_mini);
    xs_s_label->getRenderer()->setTextColor(text_color);
    panel->add(xs_s_label, "xs_s_label");

}

void GUIChemistry::create_scattering_slider(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML &gui) {
    //SIGMA SCATTERING SLIDER
    auto xs_s_slider = tgui::Slider::create();
    xs_s_slider->setPosition(x_widget, y_scattering_slider);
    xs_s_slider->setSize(dm.slider_width, dm.text_size_mini);
    //int minimum_s = 0.2 * dm.volu_array[0].material.sigma_s;
    //int maximum_s = 50 * dm.volu_array[0].material.sigma_s;
    xs_s_slider->setMinimum(0);
    xs_s_slider->setMaximum(1000);
    xs_s_slider->setValue(dm.volu_array[0].material.sigma_s);

    xs_s_slider->onValueChange([&]() {
        if (dm.selected_volume_index != 999) {
            float slider_s_index = gui.get<tgui::Slider>("xs_s_slider")->getValue();
            gui.get<tgui::Label>("xs_s_label")->setText(dm.xs_s_text + std::to_string(slider_s_index));
            dm.volu_array[dm.selected_volume_index].material.set_xs_s(slider_s_index);
            update_material_buckling(dm, gui);
        }
        });
    panel->add(xs_s_slider, "xs_s_slider");
}


void GUIChemistry::create_fission_label(DataManager& dm, tgui::Panel::Ptr panel) {
    //SIGMA FISSION LABEL
    auto xs_f_label = tgui::Label::create();
    xs_f_label->setText(dm.xs_f_text + std::to_string(dm.volu_array[0].material.sigma_f));
    xs_f_label->setPosition(x_widget, y_fission_label);
    xs_f_label->setTextSize(dm.text_size_mini);
    xs_f_label->getRenderer()->setTextColor(text_color);
    panel->add(xs_f_label, "xs_f_label");
}

void GUIChemistry::create_fission_slider(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui) {
    //SIGMA FISSION SLIDER
    auto xs_f_slider = tgui::Slider::create();
    xs_f_slider->setPosition(x_widget, y_fission_slider);
    xs_f_slider->setSize(dm.slider_width, dm.text_size_mini);
    //int minimum_f = 0.2 * dm.volu_array[0].material.sigma_f;
    //int maximum_f = 2 * dm.volu_array[0].material.sigma_f;
    xs_f_slider->setMinimum(0);
    xs_f_slider->setMaximum(1000);
    xs_f_slider->setValue(dm.volu_array[0].material.sigma_f);

    xs_f_slider->onValueChange([&]() {
        if (dm.selected_volume_index != 999) {
            float slider_f_index = gui.get<tgui::Slider>("xs_f_slider")->getValue();
            gui.get<tgui::Label>("xs_f_label")->setText(dm.xs_f_text + std::to_string(slider_f_index));
            dm.volu_array[dm.selected_volume_index].material.set_xs_f(slider_f_index);
        }
        update_material_buckling(dm, gui);
        });
    panel->add(xs_f_slider, "xs_f_slider");

}

void GUIChemistry::create_density_label(DataManager& dm, tgui::Panel::Ptr panel) {
    auto ad_label = tgui::Label::create();
    ad_label->setPosition(x_widget, y_density_label);
    ad_label->setTextSize(dm.text_size_mini);
    ad_label->getRenderer()->setTextColor(text_color);
    std::stringstream ss;
    ss << std::scientific << dm.volu_array[0].material.atomic_density;
    ad_label->setText(dm.density_text + ss.str());
    panel->add(ad_label, "ad_label");
}

void GUIChemistry::create_density_slider(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui) {
    //ATOMIC DENSITY SLIDER
    auto ad_slider = tgui::Slider::create();
    ad_slider->setPosition(x_widget, y_density_slider);
    ad_slider->setSize(dm.slider_width, dm.text_size_mini);
    ad_slider->setMinimum(5e19);
    ad_slider->setMaximum(1e21);
    ad_slider->setValue(dm.volu_array[0].material.atomic_density);
    ad_slider->onValueChange([&]() {
        if (dm.selected_volume_index != 999) {
            float slider_index = gui.get<tgui::Slider>("ad_slider")->getValue();
            dm.volu_array[dm.selected_volume_index].material.set_ad(slider_index);
            update_material_buckling(dm, gui);
            std::stringstream ss;
            ss << std::scientific << slider_index;
            gui.get<tgui::Label>("ad_label")->setText(dm.density_text + ss.str());
        }
        });
    panel->add(ad_slider, "ad_slider");
}

void GUIChemistry::create_nubar_label(DataManager& dm, tgui::Panel::Ptr panel) {
    auto nubar_label = tgui::Label::create();
    nubar_label->setText(dm.nubar_text + std::to_string(dm.volu_array[0].material.nu_bar));
    nubar_label->setPosition(x_widget, y_nubar);
    nubar_label->setTextSize(dm.text_size_mini);
    nubar_label->getRenderer()->setTextColor(text_color);
    panel->add(nubar_label, "nubar_label");
}

void GUIChemistry::create_nubar_slider(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui) {
    auto nubar_slider = tgui::Slider::create();
    nubar_slider->setPosition(x_widget, y_nubar_slider);
    nubar_slider->setSize(dm.slider_width, dm.text_size_mini);
    nubar_slider->setMinimum(0);
    nubar_slider->setMaximum(30);
    nubar_slider->setValue(dm.volu_array[0].material.nu_bar);

    nubar_slider->onValueChange([&]() {
        if (dm.selected_volume_index != 999) {
            int slider_index = (int)gui.get<tgui::Slider>("nubar_slider")->getValue();
            gui.get<tgui::Label>("nubar_label")->setText(dm.nubar_text + to_string((float)slider_index/10));
            dm.volu_array[dm.selected_volume_index].material.set_nu_bar((float)slider_index/10);
            update_material_buckling(dm, gui);
        }
        });
    panel->add(nubar_slider, "nubar_slider");
}


void GUIChemistry::create_material_buckling_label(DataManager& dm, tgui::Panel::Ptr panel) {
    //MATERIAL BUCKLING
    auto buckling_label = tgui::Label::create();
    /*
    dm.volu_array[dm.selected_volume_index].material.compute_macroscropic_sigma();
    dm.volu_array[dm.selected_volume_index].material.compute_buckling();
    buckling_label->setText(dm.material_buckling_label_text +
        std::to_string(dm.volu_array[0].material.material_buckling));
        */
    buckling_label->setText(dm.material_buckling_label_text);
    buckling_label->setPosition(x_widget, y_material_buckling);
    buckling_label->setTextSize(dm.text_size_mini);
    buckling_label->getRenderer()->setTextColor(text_color);
    panel->add(buckling_label, "buckling_label");
}

void GUIChemistry::update_material_buckling(DataManager& dm, tgui::GuiSFML& gui) {
    if (dm.selected_volume_index != 999) {
        dm.volu_array[dm.selected_volume_index].material.compute_macroscropic_sigma();
        dm.volu_array[dm.selected_volume_index].material.compute_mean_free_path();
        dm.volu_array[dm.selected_volume_index].material.compute_buckling();
        gui.get<tgui::Label>("buckling_label")->setText(dm.material_buckling_label_text +
            std::to_string(dm.volu_array[dm.selected_volume_index].material.material_buckling));
    }
}


void GUIChemistry::reset_panel(DataManager& dm, tgui::GuiSFML& gui) {    
    if (dm.chemistry_panel_is_visible) {
        if (dm.selected_volume_index != 999) {
            gui.get<tgui::Label>("xs_c_label")->setText(dm.xs_c_text + std::to_string(dm.volu_array[dm.selected_volume_index].material.sigma_c));
            gui.get<tgui::Slider>("xs_c_slider")->setValue(dm.volu_array[dm.selected_volume_index].material.sigma_c);

            gui.get<tgui::Label>("xs_s_label")->setText(dm.xs_s_text + std::to_string(dm.volu_array[dm.selected_volume_index].material.sigma_s));
            gui.get<tgui::Slider>("xs_s_slider")->setValue(dm.volu_array[dm.selected_volume_index].material.sigma_s);

            gui.get<tgui::Label>("xs_f_label")->setText(dm.xs_f_text + std::to_string(dm.volu_array[dm.selected_volume_index].material.sigma_f));
            gui.get<tgui::Slider>("xs_f_slider")->setValue(dm.volu_array[dm.selected_volume_index].material.sigma_f);

            std::stringstream ss;
            ss << std::scientific << dm.volu_array[0].material.atomic_density;
            gui.get<tgui::Label>("ad_label")->setText(dm.density_text + ss.str());
            gui.get<tgui::Slider>("ad_slider")->setValue(dm.volu_array[dm.selected_volume_index].material.atomic_density);

            gui.get<tgui::Label>("nubar_label")->setText(dm.nubar_text + std::to_string(dm.volu_array[dm.selected_volume_index].material.nu_bar));
            gui.get<tgui::Slider>("nubar_slider")->setValue(dm.volu_array[dm.selected_volume_index].material.nu_bar);

            update_material_buckling(dm, gui);
            gui.get<tgui::Label>("buckling_label")->setText(dm.material_buckling_label_text + std::to_string(dm.volu_array[dm.selected_volume_index].material.material_buckling));
        }
    }    
}