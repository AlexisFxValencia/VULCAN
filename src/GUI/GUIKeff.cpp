#include "GUIKeff.h"

GUIKeff::GUIKeff() {


}


GUIKeff::GUIKeff(DataManager& dm) {
    y_keff_panel = dm.y_keff_panel;
    x_widget = 0.05 * dm.button_width;
	automatic_computed_keff = false;
    text_size_mini = 15;

    height = 7 * dm.dy;

    y_batch = 0 * dm.dy + y_keff_panel;
    y_keff = 1 * dm.dy + y_keff_panel;
    y_last_keff = 2 * dm.dy + y_keff_panel;
    y_averaged_keff = 3 * dm.dy + y_keff_panel;
    y_sigma = 4 * dm.dy + y_keff_panel;
    y_keff_automatic_button = 5 * dm.dy + y_keff_panel;
}

void GUIKeff::create_panel(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel, tgui::GuiSFML& gui) {
    create_batch_label(dm, neutron_set, panel);
    create_keff_label(dm, neutron_set, panel); 
    create_last_keff_label(dm, neutron_set, panel);
    create_averaged_keff_label(dm, neutron_set, panel);
    create_sigma_label(dm, neutron_set, panel);
    create_automatic_keff_button(dm, neutron_set, panel, gui);
}

void GUIKeff::delete_panel(tgui::GuiSFML& gui, tgui::Panel::Ptr panel) {   
    if (auto batch_label = gui.get<tgui::Label>("batch_label")) {
        panel->remove(batch_label);
    }
    if (auto keff_label = gui.get<tgui::Label>("keff_label")) {
        panel->remove(keff_label);
    }
    if (auto last_keff_label = gui.get<tgui::Label>("last_keff_label")) {
        panel->remove(last_keff_label);
    }
    if (auto averaged_keff_label = gui.get<tgui::Label>("averaged_keff_label")) {
        panel->remove(averaged_keff_label);
    }
    if (auto sigma_label = gui.get<tgui::Label>("sigma_label")) {
        panel->remove(sigma_label);
    }

    if (auto keff_automatic_button = gui.get<tgui::Button>("keff_automatic_button")) {
        panel->remove(keff_automatic_button);
    }
}

void GUIKeff::reset_panel(DataManager& dm, tgui::GuiSFML& gui) {
    tgui::Theme gui_theme{ "themes/GUITheme.txt" };
    gui.get<tgui::Label>("keff_label")->setText(dm.keff_label_text + "0");

    if (automatic_computed_keff) {
        gui.get<tgui::Button>("keff_automatic_button")->setRenderer(gui_theme.getRenderer("ActiveButton"));
    }
    else {
        gui.get<tgui::Button>("keff_automatic_button")->setRenderer(gui_theme.getRenderer("PassiveButton"));
    }
}

void GUIKeff::create_batch_label(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel) {
    auto batch_label = tgui::Label::create();
    batch_label->setText("batch number = 1");
    batch_label->setPosition(x_widget, y_batch);
    batch_label->setTextSize(text_size_mini);
    batch_label->getRenderer()->setTextColor(sf::Color::White);
    panel->add(batch_label, "batch_label");
}

void GUIKeff::create_keff_label(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel) {
    auto keff_label = tgui::Label::create();

    string keff = to_string(neutron_set.keff_estimator_coll_fiss);
    string rounded_keff = keff.substr(0, keff.find(".") + 3);
    keff_label->setText(dm.keff_label_text + rounded_keff);
    keff_label->setPosition(x_widget, y_keff);
    keff_label->setTextSize(text_size_mini);
    keff_label->getRenderer()->setTextColor(sf::Color::Yellow);
    panel->add(keff_label, "keff_label");

}

void GUIKeff::create_last_keff_label(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel) {
    auto last_keff_label = tgui::Label::create();
    string keff = to_string(neutron_set.keff_estimator_coll_fiss);
    string rounded_keff = keff.substr(0, keff.find(".") + 3);
    last_keff_label->setText(dm.last_keff_label_text + rounded_keff);
    last_keff_label->setPosition(x_widget, y_last_keff);
    last_keff_label->setTextSize(text_size_mini);
    last_keff_label->getRenderer()->setTextColor(sf::Color::Green);
    panel->add(last_keff_label, "last_keff_label");
}

void GUIKeff::create_averaged_keff_label(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel) {
    auto averaged_keff_label = tgui::Label::create();
    string keff = to_string(neutron_set.keff_estimator_coll_fiss);
    string rounded_keff = keff.substr(0, keff.find(".") + 3);
    averaged_keff_label->setText(dm.averaged_keff_label_text + rounded_keff);
    averaged_keff_label->setPosition(x_widget, y_averaged_keff);
    averaged_keff_label->setTextSize(text_size_mini);
    averaged_keff_label->getRenderer()->setTextColor(sf::Color::Green);
    panel->add(averaged_keff_label, "averaged_keff_label");
}

void GUIKeff::create_sigma_label(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel) {
    auto sigma_label = tgui::Label::create();
    string sigma = to_string(neutron_set.sigma);
    string rounded_sigma = sigma.substr(0, sigma.find(".") + 3);
    sigma_label->setText(dm.sigma_label_text + rounded_sigma);
    sigma_label->setPosition(x_widget, y_sigma);
    sigma_label->setTextSize(text_size_mini);
    sigma_label->getRenderer()->setTextColor(sf::Color::Green);
    panel->add(sigma_label, "sigma_label");
}

void GUIKeff::create_automatic_keff_button(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel, tgui::GuiSFML& gui) {
    auto keff_automatic_button = tgui::Button::create(dm.keff_automatic_button_text);
    keff_automatic_button->setSize({ dm.button_width, dm.button_height });
    keff_automatic_button->setPosition({ x_widget, y_keff_automatic_button });
    keff_automatic_button->onPress([&]() {
        if (automatic_computed_keff) {
            automatic_computed_keff = false;
            //gui.get<tgui::Button>("keff_automatic_button")->setText(manual_source_text);
            tgui::Theme gui_theme{ "themes/GUITheme.txt" };
            gui.get<tgui::Button>("keff_automatic_button")->setRenderer(gui_theme.getRenderer("PassiveButton"));
        }
        else {
            automatic_computed_keff = true;
            //gui.get<tgui::Button>("keff_automatic_button")->setText(automatic_source_text);
            tgui::Theme gui_theme{ "themes/GUITheme.txt" };
            gui.get<tgui::Button>("keff_automatic_button")->setRenderer(gui_theme.getRenderer("AutoButton"));
        }


        });
    panel->add(keff_automatic_button, "keff_automatic_button");

}

void GUIKeff::update_keff(DataManager& dm, NeutronSet& neutron_set, tgui::GuiSFML& gui) {
    string keff = to_string(neutron_set.keff_estimator_coll_fiss);
    string rounded_keff = keff.substr(0, keff.find(".") + 3);
    gui.get<tgui::Label>("keff_label")->setText(dm.keff_label_text + rounded_keff);    
}

void GUIKeff::update_all(DataManager& dm, NeutronSet& neutron_set, tgui::GuiSFML& gui) {
    string keff = to_string(neutron_set.keff_estimator_coll_fiss);
    string rounded_keff = keff.substr(0, keff.find(".") + 3);
    gui.get<tgui::Label>("last_keff_label")->setText(dm.last_keff_label_text + rounded_keff);    
    string averaged_keff = to_string(neutron_set.averaged_keff);
    string rounded_averaged_keff = averaged_keff.substr(0, averaged_keff.find(".") + 3);
    gui.get<tgui::Label>("averaged_keff_label")->setText(dm.averaged_keff_label_text + rounded_averaged_keff);    
    string sigma = to_string(neutron_set.sigma);
    string rounded_sigma = sigma.substr(0, sigma.find(".") + 3);
    gui.get<tgui::Label>("sigma_label")->setText(dm.sigma_label_text + rounded_sigma);
    gui.get<tgui::Label>("batch_label")->setText("batch number = " + to_string(1 + neutron_set.batch_keff_vector.size()));
}