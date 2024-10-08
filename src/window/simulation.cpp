#include "../../includes/window/simulation.h"

Simulation::Simulation() {
    window_ = new sf::RenderWindow(sf::VideoMode(1200, 800), "Docking simulation");
    event_ = new sf::Event;
    model_ = new Model;
    /* these arguments are set by user */
    model_->SetStepSize(1);
    model_->SetFont("assets/fonts/roboto.ttf");
    model_->SetTimeLimits(30, 12);
    model_->SetWeightLimits(100, 500);
    model_->SetRejectionLimits(1, 6);
    model_->SetFineLimits(20, 100);
    model_->SetSpeedLimits(1, 3);

    Crane* temp_crane;
    temp_crane = new BulkCrane;
    temp_crane->SetPos(50, 50);
    temp_crane->SetSize(100, 100);
    temp_crane->SetName("Red impostor");
    temp_crane->SetModel("assets/sprites/default_crane.png");
    model_->AddBulkCrane(temp_crane);

    temp_crane = new FluidCrane;
    temp_crane->SetPos(150, 50);
    temp_crane->SetSize(100, 100);
    temp_crane->SetName("Best crane ever");
    temp_crane->SetModel("assets/sprites/default_crane.png");
    model_->AddFluidCrane(temp_crane);

    temp_crane = new ContainerCrane;
    temp_crane->SetPos(250, 50);
    temp_crane->SetSize(100, 100);
    temp_crane->SetName("lol kek cheburek kek lol arbidol");
    temp_crane->SetModel("assets/sprites/default_crane.png");
    model_->AddContainerCrane(temp_crane);
    
    Ship* temp_ship;
    temp_ship = new CargoShip;
    temp_ship->set_weight(1000);
    temp_ship->set_arrival_time({ 1, 0 });
    temp_ship->set_ship_name("Green Sausages");
    temp_ship->SetPos(90, 90);
    temp_ship->SetSize(80, 150);
    temp_ship->SetModel("assets/sprites/default_ship.png");
    model_->AddCargoShip(temp_ship);

    temp_ship = new CargoShip;
    temp_ship->set_weight(10000);
    temp_ship->set_arrival_time({ 1, 0 });
    temp_ship->set_ship_name("Lebron James");
    temp_ship->SetPos(190, 170);
    temp_ship->SetSize(80, 150);
    temp_ship->SetModel("assets/sprites/default_ship.png");
    model_->AddCargoShip(temp_ship);

    model_->RandomizeShipsData();

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
            if (event_->key.scancode == sf::Keyboard::Scan::Right) {
                model_->NextStep();
                model_->UpdateRejections();
                model_->UpdateQueues();
                model_->UpdateUnloads();
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

    model_->DisplayTime(window_);
    model_->DisplayShips(window_);
    model_->DisplayCranes(window_);
    chw_->Draw(window_);
    window_->display();
}

bool Simulation::isOpen() {
    return window_->isOpen();
}

Simulation::~Simulation() {}
