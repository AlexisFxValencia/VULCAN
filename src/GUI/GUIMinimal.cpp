#include "GUIMinimal.h"

GUIMinimal::GUIMinimal() {
}

GUIMinimal::GUIMinimal(DataManager& dm) {
	y_minimal_panel = 0;
	text_size_mini = 15;
    simulationPaused = false;
    x_widget = 0.05 * dm.button_width;
    update_y_positions(dm);
    height = 5*dm.dy;
}

void GUIMinimal::update_y_positions(DataManager& dm) {
    y_nb_neutrons = 1 * dm.dy;
    y_source_button = 2 * dm.dy;
    y_pause_button = 3 * dm.dy;
    //y_reset = 3 * dy;    
    y_reflexion_button = 4 * dm.dy;
}

void GUIMinimal::create_panel(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel, tgui::GuiSFML& gui) {
    create_nb_neutrons_label(dm, neutron_set, panel);
    create_sources_button(dm, neutron_set, panel);
    create_pause_button(dm, panel, gui);
    create_reflexion_button(dm, gui, panel);
}

void GUIMinimal::delete_panel(tgui::GuiSFML& gui, tgui::Panel::Ptr panel) {
    
    if (auto nb_neutrons_label = gui.get<tgui::Label>("nb_neutrons_label")) {
        panel->remove(nb_neutrons_label);
    }
    if (auto sources_button = gui.get<tgui::Button>("sources_button")) {
        panel->remove(sources_button);
    }
    if (auto pause_button = gui.get<tgui::Button>("pause_button")) {
        panel->remove(pause_button);
    }
    if (auto rebound_button = gui.get<tgui::Button>("rebound_button")) {
        panel->remove(rebound_button);
    }
}

void GUIMinimal::reset_panel(DataManager& dm, tgui::GuiSFML& gui) {
    tgui::Theme gui_theme{ "themes/GUITheme.txt" };

    gui.get<tgui::Button>("pause_button")->setText(dm.pause_text);
    if (simulationPaused) {
        gui.get<tgui::Button>("pause_button")->setRenderer(gui_theme.getRenderer("ActiveButton"));
    }
    else {
        gui.get<tgui::Button>("pause_button")->setRenderer(gui_theme.getRenderer("PassiveButton"));
    }

    if (dm.reflexions_activated) {
        gui.get<tgui::Button>("rebound_button")->setText(dm.deactivate_reflexion_text);
        gui.get<tgui::Button>("rebound_button")->setRenderer(gui_theme.getRenderer("ActiveButton"));
    }
    else {
        gui.get<tgui::Button>("rebound_button")->setText(dm.activate_reflexion_text);
        gui.get<tgui::Button>("rebound_button")->setRenderer(gui_theme.getRenderer("PassiveButton"));
    }

}


void GUIMinimal::create_nb_neutrons_label(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel) {
    auto nb_neutrons_label = tgui::Label::create();
    nb_neutrons_label->setText(to_string(neutron_set.get_nb_alive_neutrons()) + " neutrons actifs");
    nb_neutrons_label->setPosition(x_widget, y_nb_neutrons);
    nb_neutrons_label->setTextSize(20);
    nb_neutrons_label->getRenderer()->setTextColor(sf::Color::White);
    panel->add(nb_neutrons_label, "nb_neutrons_label");
}

void GUIMinimal::create_sources_button(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel) {
    //SOURCES BUTTON
    auto sources_button = tgui::Button::create(dm.generate_source_text);
    sources_button->setSize({ dm.button_width, dm.button_height });
    sources_button->setPosition({ x_widget, y_source_button });
    sources_button->onPress([&]() {
        neutron_set.add_source_neutrons(dm);        
        dm.display_legend = false;
        });
    panel->add(sources_button, "sources_button");
}

void GUIMinimal::create_pause_button(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui) {
    auto pause_button = tgui::Button::create("Pause simulation");
    if (simulationPaused) {
        pause_button->setText(dm.play_text);
    }
    else {
        pause_button->setText(dm.pause_text);
    }
    pause_button->setSize({ dm.button_width/2, dm.button_height });
    pause_button->setPosition({ x_widget, y_pause_button });

    pause_button->onPress([&]() {
        if (simulationPaused) {
            simulationPaused = false;
            gui.get<tgui::Button>("pause_button")->setText(dm.pause_text);
            tgui::Theme gui_theme{ "themes/GUITheme.txt" };
            gui.get<tgui::Button>("pause_button")->setRenderer(gui_theme.getRenderer("PassiveButton"));

        }
        else {
            simulationPaused = true;
            gui.get<tgui::Button>("pause_button")->setText(dm.play_text);
            tgui::Theme gui_theme{ "themes/GUITheme.txt" };
            gui.get<tgui::Button>("pause_button")->setRenderer(gui_theme.getRenderer("ActiveButton"));

        }

        });
    panel->add(pause_button, "pause_button");
}

void GUIMinimal::create_reflexion_button(DataManager& dm, tgui::GuiSFML& gui, tgui::Panel::Ptr panel) {
    //REFLEXIONS BUTTON
    auto rebound_button = tgui::Button::create();
    if (dm.reflexions_activated) {
        rebound_button->setText(dm.deactivate_reflexion_text);
    }
    else {
        rebound_button->setText(dm.activate_reflexion_text);
    }
    rebound_button->setSize({ dm.button_width, dm.button_height });
    rebound_button->setPosition({ x_widget, y_reflexion_button });

    tgui::Theme gui_theme{ "themes/GUITheme.txt" };
    rebound_button->setRenderer(gui_theme.getRenderer("PassiveButton"));

    rebound_button->onPress([&]() {
        if (dm.reflexions_activated) {
            dm.reflexions_activated = false;
            gui.get<tgui::Button>("rebound_button")->setText(dm.activate_reflexion_text);
            tgui::Theme gui_theme{ "themes//GUITheme.txt" };
            gui.get<tgui::Button>("rebound_button")->setRenderer(gui_theme.getRenderer("PassiveButton"));
        }
        else {
            dm.reflexions_activated = true;
            gui.get<tgui::Button>("rebound_button")->setText(dm.deactivate_reflexion_text);
            tgui::Theme gui_theme{ "themes/GUITheme.txt" };
            gui.get<tgui::Button>("rebound_button")->setRenderer(gui_theme.getRenderer("ActiveButton"));
        }
        });
    panel->add(rebound_button, "rebound_button");
}



void GUIMinimal::update_nb_neutrons(DataManager& dm, NeutronSet& neutron_set, tgui::GuiSFML& gui) {
    gui.get<tgui::Label>("nb_neutrons_label")->setText(to_string(neutron_set.get_nb_alive_neutrons()) + " neutrons actifs");
    
    /*
    string keff = to_string(neutron_set.keff);
    string rounded_keff = keff.substr(0, keff.find(".") + 3);
    gui.get<tgui::Label>("keff_label")->setText(dm.keff_label_text + rounded_keff);
    */

}
