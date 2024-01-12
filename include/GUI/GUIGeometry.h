#pragma once


#include <TGUI/TGUI.hpp>
#include "GeometryCreator.h"
#include "DataManager.h"
#include "NeutronSet.h"




class GUIGeometry
{
public:
    int x_widget;

    int height;

    int y_title_label;
    int y_geometry_panel;
    int y_param_1_label;
    int y_param_1_slider;
    int y_param_2_label;
    int y_param_2_slider;
    int y_geometrical_buckling;
    int y_ppcm_label;
    int y_ppcm_slider;
    

    sf::Color text_color;

	GUIGeometry();
    GUIGeometry(DataManager& dm);

    void create_panel(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel, tgui::GuiSFML& gui);
    void update_y_positions(DataManager& dm);
    void delete_panel(tgui::GuiSFML& gui, tgui::Panel::Ptr panel);
    
    void create_title(DataManager& dm, tgui::Panel::Ptr panel);

    void create_param_1_label(DataManager& dm, tgui::Panel::Ptr panel);
    void create_param_1_slider(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui);
    void create_param_2_label(DataManager& dm, tgui::Panel::Ptr panel);
    void create_param_2_slider(DataManager& dm, tgui::Panel::Ptr panel, tgui::GuiSFML& gui);
    void create_geometrical_buckling_label(DataManager& dm, tgui::Panel::Ptr panel);

    void update_labels(DataManager& dm, tgui::GuiSFML& gui);

    void reset_panel(DataManager& dm, tgui::GuiSFML& gui);

    void create_ppcm_label(DataManager& dm, tgui::Panel::Ptr panel);
    void create_ppcm_slider(DataManager& dm, NeutronSet& neutron_set, tgui::Panel::Ptr panel, tgui::GuiSFML& gui);
};

