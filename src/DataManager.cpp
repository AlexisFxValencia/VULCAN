#include "DataManager.h"


DataManager::DataManager() {
    version = "1.01";
    keep_window_closed = false;
    language = "french";
	continuous_simulation = true;
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    x_window = mode.width;
    y_window = mode.height;
    //cout << "Screen resolution :" << "\t" << mode.width << "x" << mode.height << " \t " << mode.bitsPerPixel << " bpp" << endl;
    x_gui_panel = 0.25 * x_window;//400;    
    x_canvas = x_window - x_gui_panel;
    y_canvas = y_window;
    ppcm = get_pixels_per_cm();
    fps = 20;    

    simulationPaused = false;

    max_nb_neutrons = 10000;
    display_legend = true;
    display_plot = false;
    reset_graph = false;
    display_detector_plot = false;
    reset_simulation = false;

    //GUI
    y_keff_panel = 270;
    y_source_panel = 600;
    y_geometry_panel = 1200;
    y_chemistry_panel = 1550;

    height_menu = 30;
    x_margin = 10;
    gui_width = x_window - x_canvas - x_margin;
    gui_height = y_canvas;
    x_left_margin = 10;
    y_up_margin = 10;
    dy = 50;
    text_size = 18;
    text_size_mini = 15;
    button_width = 0.9*(gui_width - x_margin);
    button_height = 0.8 * dy;
    slider_width = 0.9 * (gui_width - x_margin);  
    keff_panel_is_visible = true;
    source_panel_is_visible = true;
    geometry_panel_is_visible = true;
    chemistry_panel_is_visible = true;


    mass_neutron = 1;
    r_neutron = 0.2;
    nb_source = 30;
    x_source = 999;
    y_source = 999;
    type_source = "punctual";

    neutron_speed_magnitude = 1.5*2;
    delayed_neutrons_proportion = 0.0;
    delayed_neutrons_time = 2000; //msec

    renormalization_delay = 30;
    add_source_delay = 5;
    selected_volume_index = 999;
    reflexions_activated = false;

    //create_materials();
    //create_continuous_geometry();
    //create_config2();


    //for discrete simulation:
    r_nuclide = 3 * r_neutron;
    r_hydrogen = 0.5;
    nb_nuclide = 9;
    nb_spent_nuclide = 9;
    mass_nuclide = 200;  
    mass_hydrogen = 1;
    nu_bar_discrete = 2;
    nb_hydrogen = 20;
    nuclide_speed_magnitude = 0.0;
    hydrogen_speed_magnitude = 0.0;
    fission_probability = 1000;
    nuclide_refresh_delay = 6.0;
    neutron_refresh_delay = 1.0; //in sec
    nuclides_distribution = "square";
    collision_type = "elastic";
    
    highest_volume_priority = 0;

    //control rod parameters:
    control_rod_exists = false;
    x_rod = 5;
    y_rod = 10;
    width_rod = 2;
    height_rod = 7;
    delta_rod = 0.3;

    automatic_generated_sources = false;
    automatic_computed_keff = false;

    allow_neutron_creation = true;
}

void DataManager::clear(){
    volu_array.clear();
    mate_array.clear();
    control_rod_exists = false;
}

void DataManager::create_materials() {
    // source : https://www.nuclear-power.com/nuclear-power/reactor-physics/nuclear-engineering-fundamentals/neutron-nuclear-reactions/atomic-number-density/
    float atomic_density_fuel = 9.48e20; //cm2
    float nu_bar = 2;
    //source : https://wwwndc.jaea.go.jp/cgi-bin/Tab80WWW.cgi?lib=J40&iso=U23
    float sigma_s = 15.12;
    float sigma_c = 98.71;
    float sigma_f = 585.1;// / 2.6;
    sf::Color color_fuel = sf::Color::Green;
    this->fuel = Material("fuel", color_fuel, atomic_density_fuel, nu_bar, sigma_s, sigma_c, sigma_f);
    fuel.compute_buckling();

    sf::Color color_water = sf::Color::Blue;
    this->water = Material("water", color_water, atomic_density_fuel, nu_bar, 10 * sigma_s, 0.1 * sigma_c, 0.0);
    fuel.compute_buckling();
}

void DataManager::create_continuous_geometry() {
    int radius = 5 ;
    float x_c = (x_window / 2)/ppcm;
    float y_c = (y_window / 3)/ppcm;

    Volume water_disk = Volume("water_disk", "disk", 2 * radius, 0, x_c, y_c, water, 1);
    //volu_array.push_back(water_disk);

    Volume fuel_disk = Volume("fuel_disk", "disk", radius, 0, x_c, y_c, fuel, 2);
    volu_array.push_back(fuel_disk);


    Volume disk2 = Volume("disk2","disk", 1.0, 0.0, 5.0, 10.0, fuel, 3);
    //volu_array.push_back(disk2);

    float width = 200 / ppcm;
    float height = 100 / ppcm;
    float x_r = 900 / ppcm;
    float y_r = 800 / ppcm;
    Volume rectangle = Volume("monrectangle", "rectangle", width, height, x_r, y_r, fuel, 4);
    //volu_array.push_back(rectangle);
}


void DataManager::create_config2() {
    int radius = 2;
    int x_c = 10;
    int y_c = 9;
    Volume fuel_disk = Volume("fuel_disk", "disk", radius, 0, x_c, y_c, fuel, 1);
    volu_array.push_back(fuel_disk);

    int width = 2;
    int height = 16;
    int x_r = 17;
    int y_r = y_c;
    Volume rectangle = Volume("monrectangle", "rectangle", width, height, x_r, y_r, water, 2);
    volu_array.push_back(rectangle);


    int x_c2 = (x_window / ppcm - 10);
    int y_c2 = y_c;
    Volume fuel_disk2 = Volume("fuel_disk2", "disk", radius, 0, x_c2, y_c2, fuel, 3);
    volu_array.push_back(fuel_disk2);
}

float DataManager::get_pixels_per_cm() {
    //HDC screen = GetDC(NULL);
    //int screen_mm_width = GetDeviceCaps(screen, HORZSIZE);
    //int screen_mm_height = GetDeviceCaps(screen, VERTSIZE);

    float screen_mm_width = 396; // mm for 15,6'
    float pixels_per_cm = (float)x_window * 10 / screen_mm_width;

    return pixels_per_cm;
}

void DataManager::write(string filename) {
    cout << "saving file : " << filename << endl;
    ofstream myfile;
    myfile.open("input_files/" + filename);
    myfile << "# Saved input for neutronics simulator.\n";
    myfile << endl;
    myfile << "# GUI parameters";
    myfile << "# window " + to_string(x_window) << " " << to_string(y_window) << endl;
    myfile << "fps " + to_string(fps) << endl;
    myfile << "language " + language << endl;
    myfile << "keff_panel_is_visible " << std::boolalpha << keff_panel_is_visible << endl;
    myfile << "source_panel_is_visible " << std::boolalpha << source_panel_is_visible << endl;
    myfile << "geometry_panel_is_visible " << std::boolalpha << geometry_panel_is_visible << endl;
    myfile << "chemistry_panel_is_visible " << std::boolalpha << chemistry_panel_is_visible << endl;
    myfile << endl;

    myfile << "# Simulation parameters :" << endl;
    myfile << "continuous_simulation " << std::boolalpha << continuous_simulation << endl;
    myfile << "reflexions_activated " << std::boolalpha << reflexions_activated << endl;
    myfile << "r_neutron " << to_string(r_neutron)<< endl;
    myfile << "neutron_speed_magnitude " << to_string(neutron_speed_magnitude) << endl;    
    if (control_rod_exists) {
        myfile << "control_rod_exists true" << endl;
        myfile << "# x_rod, y_rod, width_rod, height_rod, delta_rod" << endl;
        myfile << "rod " << to_string(x_rod) + " " + to_string(y_rod) + " " + to_string(width_rod) + " " + to_string(height_rod) + " " + to_string(delta_rod) << endl;
    }
    myfile << endl;

    myfile << "# Sources :" << endl;
    myfile << "nb_source " << nb_source << endl;
    myfile << "type_source " << type_source << endl;
    myfile << "x_source " << x_source << endl;
    myfile << "y_source " << y_source << endl;
    myfile << "renormalization_delay " << renormalization_delay << endl;
    myfile << "add_source_delay " << add_source_delay << endl;
    myfile << endl;


    myfile << "# Materials :" << endl;
    for (int i = 0; i < volu_array.size(); i++) {
        volu_array[i].material.name.append("_" + volu_array[i].name);   
        myfile << "material " << volu_array[i].material.name << " random " << volu_array[i].material.atomic_density << " " + to_string(volu_array[i].material.nu_bar)
            << " " + to_string(volu_array[i].material.sigma_s) + " " << to_string(volu_array[i].material.sigma_c) << " " + to_string(volu_array[i].material.sigma_f) << endl;
    }    
    myfile << endl;


    myfile << "# Volumes :" << endl;
    for (int j = 0; j < volu_array.size(); j++) {
        if (volu_array[j].type == "disk") {
            myfile << volu_array[j].type << " " << volu_array[j].name + " " + to_string(volu_array[j].param1) 
                << " " + to_string(volu_array[j].x) + " " + to_string(volu_array[j].y) + " " + volu_array[j].material.name + " " + to_string(volu_array[j].priority) << endl;
        }
        else if (volu_array[j].type == "rectangle") {
            myfile << volu_array[j].type << " " << volu_array[j].name << " " << to_string(volu_array[j].param1) << " " + to_string(volu_array[j].param2)
                << " " + to_string(volu_array[j].x) + " " << to_string(volu_array[j].y) + " " << volu_array[j].material.name + " " + to_string(volu_array[j].priority) << endl;
        }        
    }
    
    myfile.close();

}


void DataManager::read(string filename) {
    ifstream input_file;
    input_file.open(filename);

    if (!input_file.is_open()) {
        cout << "file " << filename <<" not found !" << endl;
    }
    else {
        cout << "Input file read : " << filename << endl;
    }

    if (input_file.is_open()) {
        
        while (input_file) {
            string myline = " ";
            getline(input_file, myline);
            cout << myline << endl;
            std::vector<std::string> line_array = split(myline, ' ');
            //display_line(line_array);
            
            parse_line(line_array);
            
        }       

        input_file.close();
    }
}

vector<std::string> DataManager::split(string str, char separator){
    std::vector<std::string> strings;
    int i = 0;
    int startIndex = 0, endIndex = 0;
    while (i <= str.length()){
        if (str[i] == separator || i == str.length()){
            endIndex = i;
            string subStr = "";
            subStr.append(str, startIndex, endIndex - startIndex);
            strings.push_back(subStr);
            startIndex = endIndex + 1;
        }
        i++;
    }
    return strings;
    
}


void DataManager::display_line(vector<string> line_array) {
    cout << endl << line_array.size() << endl;
    for (int i = 0; i < line_array.size(); i++)
    {
        cout << "\n i : " << i << " " << line_array[i];
    }
    cout << endl;
}

void DataManager::parse_line(vector<string> line_array) {   
    if (!is_comment(line_array)) {
        parse_language(line_array);
        parse_continuous(line_array);
        parse_reflexions(line_array);
        parse_window_size(line_array);
        parse_fps(line_array);
        parse_r_neutron(line_array);
        parse_r_nuclide(line_array);

        parse_r_hydrogen(line_array);
        parse_nb_hydrogen(line_array);
        parse_nb_nuclide(line_array);
        parse_nb_spent_nuclide(line_array);
        parse_mass_hydrogen(line_array);
        parse_mass_nuclide(line_array);
        parse_hydrogen_speed_magnitude(line_array);
        parse_nuclides_distribution(line_array);
        parse_nuclide_refresh_delay(line_array);
        parse_neutron_refresh_delay(line_array);
        parse_nuclide_speed_magnitude(line_array);

        parse_neutron_speed(line_array);
        parse_rod(line_array);
        parse_source(line_array);
        parse_keff(line_array);
        parse_renormalization_delay(line_array);
        parse_add_source_delay(line_array);
        parse_materials(line_array);
        parse_geometry(line_array);

        parse_panels_visibility(line_array);
        
        parse_collision_type(line_array);
    }
    

}

bool DataManager::is_comment(vector<string> line_array) {
    int index = getIndex(line_array, "#");
    if (index == 0 ) {
        //cout << "this line is a comment." << endl;
        return true;
    }
    else {
        return false;
    }
}

void DataManager::parse_language(vector<string> line_array) {
    int index = getIndex(line_array, "language");
    if (index != -1) {
        if (line_array[index + 1] == "french") {
            language = "french";
        }
        else if (line_array[index + 1] == "english") {
            language = "english";
        }
    }
    assign_language();

}

void DataManager::parse_continuous(vector<string> line_array) {
    int index = getIndex(line_array, "continuous_simulation");
    if (index != -1) {
        if (line_array[index + 1] == "true") {
            continuous_simulation = true;
            //cout << "continuous_simulation is read as true." << endl;
        }
        else if (line_array[index + 1] == "false") {
            continuous_simulation = false;
            //cout << "continuous_simulation is read as false." << endl;
        }
    }

}

void DataManager::parse_reflexions(vector<string> line_array) {
    int index = getIndex(line_array, "reflexions_activated");
    if (index != -1) {
        if (line_array[index + 1] == "true") {
            reflexions_activated = true;
            //cout << "reflexions_activated is read as true." << endl;
        }
        else if (line_array[index + 1] == "false") {
            reflexions_activated = false;
            //cout << "reflexions_activated is read as false." << endl;

        }
    }

}



void DataManager::parse_window_size(vector<string> line_array) {
    int index = getIndex(line_array, "window");
    if (index != -1) {
        x_window = stoi(line_array[index + 1]);
        y_window = stoi(line_array[index + 2]);
    }
}

void DataManager::parse_fps(vector<string> line_array) {
    int index = getIndex(line_array, "fps");
    if (index != -1) {
        fps = stoi(line_array[index + 1]);
    }
}

void DataManager::parse_r_neutron(vector<string> line_array) {
    int index = getIndex(line_array, "r_neutron");
    if (index != -1) {
        r_neutron = stof(line_array[index + 1]);
    }
}

void DataManager::parse_r_nuclide(vector<string> line_array) {
    int index = getIndex(line_array, "r_nuclide");
    if (index != -1) {
        r_nuclide = stof(line_array[index + 1]);
    }
}


void DataManager::parse_r_hydrogen(vector<string> line_array) {
    int index = getIndex(line_array, "r_hydrogen");
    if (index != -1) {
        r_hydrogen = stof(line_array[index + 1]);
    }
}

void DataManager::parse_mass_hydrogen(vector<string> line_array) {
    int index = getIndex(line_array, "mass_hydrogen");
    if (index != -1) {
        mass_hydrogen = stof(line_array[index + 1]);
    }
}

void DataManager::parse_mass_nuclide(vector<string> line_array) {
    int index = getIndex(line_array, "mass_nuclide");
    if (index != -1) {
        mass_nuclide = stof(line_array[index + 1]);
    }
}

void DataManager::parse_hydrogen_speed_magnitude(vector<string> line_array) {
    int index = getIndex(line_array, "hydrogen_speed_magnitude");
    if (index != -1) {
        hydrogen_speed_magnitude = stof(line_array[index + 1]);
    }
}

void DataManager::parse_nuclide_speed_magnitude(vector<string> line_array) {
    int index = getIndex(line_array, "nuclide_speed_magnitude");
    if (index != -1) {
        nuclide_speed_magnitude = stof(line_array[index + 1]);
    }
}

void DataManager::parse_nuclides_distribution(vector<string> line_array) {
    int i = getIndex(line_array, "nuclides_distribution");
    if (i != -1) {
        if (line_array[i + 1] == "square") {
            nuclides_distribution = "square";
        }
        if (line_array[i + 1] == "rounded_distribution") {
            nuclides_distribution = "disk";
        }
        if (line_array[i + 1] == "random") {
            nuclides_distribution = "random";
        }
    }
}




void DataManager::parse_nb_hydrogen(vector<string> line_array) {
    int index = getIndex(line_array, "nb_hydrogen");
    if (index != -1) {
        nb_hydrogen = stof(line_array[index + 1]);
    }
}

void DataManager::parse_nb_nuclide(vector<string> line_array) {
    int index = getIndex(line_array, "nb_nuclide");
    if (index != -1) {
        nb_nuclide = stof(line_array[index + 1]);
    }
}

void DataManager::parse_nb_spent_nuclide(vector<string> line_array) {
    int index = getIndex(line_array, "nb_spent_nuclide");
    if (index != -1) {
        nb_spent_nuclide = stof(line_array[index + 1]);
    }
}


void DataManager::parse_neutron_speed(vector<string> line_array) {
    int index = getIndex(line_array, "neutron_speed_magnitude");
    if (index != -1) {
        neutron_speed_magnitude = stof(line_array[index + 1]);
    }
}


void DataManager::parse_rod(vector<string> line_array) {
    int j = getIndex(line_array, "rod");
    if (j != -1) {
        x_rod = stoi(line_array[j + 1]);
        y_rod = stoi(line_array[j + 2]);
        width_rod = stoi(line_array[j + 3]);
        height_rod = stoi(line_array[j + 4]);
        delta_rod = stof(line_array[j + 5]);
    }
    
    int i = getIndex(line_array, "control_rod_exists");
    
    if (i != -1) {
        
        if (line_array[i + 1] == "true") {
            control_rod_exists = true;
            //cout << "control_rod_exists is read as true." << endl;            
        }
        else if (line_array[i + 1] == "false") {
            control_rod_exists = false;
            //cout << "control_rod_exists is read as false." << endl;
        }
    }

    
    
}

void DataManager::parse_source(vector<string> line_array) {
    int index = getIndex(line_array, "nb_source");
    if (index != -1) {
        nb_source = stoi(line_array[index + 1]);
    }
    
    int index_3 = getIndex(line_array, "type_source");
    if (index_3 != -1) {
        type_source = line_array[index_3 + 1];
        //cout << "type_source = " << type_source << endl;
    }
    

    int index_1 = getIndex(line_array, "x_source");
    
    if (index_1 != -1) {
        x_source = stof(line_array[index_1 + 1]);
    }

    int index_2 = getIndex(line_array, "y_source");
    if (index_2 != -1) {
        y_source = stof(line_array[index_2 + 1]);
    }

}


void DataManager::parse_keff(vector<string> line_array){
    int index = getIndex(line_array, "automatic_computed_keff");
    
    if (index != -1) {
        if (line_array[index + 1] == "true") {
            automatic_computed_keff = true;
        }
        else if (line_array[index + 1] == "false") {
            automatic_computed_keff = false;
        }
    }
}



void DataManager::parse_renormalization_delay(vector<string> line_array) {
    int index = getIndex(line_array, "renormalization_delay");
    if (index != -1) {
        renormalization_delay = stoi(line_array[index + 1]);
    }
}

void DataManager::parse_nuclide_refresh_delay(vector<string> line_array) {
    int index = getIndex(line_array, "nuclide_refresh_delay");
    if (index != -1) {
        nuclide_refresh_delay = stof(line_array[index + 1]);
    }
}

void DataManager::parse_neutron_refresh_delay(vector<string> line_array) {
    int index = getIndex(line_array, "neutron_refresh_delay");
    if (index != -1) {
        neutron_refresh_delay = stof(line_array[index + 1]);
    }
}



void DataManager::parse_add_source_delay(vector<string> line_array) {
    int index = getIndex(line_array, "add_source_delay");
    if (index != -1) {
        add_source_delay = stoi(line_array[index + 1]);
    }
}

void DataManager::parse_materials(vector<string> line_array) {
    int index = getIndex(line_array, "material");
    if (index != -1) {
        string name = line_array[index + 1];
        string color_string = line_array[index + 2];
        sf::Color color = generate_random_color(); 
        if (color_string == "red") {
            color = sf::Color(255, 0, 0); 
        } else if (color_string == "lightred") {
            color = sf::Color(220, 20, 60);
        } else if (color_string == "green") {
            color = sf::Color(0, 155, 0);
        } else if (color_string == "darkgreen") {
            color = sf::Color(0, 100, 0);
        } else if (color_string == "blue") {
            color = sf::Color(30, 144, 255); //dodgerblue
        } else if (color_string == "yellow") {
            color = sf::Color(255, 255, 102); //Light yellow3
        } else if (color_string == "grey") {
            color = sf::Color(192, 192, 192); //silver
        } else if (color_string == "darkgrey") {
            color = sf::Color(105, 105, 105); //dimgrey
        } else if (color_string == "brown") {
            color = sf::Color(139, 69, 19); //saddlebrown
        } else if (color_string == "purple") {
            color = sf::Color(148, 0, 211); //darkviolet
        } else if (color_string == "pink") {
            color = sf::Color(255, 192, 203);
        } else if (color_string == "white") {
            color = sf::Color(255, 255, 255);
        } else if (color_string == "black") {
            color = sf::Color(0, 0, 0);
        }
        
        float atomic_density_2 = stof(line_array[index + 3]);
        float nu_2 = stof(line_array[index + 4]);
        float sigma_s_2 = stof(line_array[index + 5]);
        float sigma_c_2 = stof(line_array[index + 6]);
        float sigma_f_2 = stof(line_array[index + 7]); 
        Material material_2 = Material(name, color, atomic_density_2, nu_2, sigma_s_2, sigma_c_2, sigma_f_2);
        mate_array.push_back(material_2);
        //cout << endl << "color : " << material_2.color.toInteger() << endl;
    }
}

void DataManager::parse_geometry(vector<string> line_array) {
    //cout << "parsing geometry of line : " << line_array[0] << endl;
    //"disk", radius, 0, x_c, y_c, fuel
    int index = getIndex(line_array, "disk");
    if (index != -1) {
        //cout << "geometry : one disk read" << endl;
        string name = line_array[index + 1];
        float radius = stof(line_array[index + 2]);
        float x_c = stof(line_array[index + 3]);
        float y_c = stof(line_array[index + 4]);
        string material_name = line_array[index + 5];
        int priority = stoi(line_array[index + 6]);
        Material material = find_material(material_name);
        Volume disk_volu = Volume(name, "disk", radius, 0, x_c, y_c, material, priority);

        if (line_array.size() > 7) {
            if (line_array[index + 7] == "true") {
                disk_volu.arrow_moves_allowed = true;
                cout << "Volume named " << disk_volu.name << " can be moved with arrows" << endl;
            }
        }

        if (priority > highest_volume_priority) {
            highest_volume_priority = priority;
        }

        volu_array.push_back(disk_volu);
    }

    //"rectangle", width, height, x_r, y_r, water);
    index = getIndex(line_array, "rectangle");
    if (index != -1) {
        //cout << "geometry : one rectangle read" << endl;
        string name = line_array[index + 1];
        float width = stof(line_array[index + 2]);
        float height = stof(line_array[index + 3]);
        float x_r = stof(line_array[index + 4]);
        float y_r = stof(line_array[index + 5]);
        string material_name = line_array[index + 6];
        int priority = stoi(line_array[index + 7]);
        Material material = find_material(material_name);


        Volume rect_volu = Volume(name, "rectangle", width, height, x_r, y_r, material, priority);
        cout << "line_array size : " << line_array.size() << endl;
        for (int i = 0; i < line_array.size(); i++) {
            cout << i << " : " << line_array[i] << endl;
        }
        if (line_array.size() > 8) {
            if (line_array[index + 8] == "true") {
                        rect_volu.arrow_moves_allowed = true;
                        cout << "Volume named " << rect_volu.name << " can be moved with arrows" << endl;
            }
        }
        

        if (priority > highest_volume_priority) {
            highest_volume_priority = priority;
        }
        volu_array.push_back(rect_volu);
    }
}

int DataManager::getIndex(vector<string> v, string K){
    auto it = find(v.begin(), v.end(), K);
    // If element was found
    if (it != v.end()){
        // calculating the index
        // of K
        int index = it - v.begin();
        //cout << index << endl;
        return index;
    } else {
        // If the element is not
        // present in the vector
        //cout << "-1" << endl;
        return -1;
    }
}   


Material DataManager::find_material(string material_name) {
    for (int i = 0; i < mate_array.size(); i++) {
        if (mate_array[i].name == material_name) {
            return mate_array[i];
        } 
    }
    cout << "Material named " << material_name << " not found" << endl;
}

list<int> DataManager::find_fissile_volumes() {
    list<int> fissile_volume_indexes;
    for (int i = 0; i < volu_array.size(); i++) {
        if (volu_array[i].material.sigma_f > 0) {
            fissile_volume_indexes.push_back(i);
        }
    }
    return fissile_volume_indexes;
}

sf::Color DataManager::generate_random_color() {
    int r = rand() % 255;
    int g = rand() % 255;
    int b = rand() % 255;
    //cout << endl << "red : " << r << endl;

    sf::Color color = sf::Color(r, g, b);
    return color;
}


void DataManager::assign_language() {
    //language
    if (language == "french") {
        material_buckling_label_text = "Laplacien matiere (cm-2) : ";
        geometrical_buckling_label_text = "Laplacien geometrique (cm-2) : ";

        xs_c_text = "Section microscopique de capture (barn) :\n ";
        xs_s_text = "Section microscopique de diffusion (barn) :\n ";
        xs_f_text = "Section microscopique de fission (barn) :\n ";
        density_text = "Densite atomique (at/cm3) :\n ";
        pause_text = "Pause";
        play_text = "Reprendre";
        reset_text = "Reinitialiser";
        activate_reflexion_text = "Activer les reflexions";
        deactivate_reflexion_text = "Desactiver les reflexions";
        renormalization_text = "Periode de renormalisation : ";
        radius_text = "Rayon (cm) : ";
        width_text = "Largeur (cm) : ";
        height_text = "Hauteur (cm) : ";
        generate_source_text = "Generer les sources";
        automatic_source_text = "Sources en auto";
        manual_source_text = "Sources en manuel";
        source_delay_text = "Periode de generation des sources : ";
        nubar_text = "Nu (Nombre de neutrons par fission): ";

        selected_shapetext = " : volume selectionne";

        source_title = "PARAMETRES DES NEUTRONS SOURCES";
        geometry_panel_title = "GEOMETRIE DU VOLUME SELECTIONNE :";
        chemistry_panel_title = "CARACTERISTIQUES DU MATERIAU \nDU VOLUME SELECTIONNE :";
        source_number_text = "Nombre de neutrons \nsources generes :";
        source_coordinates_text = "x, y des \nneutrons source : ";
        keff_button_text = "forcer le calcul du keff";
        keff_automatic_button_text = "calcul repete de keff (par batches)";
        keff_label_text = "Keff du batch en cours = ";
        last_keff_label_text = "Keff du dernier batch = ";
        averaged_keff_label_text = "Keff moyenne sur les batch calcules = ";
        sigma_label_text = "Sigma keff (pcm) : ";
        
    
    } else if (language == "english") {
        material_buckling_label_text = "Material Buckling (cm-2): ";
        geometrical_buckling_label_text = "Geometrical Buckling (cm-2): ";
        xs_c_text = "Microscopic capture xs (barn):\n ";
        xs_s_text = "Microscopic scattering xs (barn):\n ";
        xs_f_text = "Microscopic fission xs (barn):\n ";
        density_text = "Atomic density (at/cm3):\n ";
        pause_text = "Pause";
        play_text = "Resume";
        reset_text = "Reset Parameters";
        activate_reflexion_text = "Activate reflexions";
        deactivate_reflexion_text = "Deactivate reflexions";
        renormalization_text = "Renormalization period (sec) ";
        radius_text = "Radius (cm): ";
        width_text = "Width (cm): ";
        height_text = "Height (cm): ";
        generate_source_text = "Generate sources";
        automatic_source_text = "Source in automatic mode";
        manual_source_text = "Source in manual mode";
        source_delay_text = "Source generation period : ";
        nubar_text = "Nu (Number of neutrons per fission): ";

        selected_shapetext = " : selected volume";

        source_title = "SOURCE NEUTRONS PARAMETERS";
        geometry_panel_title = "GEOMETRY OF THE SELECTED VOLUME:";
        chemistry_panel_title = "SELECTED VOLUME \nMATERIAL CHARACTERISTICS:";

        source_number_text = "Number of generated \nsource neutrons:";
        source_coordinates_text = "x, y of \nsource neutrons: ";
        keff_button_text = "force keff computing";
        keff_automatic_button_text = "repeted keff computing (batches)";
        keff_label_text = "Current batch Keff = ";
        last_keff_label_text = "Last batch Keff = ";
        averaged_keff_label_text = "Computed batches averaged Keff = ";
        sigma_label_text = "Sigma keff (pcm) = ";

    }
}


void DataManager::parse_panels_visibility(vector<string> line_array) {
    
    int index = getIndex(line_array, "keff_panel_is_visible");
    if (index != -1) {
        if (line_array[index + 1] == "true") {
            keff_panel_is_visible = true;
        }
        else if (line_array[index + 1] == "false") {
            keff_panel_is_visible = false;
        }
    }

    index = getIndex(line_array, "source_panel_is_visible");
    if (index != -1) {
        if (line_array[index + 1] == "true") {
            source_panel_is_visible = true;
        }
        else if (line_array[index + 1] == "false") {
            source_panel_is_visible = false;
        }
    }    

    index = getIndex(line_array, "geometry_panel_is_visible");
    if (index != -1) {
        if (line_array[index + 1] == "true") {
            geometry_panel_is_visible = true;
        }
        else if (line_array[index + 1] == "false") {
            geometry_panel_is_visible = false;
        }
    }

    index = getIndex(line_array, "chemistry_panel_is_visible");
    if (index != -1) {
        if (line_array[index + 1] == "true") {
            chemistry_panel_is_visible = true;
        }
        else if (line_array[index + 1] == "false") {
            chemistry_panel_is_visible = false;
        }
    }

}


void DataManager::delete_one_volume(string name) {
    for (int i = 0; i < volu_array.size(); i++) {
        if (volu_array[i].name == name) {
            volu_array.erase(volu_array.begin() + i);
        }
    }
}

void DataManager::parse_collision_type(vector<string> line_array) {
    int index = getIndex(line_array, "collision_type");
    if (index != -1) {
        collision_type = line_array[index + 1];
    }
}