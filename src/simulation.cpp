#include "simulation.h"

Simulation::Simulation() {
    window_ = new sf::RenderWindow(sf::VideoMode(1200, 800), "Docking simulation");
    event_ = new sf::Event;
    crane_ = new BulkCrane;
    crane_->SetPos(100, 100);
    crane_->SetSize(100, 100);
    crane_->SetModel("src/assets/sprites/default_crane.png");
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
    window_->clear(sf::Color::Cyan);
    crane_->Draw(window_);
    window_->display();
}

bool Simulation::isOpen() {
    return window_->isOpen();
}

Simulation::~Simulation() {}
