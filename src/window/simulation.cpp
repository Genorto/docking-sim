#include "../../includes/window/simulation.h"

Simulation::Simulation() {
    window_ = new sf::RenderWindow(sf::VideoMode(1200, 800), "Docking simulation");
    event_ = new sf::Event;

    crane_ = new BulkCrane;
    crane_->SetPos(50, 50);
    crane_->SetSize(100, 100);
    crane_->SetModel("assets/sprites/default_crane.png");

    ship_ = new CargoShip(100, { 0, 0 }, "GreenSausages");
    ship_->SetPos(90, 90);
    ship_->SetSize(50, 100);
    ship_->SetModel("assets/sprites/default_ship.png");
    crane_->AddToQueue(ship_);

    chw_ = new CursorHoverWindow;
    chw_->SetSize(100, 100);
    chw_->SetFont("assets/fonts/roboto.ttf");
}

void Simulation::CheckEvents() {
    while (window_->pollEvent(*event_)) {
        switch (event_->type) {
        case sf::Event::Closed:
            window_->close();
            break;
        }
    }
    /* check all objects if they are hovered */
    std::vector<std::string*> empty(0);
    chw_->SetInfo(empty);
    chw_->SetPos(-1000, -1000);
    sf::Vector2i cursor = sf::Mouse::getPosition(*window_);
    if (crane_->isHovered(cursor)) {
        chw_->SetInfo(crane_->GetInfo());
        chw_->SetPos(cursor.x, cursor.y);
    }
}

void Simulation::Draw() {
    window_->clear(sf::Color::Cyan);
    ship_->Draw(window_);
    crane_->Draw(window_);
    chw_->Draw(window_);
    window_->display();
}

bool Simulation::isOpen() {
    return window_->isOpen();
}

Simulation::~Simulation() {}
