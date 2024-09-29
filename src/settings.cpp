#include "settings.h"

Settings::Settings() {
    window_ = new sf::RenderWindow(sf::VideoMode(500, 800), "Settings");
    event_ = new sf::Event;
}

void Settings::CheckEvents() {
    while (window_->pollEvent(*event_)) {
        switch (event_->type) {
        case sf::Event::Closed:
            window_->close();
            break;
        }
    }
}

void Settings::Draw() {
    window_->clear();
    /* draw all elements */
    window_->display();
}

bool Settings::isOpen() {
    return window_->isOpen();
}

Settings::~Settings() {}
