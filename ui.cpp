#include "ui.h"

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

void startUI() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Artist Search");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}
