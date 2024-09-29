#include "gameplay.h"

Gameplay::Gameplay() {
    window_ = new sf::RenderWindow(sf::VideoMode(1200, 800), "Docking simulation");
    event_ = new sf::Event;
}

void Gameplay::CheckEvents() {
    while (window_->pollEvent(*event_)) {
        switch (event_->type) {
        case sf::Event::Closed:
            window_->close();
            break;
        }
    }
}

void Gameplay::Draw() {
    window_->clear();
    /* draw all elements */
    window_->display();
}

bool Gameplay::isOpen() {
    return window_->isOpen();
}

Gameplay::~Gameplay() {}
