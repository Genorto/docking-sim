#include "simulation.h"

Simulation::Simulation() {
    window_ = new sf::RenderWindow(sf::VideoMode(1200, 800), "Docking simulation");
    event_ = new sf::Event;
    /* implement objects */
}

void Simulation::CheckEvents() {
    while (window_->pollEvent(*event_)) {
        switch (event_->type) {
        case sf::Event::Closed:
            window_->close();
            break;
        }
    }
}

void Simulation::Draw() {
    window_->clear();
    /* draw objects */
    window_->display();
}

bool Simulation::isOpen() {
    return window_->isOpen();
}

Simulation::~Simulation() {}
