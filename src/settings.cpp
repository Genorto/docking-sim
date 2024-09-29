#include "settings.h"

Settings::Settings() {
    window_ = new sf::RenderWindow(sf::VideoMode(1000, 1000), "SFML works");
    event_ = new sf::Event;
}

void Settings::Draw() {
    window_->clear();
    window_->display();
}

void Settings::CheckEvents() {
    while (window_->pollEvent(*event_)) {
        if (event_->type == sf::Event::Closed)
            window_->close();
    }
}

bool Settings::isOpen() {
    return window_->isOpen();
}
