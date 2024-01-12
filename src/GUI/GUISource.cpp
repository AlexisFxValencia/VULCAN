#include "GUISource.h"

GUISource::GUISource() {

}

GUISource::GUISource(DataManager& dm) {
    y_source_panel = dm.y_source_panel;

    text_size = 18;
    text_size_mini = 15;
    x_widget = 0.05 * dm.button_width;
    height = 15 * dm.dy;


    text_color = sf::Color(253, 163, 163);
}

void GUISource::create_panel(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel, tgui::GuiSFML& gui) {
    update_y_positions(dm);
    create_source_title_label(dm, panel);
    create_type_source_buttons(dm, panel, gui);
    create_source_number_label(dm, panel);
    create_sources_textbox(dm, panel, gui);
    create_source_coordinates_label(dm, panel);
    create_x_source_textbox(dm, panel, gui);
    create_y_source_textbox(dm, panel, gui);
    create_automatic_sources_button(dm, panel, gui);
    create_source_delay_label(dm, panel, gui);
    create_source_slider(dm, panel, gui);
    create_renormalization_label(dm, panel);
    create_renormalization_slider(dm, panel, gui);

    create_neutrons_speed_label(dm, panel);
    create_neutrons_speed_slider(dm, panel, gui, neutron_set);

    create_delayed_neutrons_proportion_label(dm, panel);
    create_delayed_neutrons_proportion_slider(dm, panel, gui);
    create_delayed_neutron_time_label(dm, panel);
    create_delayed_neutron_time_slider(dm, panel, gui);

}

void GUISource::update_y_positions(DataManager& dm) {
    y_source_title = 0 * dm.dy + y_source_panel;
    y_type_source =  1 * dm.dy + y_source_panel;
    y_source_number_label = 2 * dm.dy + y_source_panel;
    y_source_coordinates = 3 * dm.dy + y_source_panel;
    y_source_automatic_button = 4 * dm.dy + y_source_panel;
    y_source_delay_label = 5 * dm.dy + y_source_panel;
    y_source_slider = 6 * dm.dy + y_source_panel;
    y_renormalization_label = 7 * dm.dy + y_source_panel;
    y_renormalization_slider = 8 * dm.dy + y_source_panel;

    y_neutrons_speed_label = 9 * dm.dy + y_source_panel;
    y_neutrons_speed_slider = 10 * dm.dy + y_source_panel;

    y_delayed_neutrons_proportion_label = 11 * dm.dy + y_source_panel;
    y_delayed_neutrons_proportion_slider = 12 * dm.dy + y_source_panel;
    y_delayed_neutrons_time_label = 13 * dm.dy + y_source_panel;
    y_delayed_neutrons_time_slider = 14 * dm.dy + y_source_panel;

}


void GUISource::delete_panel(tgui::GuiSFML& gui, tgui::Panel::Ptr panel) {
    if (auto source_title_label = gui.get<tgui::Label>("source_title_label")) {
        panel->remove(source_title_label);
    }

    if (auto ponctual_source_button = gui.get<tgui::Button>("ponctual_source_button")) {
        panel->remove(ponctual_source_button);
    }
    if (auto uniform_source_button = gui.get<tgui::Button>("uniform_source_button")) {
        panel->remove(uniform_source_button);
    }
    if (auto volumes_source_button = gui.get<tgui::Button>("volumes_source_button")) {
        panel->remove(volumes_source_button);
    }
    

    if (auto source_number_label = gui.get<tgui::Label>("source_number_label")) {
        panel->remove(source_number_label);
    }

    if (auto sources_textbox = gui.get<tgui::EditBox>("sources_textbox")) {
        panel->remove(sources_textbox);
    }
    if (auto source_coordinates_label = gui.get<tgui::Label>("source_coordinates_label")) {
        panel->remove(source_coordinates_label);
    }
    if (auto x_source_textbox = gui.get<tgui::EditBox>("x_source_textbox")) {
        panel->remove(x_source_textbox);
    }
    if (auto y_source_textbox = gui.get<tgui::EditBox>("y_source_textbox")) {
        panel->remove(y_source_textbox);
    }
    if (auto source_automatic_button = gui.get<tgui::Button>("source_automatic_button")) {
        panel->remove(source_automatic_button);
    }

    if (auto source_delay_label = gui.get<tgui::Label>("source_delay_label")) {
        panel->remove(source_delay_label);
    }
    if (auto source_slider = gui.get<tgui::Slider>("source_slider")) {
        panel->remove(source_slider);
    }
    if (auto renorm_label = gui.get<tgui::Label>("renorm_label")) {
        panel->remove(renorm_label);
    }
    if (auto renorm_slider = gui.get<tgui::Slider>("renorm_slider")) {
        panel->remove(renorm_slider);
    }
    if (auto speed_label = gui.get<tgui::Label>("speed_label")) {
        panel->remove(speed_label);
    }
    if (auto speed_slider = gui.get<tgui::Slider>("speed_slider")) {
        panel->remove(speed_slider);
    }

    if (auto delayed_neutrons_proportion_label = gui.get<tgui::Label>("delayed_neutrons_proportion_label")) {
        panel->remove(delayed_neutrons_proportion_label);
    }
    if (auto delayed_neutrons_proportion_slider = gui.get<tgui::Slider>("delayed_neutrons_proportion_slider")) {
        panel->remove(delayed_neutrons_proportion_slider);
    }
    if (auto delayed_neutrons_time_label = gui.get<tgui::Label>("delayed_neutrons_time_label")) {
        panel->remove(delayed_neutrons_time_label);
    }
    if (auto delayed_neutrons_time_slider = gui.get<tgui::Slider>("delayed_neutrons_time_slider")) {
        panel->remove(delayed_neutrons_time_slider);
    }
}


void GUISource::reset_panel(DataManager& dm, tgui::GuiSFML& gui) {
    if (dm.source_panel_is_visible) {
        tgui::Theme gui_theme{ "themes/GUITheme.txt" };

        gui.get<tgui::Button>("source_automatic_button")->setText(dm.manual_source_text);
        if (dm.automatic_generated_sources) {
            gui.get<tgui::Button>("source_automatic_button")->setRenderer(gui_theme.getRenderer("AutoButton"));
        }
        else {
            gui.get<tgui::Button>("source_automatic_button")->setRenderer(gui_theme.getRenderer("ManualButton"));
        }

        gui.get<tgui::EditBox>("sources_textbox")->setText(to_string(dm.nb_source));
        gui.get<tgui::EditBox>("x_source_textbox")->setText(tgui::String::fromNumber(dm.x_source));
        gui.get<tgui::EditBox>("y_source_textbox")->setText(tgui::String::fromNumber(dm.y_source));

        gui.get<tgui::Slider>("source_slider")->setValue(dm.add_source_delay);
        gui.get<tgui::Label>("source_delay_label")->setText(dm.source_delay_text + std::to_string(dm.add_source_delay) + " sec");

        gui.get<tgui::Slider>("renorm_slider")->setValue(dm.renormalization_delay);
        gui.get<tgui::Label>("renorm_label")->setText(dm.renormalization_text + to_string(dm.renormalization_delay) + " sec");

    }
}


void GUISource::create_source_title_label(DataManager& dm, tgui::Panel::Ptr panel) {
    auto source_title_label = tgui::Label::create();
    source_title_label->setText(dm.source_title);
    source_title_label->setPosition(x_widget, y_source_title);
    source_title_label->setTextSize(text_size_mini);
    source_title_label->getRenderer()->setTextColor(text_color);
    panel->add(source_title_label, "source_title_label");
}


void GUISource::create_type_source_buttons(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui) {
    auto ponctual_source_button = tgui::Button::create("source ponctuelle");
    ponctual_source_button->setSize({ dm.button_width/3, dm.button_height });
    ponctual_source_button->setPosition({ x_widget, y_type_source });
    tgui::Theme gui_theme{ "themes/GUITheme.txt" };
    if (dm.type_source == "punctual") {
        ponctual_source_button->setRenderer(gui_theme.getRenderer("ActiveButton"));
    }
    else {
        ponctual_source_button->setRenderer(gui_theme.getRenderer("PassiveButton"));
    }
    ponctual_source_button->onPress([&]() {
        dm.type_source = "punctual";
        tgui::Theme gui_theme{ "themes/GUITheme.txt" };
        gui.get<tgui::Button>("ponctual_source_button")->setRenderer(gui_theme.getRenderer("ActiveButton"));
        gui.get<tgui::Button>("uniform_source_button")->setRenderer(gui_theme.getRenderer("PassiveButton"));
        gui.get<tgui::Button>("volumes_source_button")->setRenderer(gui_theme.getRenderer("PassiveButton"));

        gui.get<tgui::Label>("source_coordinates_label")->getRenderer()->setOpacity(1);
        gui.get<tgui::EditBox>("x_source_textbox")->getRenderer()->setOpacity(1);
        gui.get<tgui::EditBox>("y_source_textbox")->getRenderer()->setOpacity(1);
        });
    panel->add(ponctual_source_button, "ponctual_source_button");


    auto uniform_source_button = tgui::Button::create("source uniforme");
    uniform_source_button->setSize({ dm.button_width / 3, dm.button_height });
    uniform_source_button->setPosition({ x_widget + dm.button_width / 3 + (x_widget / 4), y_type_source });
    if (dm.type_source == "uniform") {
        uniform_source_button->setRenderer(gui_theme.getRenderer("ActiveButton"));
    }
    else {
        uniform_source_button->setRenderer(gui_theme.getRenderer("PassiveButton"));
    }
    uniform_source_button->onPress([&]() {
        dm.type_source = "uniform";
        tgui::Theme gui_theme{ "themes/GUITheme.txt" };
        gui.get<tgui::Button>("ponctual_source_button")->setRenderer(gui_theme.getRenderer("PassiveButton"));
        gui.get<tgui::Button>("uniform_source_button")->setRenderer(gui_theme.getRenderer("ActiveButton"));
        gui.get<tgui::Button>("volumes_source_button")->setRenderer(gui_theme.getRenderer("PassiveButton"));
        
        gui.get<tgui::Label>("source_coordinates_label")->getRenderer()->setOpacity(0);
        gui.get<tgui::EditBox>("x_source_textbox")->getRenderer()->setOpacity(0);
        gui.get<tgui::EditBox>("y_source_textbox")->getRenderer()->setOpacity(0);

    });
    panel->add(uniform_source_button, "uniform_source_button");

    auto volumes_source_button = tgui::Button::create("source dans \nvolumes fissiles");
    volumes_source_button->setSize({ dm.button_width/3, dm.button_height });
    volumes_source_button->setPosition({ x_widget + (2 * dm.button_width /3) + (x_widget / 2), y_type_source });
    if (dm.type_source == "fissile") {
        volumes_source_button->setRenderer(gui_theme.getRenderer("ActiveButton"));
    }
    else {
        volumes_source_button->setRenderer(gui_theme.getRenderer("PassiveButton"));
    }
    volumes_source_button->onPress([&]() {
        dm.type_source = "fissile";
        tgui::Theme gui_theme{ "themes/GUITheme.txt" };
        gui.get<tgui::Button>("ponctual_source_button")->setRenderer(gui_theme.getRenderer("PassiveButton"));
        gui.get<tgui::Button>("uniform_source_button")->setRenderer(gui_theme.getRenderer("PassiveButton"));
        gui.get<tgui::Button>("volumes_source_button")->setRenderer(gui_theme.getRenderer("ActiveButton")); 
        
        gui.get<tgui::Label>("source_coordinates_label")->getRenderer()->setOpacity(0);
        gui.get<tgui::EditBox>("x_source_textbox")->getRenderer()->setOpacity(0);
        gui.get<tgui::EditBox>("y_source_textbox")->getRenderer()->setOpacity(0);
    });
    panel->add(volumes_source_button, "volumes_source_button");
}


void GUISource::create_source_number_label(DataManager& dm, tgui::Panel::Ptr panel) {
    auto source_number_label = tgui::Label::create();
    source_number_label->setText(dm.source_number_text);
    source_number_label->setPosition(x_widget, y_source_number_label);
    source_number_label->setTextSize(text_size_mini);
    source_number_label->getRenderer()->setTextColor(text_color);
    panel->add(source_number_label, "source_number_label");
}

void GUISource::create_sources_textbox(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui) {
    //SOURCES TEXTBOX
    auto sources_textbox = tgui::EditBox::create();
    sources_textbox->setText(to_string(dm.nb_source));
    sources_textbox->setSize({ dm.button_width / 2, dm.dy * 0.8 });
    sources_textbox->setPosition({ dm.button_width / 2 + x_widget/2, y_source_number_label });
    sources_textbox->onReturnOrUnfocus([&] {
        tgui::String input_text = gui.get<tgui::EditBox>("sources_textbox")->getText();
        dm.nb_source = input_text.toInt();
        });
    panel->add(sources_textbox, "sources_textbox");
}

void GUISource::create_source_coordinates_label(DataManager& dm, tgui::Panel::Ptr panel) {
    auto source_coordinates_label = tgui::Label::create();
    source_coordinates_label->setText(dm.source_coordinates_text);
    source_coordinates_label->setPosition(x_widget, y_source_coordinates);
    source_coordinates_label->setTextSize(text_size_mini);
    source_coordinates_label->getRenderer()->setTextColor(text_color);

    if (dm.type_source == "punctual") {
        source_coordinates_label->getRenderer()->setOpacity(1);
    }
    else {
        source_coordinates_label->getRenderer()->setOpacity(0);
    }
    panel->add(source_coordinates_label, "source_coordinates_label");
}

void GUISource::create_x_source_textbox(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui) {
    //X SOURCES TEXTBOX
    auto x_source_textbox = tgui::EditBox::create();
    tgui::String x_text = tgui::String::fromNumber(dm.x_source);
    x_source_textbox->setText(x_text);
    x_source_textbox->setSize({ dm.button_width / 4, dm.button_height });
    x_source_textbox->setPosition({ dm.button_width / 2 + x_widget/2, y_source_coordinates });
    x_source_textbox->onReturnOrUnfocus([&] {
        tgui::String x = gui.get<tgui::EditBox>("x_source_textbox")->getText();
        float x1 = x.toFloat();
        dm.x_source = x1;
        });
    if (dm.type_source == "punctual") {
        x_source_textbox->getRenderer()->setOpacity(1);
    }
    else {
        x_source_textbox->getRenderer()->setOpacity(0);
    }
    panel->add(x_source_textbox, "x_source_textbox");
}

void GUISource::create_y_source_textbox(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui) {
    //X SOURCES TEXTBOX
    auto y_source_textbox = tgui::EditBox::create();
    tgui::String y_text = tgui::String::fromNumber(dm.y_source);
    y_source_textbox->setText(y_text);
    y_source_textbox->setSize({ dm.button_width / 4, dm.button_height });
    y_source_textbox->setPosition({ 3 * dm.button_width / 4 + (3*x_widget/4), y_source_coordinates });
    if (dm.type_source == "punctual") {
        y_source_textbox->getRenderer()->setOpacity(1);
    }
    else {
        y_source_textbox->getRenderer()->setOpacity(0);
    }
    y_source_textbox->onReturnOrUnfocus([&] {
        tgui::String y = gui.get<tgui::EditBox>("y_source_textbox")->getText();
        float y1 = y.toFloat();
        dm.y_source = y1;
        });
    panel->add(y_source_textbox, "y_source_textbox");
}



void GUISource::create_automatic_sources_button(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui) {
    auto source_automatic_button = tgui::Button::create(dm.manual_source_text);
    source_automatic_button->setSize({ dm.button_width, dm.button_height });
    source_automatic_button->setPosition({ x_widget, y_source_automatic_button });

    tgui::Theme gui_theme{ "themes/GUITheme.txt" };
    source_automatic_button->setRenderer(gui_theme.getRenderer("ManualButton"));

    source_automatic_button->onPress([&]() {
        if (dm.automatic_generated_sources) {
            dm.automatic_generated_sources = false;
            gui.get<tgui::Button>("source_automatic_button")->setText(dm.manual_source_text);
            tgui::Theme gui_theme{ "themes/GUITheme.txt" };
            gui.get<tgui::Button>("source_automatic_button")->setRenderer(gui_theme.getRenderer("ManualButton"));
            gui.get<tgui::Label>("source_delay_label")->getRenderer()->setOpacity(0);
            gui.get<tgui::Slider>("source_slider")->getRenderer()->setOpacity(0);

        }
        else {
            dm.automatic_generated_sources = true;
            gui.get<tgui::Button>("source_automatic_button")->setText(dm.automatic_source_text);
            tgui::Theme gui_theme{ "themes/GUITheme.txt" };
            gui.get<tgui::Button>("source_automatic_button")->setRenderer(gui_theme.getRenderer("AutoButton"));
            gui.get<tgui::Label>("source_delay_label")->getRenderer()->setOpacity(1);
            gui.get<tgui::Slider>("source_slider")->getRenderer()->setOpacity(1);
        }
        });
    panel->add(source_automatic_button, "source_automatic_button");
}


void GUISource::create_source_delay_label(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui) {
    auto source_delay_label = tgui::Label::create();
    source_delay_label->setText(dm.source_delay_text + to_string(dm.add_source_delay) + " sec");
    source_delay_label->setPosition(x_widget, y_source_delay_label);
    source_delay_label->setTextSize(text_size_mini);
    source_delay_label->getRenderer()->setTextColor(text_color);

    if (dm.automatic_generated_sources) {
        source_delay_label->getRenderer()->setOpacity(1);
    }
    else {
        source_delay_label->getRenderer()->setOpacity(0);
    }

    panel->add(source_delay_label, "source_delay_label");
}

void GUISource::create_source_slider(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui) {
    auto source_slider = tgui::Slider::create();
    source_slider->setPosition(x_widget, y_source_slider);
    source_slider->setSize(dm.slider_width, text_size_mini);
    source_slider->setMinimum(1);
    source_slider->setMaximum(15);
    source_slider->setValue(dm.add_source_delay);

    if (dm.automatic_generated_sources) {
        source_slider->getRenderer()->setOpacity(1);
    }
    else {
        source_slider->getRenderer()->setOpacity(0);
    }

    source_slider->onValueChange([&]() {
        float slider_index = gui.get<tgui::Slider>("source_slider")->getValue();
        dm.add_source_delay = slider_index;
        gui.get<tgui::Label>("source_delay_label")->setText(dm.source_delay_text + std::to_string(dm.add_source_delay) + " sec");
        });
    panel->add(source_slider, "source_slider");
}


void GUISource::create_renormalization_label(DataManager& dm, tgui::Panel::Ptr panel) {
    auto renorm_label = tgui::Label::create();
    renorm_label->setText(dm.renormalization_text + std::to_string(dm.renormalization_delay) + " sec");
    renorm_label->setPosition(x_widget, y_renormalization_label);
    renorm_label->setTextSize(text_size_mini);
    renorm_label->getRenderer()->setTextColor(text_color);
    panel->add(renorm_label, "renorm_label");
}

void GUISource::create_renormalization_slider(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui) {
    auto renorm_slider = tgui::Slider::create();
    renorm_slider->setPosition(x_widget, y_renormalization_slider);
    renorm_slider->setSize(dm.slider_width, text_size_mini);
    renorm_slider->setMinimum(2);
    renorm_slider->setMaximum(900);
    renorm_slider->setValue(dm.renormalization_delay);

    renorm_slider->onValueChange([&]() {
        float slider_index = gui.get<tgui::Slider>("renorm_slider")->getValue();
        dm.renormalization_delay = slider_index;
        gui.get<tgui::Label>("renorm_label")->setText(dm.renormalization_text + std::to_string(dm.renormalization_delay) + " sec");
        });
    panel->add(renorm_slider, "renorm_slider");
}


void GUISource::create_neutrons_speed_label(DataManager& dm, tgui::Panel::Ptr panel) {
    auto speed_label = tgui::Label::create();
    speed_label->setText("neutrons speed : " + std::to_string(dm.neutron_speed_magnitude) + " cm/s");
    speed_label->setPosition(x_widget, y_neutrons_speed_label);
    speed_label->setTextSize(text_size_mini);
    speed_label->getRenderer()->setTextColor(text_color);
    panel->add(speed_label, "speed_label");
}

void GUISource::create_neutrons_speed_slider(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui, NeutronSet& neutron_set) {
    auto speed_slider = tgui::Slider::create();
    speed_slider->setPosition(x_widget, y_neutrons_speed_slider);
    speed_slider->setSize(dm.slider_width, text_size_mini);
    speed_slider->setMinimum(0);
    speed_slider->setMaximum(25);
    speed_slider->setValue(dm.neutron_speed_magnitude);

    speed_slider->onValueChange([&]() {
        float slider_index = gui.get<tgui::Slider>("speed_slider")->getValue();
        dm.neutron_speed_magnitude = slider_index;
        for (int i = 0; i < neutron_set.neutrons_array.size(); i++) {
            neutron_set.neutrons_array[i].vx = dm.neutron_speed_magnitude * cos(neutron_set.neutrons_array[i].theta);
            neutron_set.neutrons_array[i].vy = dm.neutron_speed_magnitude * sin(neutron_set.neutrons_array[i].theta);
        }
        gui.get<tgui::Label>("speed_label")->setText("neutrons speed : " + std::to_string(dm.neutron_speed_magnitude) + " cm/s");
        });
    panel->add(speed_slider, "speed_slider");
}


void GUISource::create_delayed_neutrons_proportion_label(DataManager& dm, tgui::Panel::Ptr panel) {
    auto delayed_neutrons_proportion_label = tgui::Label::create();
    delayed_neutrons_proportion_label->setText("delayed neutrons proportion : " + std::to_string(dm.delayed_neutrons_proportion));
    delayed_neutrons_proportion_label->setPosition(x_widget, y_delayed_neutrons_proportion_label);
    delayed_neutrons_proportion_label->setTextSize(text_size_mini);
    delayed_neutrons_proportion_label->getRenderer()->setTextColor(text_color);
    panel->add(delayed_neutrons_proportion_label, "delayed_neutrons_proportion_label");
}

void GUISource::create_delayed_neutrons_proportion_slider(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui) {
    auto delayed_neutrons_proportion_slider = tgui::Slider::create();
    delayed_neutrons_proportion_slider->setPosition(x_widget, y_delayed_neutrons_proportion_slider);
    delayed_neutrons_proportion_slider->setSize(dm.slider_width, text_size_mini);
    delayed_neutrons_proportion_slider->setMinimum(0);
    delayed_neutrons_proportion_slider->setMaximum(100);
    delayed_neutrons_proportion_slider->setValue(dm.delayed_neutrons_proportion*100);

    delayed_neutrons_proportion_slider->onValueChange([&]() {
        float slider_index = gui.get<tgui::Slider>("delayed_neutrons_proportion_slider")->getValue();
        dm.delayed_neutrons_proportion = slider_index/100;
        
        gui.get<tgui::Label>("delayed_neutrons_proportion_label")->setText("delayed neutrons proportion : " + std::to_string(dm.delayed_neutrons_proportion));
        });
    panel->add(delayed_neutrons_proportion_slider, "delayed_neutrons_proportion_slider");
}

void GUISource::create_delayed_neutron_time_label(DataManager& dm, tgui::Panel::Ptr panel) {
    auto delayed_neutrons_time_label = tgui::Label::create();
    delayed_neutrons_time_label->setText("delayed neutrons time (s): " + std::to_string(dm.delayed_neutrons_time/1000));
    delayed_neutrons_time_label->setPosition(x_widget, y_delayed_neutrons_time_label);
    delayed_neutrons_time_label->setTextSize(text_size_mini);
    delayed_neutrons_time_label->getRenderer()->setTextColor(text_color);
    panel->add(delayed_neutrons_time_label, "delayed_neutrons_time_label");
}

void GUISource::create_delayed_neutron_time_slider(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui) {
    auto delayed_neutrons_time_slider = tgui::Slider::create();
    delayed_neutrons_time_slider->setPosition(x_widget, y_delayed_neutrons_time_slider);
    delayed_neutrons_time_slider->setSize(dm.slider_width, text_size_mini);
    delayed_neutrons_time_slider->setMinimum(0);
    delayed_neutrons_time_slider->setMaximum(10000);
    delayed_neutrons_time_slider->setValue(dm.delayed_neutrons_time);

    delayed_neutrons_time_slider->onValueChange([&]() {
        float slider_index = gui.get<tgui::Slider>("delayed_neutrons_time_slider")->getValue();
        dm.delayed_neutrons_time = slider_index;

        gui.get<tgui::Label>("delayed_neutrons_time_label")->setText("delayed neutrons time (s): " + std::to_string(dm.delayed_neutrons_time/1000));
        });
    panel->add(delayed_neutrons_time_slider, "delayed_neutrons_time_slider");
}
