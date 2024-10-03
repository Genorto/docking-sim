#include "../../includes/window/simulation.h"
#include "iostream"

Simulation::Simulation() {
    window_ = new sf::RenderWindow(sf::VideoMode(1200, 800), "Docking simulation");
    event_ = new sf::Event;
    model_ = new Model;
    /* these arguments are set by user */
    model_->CreateCranes(1, 1, 1);
    model_->CreateShips(1, 1);

    model_->GetBulkCranes()[0]->SetPos(50, 50);
    model_->GetBulkCranes()[0]->SetSize(100, 100);
    model_->GetBulkCranes()[0]->SetName("Red impostor");
    model_->GetBulkCranes()[0]->SetModel("assets/sprites/default_crane.png");

    model_->GetFluidCranes()[0]->SetPos(150, 50);
    model_->GetFluidCranes()[0]->SetSize(100, 100);
    model_->GetFluidCranes()[0]->SetName("Best crane ever");
    model_->GetFluidCranes()[0]->SetModel("assets/sprites/default_crane.png");

    model_->GetContainerCranes()[0]->SetPos(250, 50);
    model_->GetContainerCranes()[0]->SetSize(100, 100);
    model_->GetContainerCranes()[0]->SetName("lol kek cheburek kek lol arbidol");
    model_->GetContainerCranes()[0]->SetModel("assets/sprites/default_crane.png");
    

    model_->GetCargoShips()[0]->SetPos(90, 90);
    model_->GetCargoShips()[0]->SetSize(80, 150);
    model_->GetCargoShips()[0]->SetModel("assets/sprites/default_ship.png");

    model_->GetTankers()[0]->SetPos(190, 90);
    model_->GetTankers()[0]->SetSize(80, 150);
    model_->GetTankers()[0]->SetModel("assets/sprites/default_ship.png");

    chw_ = new CursorHoverWindow;
    chw_->SetSize(200, 150);
    chw_->SetFont("assets/fonts/roboto.ttf");
}

void Simulation::CheckEvents() {
    while (window_->pollEvent(*event_)) {
        switch (event_->type) {
        case sf::Event::Closed:
            window_->close();
            break;

        case sf::Event::KeyPressed:
            if (event_->key.scancode == sf::Keyboard::Right) {

            }
        }
    }
    /* check all objects if they are hovered */
    std::vector<std::string*> empty(0);
    chw_->SetInfo(empty);
    chw_->SetPos(-1000, -1000);
    sf::Vector2i cursor = sf::Mouse::getPosition(*window_);

    for (auto ship : model_->GetCargoShips()) {
        if (ship->isHovered(cursor)) {
            chw_->SetInfo(ship->GetInfo());
            chw_->SetPos(cursor.x, cursor.y);
            return;
        }
    }

    for (auto ship : model_->GetTankers()) {
        if (ship->isHovered(cursor)) {
            chw_->SetInfo(ship->GetInfo());
            chw_->SetPos(cursor.x, cursor.y);
            return;
        }
    }

    for (auto crane : model_->GetBulkCranes()) {
        if (crane->isHovered(cursor)) {
            chw_->SetInfo(crane->GetInfo());
            chw_->SetPos(cursor.x, cursor.y);
            return;
        }
    }

    for (auto crane : model_->GetFluidCranes()) {
        if (crane->isHovered(cursor)) {
            chw_->SetInfo(crane->GetInfo());
            chw_->SetPos(cursor.x, cursor.y);
            return;
        }
    }

    for (auto crane : model_->GetContainerCranes()) {
        if (crane->isHovered(cursor)) {
            chw_->SetInfo(crane->GetInfo());
            chw_->SetPos(cursor.x, cursor.y);
            return;
        }
    }
}

void Simulation::Draw() {
    window_->clear(sf::Color::Cyan);

    for (auto ship : model_->GetCargoShips()) {
        ship->Draw(window_);
    }

    for (auto ship : model_->GetTankers()) {
        ship->Draw(window_);
    }

    for (auto crane : model_->GetBulkCranes()) {
        crane->Draw(window_);
    }

    for (auto crane : model_->GetFluidCranes()) {
        crane->Draw(window_);
    }

    for (auto crane : model_->GetContainerCranes()) {
        crane->Draw(window_);
    }

    chw_->Draw(window_);
    window_->display();
}

bool Simulation::isOpen() {
    return window_->isOpen();
}

Simulation::~Simulation() {}
