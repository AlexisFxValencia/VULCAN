#include "GUIWindow.h"

GUIWindow::GUIWindow() {

}

void GUIWindow::display_credits_window(DataManager& dm) {

    sf::RenderWindow window(sf::VideoMode(400, 300), "Credits");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Text text;
        sf::Font font;
        font.loadFromFile("themes/arial.ttf");
        text.setFont(font);
        text.setCharacterSize(22); // in pixels
        text.setFillColor(sf::Color::Black);
        text.setOrigin(text.getLocalBounds().width, text.getLocalBounds().height);
        window.clear(sf::Color::White); //sf::Color(255, 255, 255)
        text.setString("Neutronics Simulator \nDevelopped by Alexis Valencia \nalexis.valencia@irsn.fr \nVersion : " + dm.version);
        text.setPosition(window.getSize().x / 10., window.getSize().y / 4.);
        window.draw(text);
        window.display();
    }

}

void GUIWindow::display_help_window(DataManager& dm) {

    sf::RenderWindow window(sf::VideoMode(700, 400), "Help");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Text text;
        sf::Font font;
        font.loadFromFile("themes/arial.ttf");
        text.setFont(font);
        text.setCharacterSize(22); // in pixels
        text.setFillColor(sf::Color::Black);
        text.setOrigin(text.getLocalBounds().width, text.getLocalBounds().height);
        window.clear(sf::Color::White); //sf::Color(255, 255, 255)
        string help = "click on a volume to move it with the mouse or with Z-Q-S-D \n\n";
        help.append("Right click in a free space to create a new shape \n\n");
        help.append("Right click on an existing shape to delete or duplicate it \n\n");
        help.append("Save the current file : File -> Save \n\n");
        help.append("Load a saved file : File -> Load -> input_saved.ns \n\n");
        help.append("The simulation pauses when the " + to_string(dm.max_nb_neutrons) + " neutrons limit is reached \n\n");
        text.setString(help);
        text.setPosition(window.getSize().x / 20., window.getSize().y / 8.);
        window.draw(text);
        window.display();
    }

}

void GUIWindow::display_max_nb_neutrons_window(DataManager& dm) {
    sf::RenderWindow window(sf::VideoMode(500, 100), "Max number of neutrons reached");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Text text;
        sf::Font font;
        font.loadFromFile("themes/arial.ttf");
        text.setFont(font);
        text.setCharacterSize(22); // in pixels
        text.setFillColor(sf::Color::Black);
        text.setOrigin(text.getLocalBounds().width, text.getLocalBounds().height);
        window.clear(sf::Color::White); //sf::Color(255, 255, 255)
        string message = "Nombre maximum de neutrons atteint (" + to_string(dm.max_nb_neutrons) + ")";
        text.setString(message);
        text.setPosition(window.getSize().x / 20., window.getSize().y / 4.);
        window.draw(text);
        window.display();
    }

}
