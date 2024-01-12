#pragma once
#include "Volume.h"
#include <vector>
//#include <stdlib.h>
#include <iostream>
#include <fstream>

//#include <Windows.h>

#include <string>
#include <list>

class DataManager
{
public:   
    string version;
    bool keep_window_closed;
    string language;
	bool continuous_simulation;
    int x_window;
    int y_window;
    int x_gui_panel;
    int x_canvas;
    int y_canvas;
    float ppcm;
    int fps;

    int max_nb_neutrons; 
    bool display_legend;
    bool display_plot;
    bool display_detector_plot;

    bool automatic_generated_sources;

    bool allow_neutron_creation;
     
    
    int selected_volume_index;

    bool simulationPaused;

    //GUI
    int height_menu;
    int x_margin;
    int gui_width;
    int gui_height;
    int x_left_margin;
    int y_up_margin;
    int dy;
    int text_size;
    int text_size_mini;
    int button_width;
    int button_height;
    int slider_width;

    int y_keff_panel;
    int y_source_panel;
    int y_chemistry_panel;
    int y_geometry_panel;

    bool keff_panel_is_visible;
    bool source_panel_is_visible;
    bool geometry_panel_is_visible;
    bool chemistry_panel_is_visible;
    bool reset_graph;
    bool reset_simulation;


    int mass_neutron;
    float r_neutron;

    int nb_source;
    float x_source = 999;
    float y_source = 999;

    float delayed_neutrons_proportion;
    float delayed_neutrons_time;

    string type_source;

    float neutron_speed_magnitude;
    bool reflexions_activated;
    int renormalization_delay;
    int add_source_delay;
    Material fuel;
    Material water;
    vector<Volume> volu_array;
    vector<Material> mate_array;
    int highest_volume_priority;

    

    //for discrete simulation
    float r_nuclide;
    float r_hydrogen;
    int nb_nuclide;
    int nb_spent_nuclide;
    int mass_nuclide;
    int mass_hydrogen;
    int nb_hydrogen;
    int nu_bar_discrete;
    float nuclide_speed_magnitude;
    float hydrogen_speed_magnitude;
    int fission_probability;
    float nuclide_refresh_delay;
    float neutron_refresh_delay;
    string nuclides_distribution;
    string collision_type;

    //control rod parameters:
    bool control_rod_exists;
    float x_rod;
    float y_rod;
    float width_rod;
    float height_rod;
    float delta_rod;



    string material_buckling_label_text;
    string geometrical_buckling_label_text;
    string xs_c_text;
    string xs_s_text;
    string xs_f_text;
    string density_text;
    string pause_text;
    string play_text;
    string reset_text;
    string activate_reflexion_text;
    string deactivate_reflexion_text;
    string renormalization_text;
    string radius_text;
    string width_text;
    string height_text;
    string generate_source_text;
    string automatic_source_text;
    string manual_source_text;
    string source_delay_text;
    string nubar_text;

    string selected_shapetext;
    string source_title;
    string geometry_panel_title;
    string chemistry_panel_title;
    
    string source_number_text;
    string source_coordinates_text;
    string keff_button_text;
    string keff_automatic_button_text;
    string keff_label_text;
    string last_keff_label_text;
    string averaged_keff_label_text;
    string sigma_label_text;

    DataManager();
    void clear();
    void create_continuous_geometry();
    void create_materials();
    void create_config2();
    float get_pixels_per_cm();

    void read(string filename);
    void write(string filename);
    vector<std::string> split(string str, char seperator);
    void display_line(vector<string> line_array);
    void parse_line(vector<string> line_array);
    int getIndex(vector<string> v, string K);
    bool is_comment(vector<string> line_array);
    void parse_language(vector<string> line_array);
    void parse_continuous(vector<string> line_array);
    void parse_reflexions(vector<string> line_array);
    void parse_window_size(vector<string> line_array);
    void parse_fps(vector<string> line_array);

    void parse_r_neutron(vector<string> line_array);
    void parse_r_hydrogen(vector<string> line_array);
    void parse_r_nuclide(vector<string> line_array);
    void parse_nb_hydrogen(vector<string> line_array);
    void parse_nb_nuclide(vector<string> line_array);
    void parse_nb_spent_nuclide(vector<string> line_array);
    void parse_neutron_speed(vector<string> line_array);
    void parse_nuclide_speed_magnitude(vector<string> line_array);

    void parse_mass_hydrogen(vector<string> line_array);
    void parse_mass_nuclide(vector<string> line_array);
    void parse_hydrogen_speed_magnitude(vector<string> line_array);
    void parse_nuclides_distribution(vector<string> line_array);
    void parse_nuclide_refresh_delay(vector<string> line_array);
    void parse_neutron_refresh_delay(vector<string> line_array);

    void parse_rod(vector<string> line_array);
    void parse_source(vector<string> line_array);
    void parse_renormalization_delay(vector<string> line_array);    
    void parse_add_source_delay(vector<string> line_array);
    void parse_materials(vector<string> line_array);

    void parse_geometry(vector<string> line_array);

    sf::Color generate_random_color();

    Material find_material(string material_name);
    list<int> find_fissile_volumes();
    
    void assign_language();

    void parse_panels_visibility(vector<string> line_array);

    void delete_one_volume(string name);

    void parse_collision_type(vector<string> line_array);
};

