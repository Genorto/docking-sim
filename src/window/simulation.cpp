#include "../../includes/window/simulation.h"

Simulation::Simulation() {
    window_ = new sf::RenderWindow(sf::VideoMode(1200, 800), "Docking simulation");
    event_ = new sf::Event;

    Crane* crane_ = new BulkCrane;
    crane_->SetPos(50, 50);
    crane_->SetSize(100, 100);
    crane_->SetModel("assets/sprites/default_crane.png");
    cranes_.push_back(crane_);

    crane_ = new FluidCrane;
    crane_->SetPos(150, 50);
    crane_->SetSize(100, 100);
    crane_->SetModel("assets/sprites/default_crane.png");
    cranes_.push_back(crane_);

    crane_ = new ContainerCrane;
    crane_->SetPos(250, 50);
    crane_->SetSize(100, 100);
    crane_->SetModel("assets/sprites/default_crane.png");
    cranes_.push_back(crane_);

    Ship* ship_ = new CargoShip(100, { 0, 0 }, "GreenSausages");
    ship_->SetPos(90, 90);
    ship_->SetSize(80, 150);
    ship_->SetModel("assets/sprites/default_ship.png");
    cranes_[0]->AddToQueue(ship_);
    ships_.push_back(ship_);

    ship_ = new CargoShip(100, { 0, 0 }, "GreenSausages");
    ship_->SetPos(190, 90);
    ship_->SetSize(80, 150);
    ship_->SetModel("assets/sprites/default_ship.png");
    // cranes_[1]->AddToQueue(ship_);
    ships_.push_back(ship_);

    ship_ = new CargoShip(100, { 0, 0 }, "GreenSausages");
    ship_->SetPos(290, 90);
    ship_->SetSize(80, 150);
    ship_->SetModel("assets/sprites/default_ship.png");
    // cranes_[2]->AddToQueue(ship_);
    ships_.push_back(ship_);

    chw_ = new CursorHoverWindow;
    chw_->SetSize(500, 300);
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
    bool checking = true;
    if (checking)
        for (auto crane : cranes_) {
            if (crane->isHovered(cursor)) {
                chw_->SetInfo(crane->GetInfo());
                chw_->SetPos(cursor.x, cursor.y);
                checking = false;
                break;
            }
        }
    /*
    if (checking)
        for (auto ship : ships_) {
            if (ship->isHovered(cursor)) {
                chw_->SetInfo(ship->GetInfo());
                chw_->SetPos(cursor.x, cursor.y);
                checking = false;
                break;
            }
        }
    */
}

void Simulation::Draw() {
    window_->clear(sf::Color::Cyan);
    for (auto ship : ships_) ship->Draw(window_);
    for (auto crane : cranes_) crane->Draw(window_);
    chw_->Draw(window_);
    window_->display();
}

bool Simulation::isOpen() {
    return window_->isOpen();
}

Simulation::~Simulation() {}
