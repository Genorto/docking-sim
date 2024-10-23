#include "../../includes/window/simulation.h"
#include "iostream"

Simulation::Simulation() {
    window_ = new sf::RenderWindow(sf::VideoMode(1200, 800), "Docking simulation", sf::Style::Close);
    event_ = new sf::Event;
    model_ = new Model;
    /* these arguments are set by user */
    model_->SetStepSize(1);
    model_->SetFont("assets/fonts/roboto.ttf");
    model_->SetTimeLimits(31, 0);
    model_->SetRejectionLimits(1, 6);
    model_->SetFine(100);
    model_->SetSpeedLimits(1, 5);
    model_->SetUnloadRejectionLimits(1, 5);
    model_->SetFPS(240);
    model_->SetStepLength(3);

    Crane* temp_crane;
    temp_crane = new BulkCrane;
    temp_crane->SetPos(50, 50);
    temp_crane->SetSize(100, 100);
    temp_crane->SetName("Red impostor");
    temp_crane->SetModel("assets/sprites/default_crane.png");
    temp_crane->SetSpace(10);
    model_->AddBulkCrane(temp_crane);

    temp_crane = new FluidCrane;
    temp_crane->SetPos(150, 50);
    temp_crane->SetSize(100, 100);
    temp_crane->SetName("Best crane ever");
    temp_crane->SetModel("assets/sprites/default_crane.png");
    temp_crane->SetSpace(10);
    model_->AddFluidCrane(temp_crane);

    temp_crane = new ContainerCrane;
    temp_crane->SetPos(250, 50);
    temp_crane->SetSize(100, 100);
    temp_crane->SetName("lol kek cheburek kek lol arbidol");
    temp_crane->SetModel("assets/sprites/default_crane.png");
    temp_crane->SetSpace(10);
    model_->AddContainerCrane(temp_crane);

    Ship* temp_ship;
    temp_ship = new CargoShip;
    temp_ship->set_weight(5000);
    temp_ship->SetArrivalTime({ 0, 1 });
    temp_ship->set_ship_name("Green Sausages");
    temp_ship->SetSize(80, 150);
    temp_ship->SetModel("assets/sprites/default_ship.png");
    model_->AddShip(temp_ship);

    temp_ship = new CargoShip;
    temp_ship->set_weight(5000);
    temp_ship->SetArrivalTime({ 0, 1 });
    temp_ship->set_ship_name("Lebron James");
    temp_ship->SetSize(80, 150);
    temp_ship->SetModel("assets/sprites/default_ship.png");
    model_->AddShip(temp_ship);

    temp_ship = new CargoShip;
    temp_ship->set_weight(5000);
    temp_ship->SetArrivalTime({ 0, 1 });
    temp_ship->set_ship_name("KKK");
    temp_ship->SetSize(80, 150);
    temp_ship->SetModel("assets/sprites/default_ship.png");
    model_->AddShip(temp_ship);

    temp_ship = new CargoShip;
    temp_ship->set_weight(5000);
    temp_ship->SetArrivalTime({ 0, 1 });
    temp_ship->set_ship_name("Evergreen");
    temp_ship->SetSize(80, 150);
    temp_ship->SetModel("assets/sprites/default_ship.png");
    model_->AddShip(temp_ship);

    temp_ship = new CargoShip;
    temp_ship->set_weight(5000);
    temp_ship->SetArrivalTime({ 0, 1 });
    temp_ship->set_ship_name("Yeei 52");
    temp_ship->SetSize(80, 150);
    temp_ship->SetModel("assets/sprites/default_ship.png");
    model_->AddShip(temp_ship);

    temp_ship = new Tanker;
    temp_ship->set_weight(5000);
    temp_ship->SetArrivalTime({ 0, 1 });
    temp_ship->set_ship_name("First tanker ever");
    temp_ship->SetSize(80, 150);
    temp_ship->SetModel("assets/sprites/default_ship.png");
    model_->AddShip(temp_ship);

    temp_ship = new Tanker;
    temp_ship->set_weight(5000);
    temp_ship->SetArrivalTime({ 0, 1 });
    temp_ship->set_ship_name("Big tanker");
    temp_ship->SetSize(80, 150);
    temp_ship->SetModel("assets/sprites/default_ship.png");
    model_->AddShip(temp_ship);

    temp_ship = new Tanker;
    temp_ship->set_weight(5000);
    temp_ship->SetArrivalTime({ 0, 1 });
    temp_ship->set_ship_name("Gorillaz");
    temp_ship->SetSize(80, 150);
    temp_ship->SetModel("assets/sprites/default_ship.png");
    model_->AddShip(temp_ship);

    model_->RandomizeShipsData();
    model_->Update();

    chw_ = new CursorHoverWindow;
    chw_->SetSize(200, 150);
    chw_->SetFont("assets/fonts/roboto.ttf");
}

Simulation::Simulation(Settings* sett) {
    window_ = new sf::RenderWindow(sf::VideoMode(1500, 800), "Docking simulation", sf::Style::Close);
    moving = false;
    view.reset(sf::FloatRect(0, 0, default_center.x * 2, default_center.y * 2));
    window_->setView(view);
    event_ = new sf::Event;
    model_ = new Model;
    /* these arguments are set by user */
    model_->SetStepSize(sett->GetStepSize());
    model_->SetFont("assets/fonts/roboto.ttf");
    model_->SetTimeLimits(31, 0);
    model_->SetRejectionLimits(sett->GetRejectionLimits());
    model_->SetFine(sett->GetFine());
    model_->SetSpeedLimits(1, 5);
    model_->SetUnloadRejectionLimits(1, 5); // may be modified
    model_->SetFPS(240);
    model_->SetStepLength(5);

    int bulk_cnt = sett->GetBulkCranesNumber();
    int fluid_cnt = sett->GetFluidCranesNumber();
    int container_cnt = sett->GetContainerCranesNumber();
    int crane_x = 50, crane_y = 100;
    int crane_size_x = 150, crane_size_y = 150;
    while (bulk_cnt--) {
        Crane* temp_crane = new BulkCrane;
        temp_crane->SetPos(crane_x, crane_y);
        temp_crane->SetSize(crane_size_x, crane_size_y);
        temp_crane->SetModel("assets/sprites/default-crane-pixel-top.png");
        temp_crane->SetSpace(30);
        model_->AddBulkCrane(temp_crane);
        crane_x += crane_size_x + 150;
    }
    while (fluid_cnt--) {
        Crane* temp_crane = new FluidCrane;
        temp_crane->SetPos(crane_x, crane_y);
        temp_crane->SetSize(crane_size_x, crane_size_y);
        temp_crane->SetModel("assets/sprites/default-crane-pixel-top.png");
        temp_crane->SetSpace(30);
        model_->AddFluidCrane(temp_crane);
        crane_x += crane_size_x + 150;
    }
    while (container_cnt--) {
        Crane* temp_crane = new ContainerCrane;
        temp_crane->SetPos(crane_x, crane_y);
        temp_crane->SetSize(crane_size_x, crane_size_y);
        temp_crane->SetModel("assets/sprites/default-crane-pixel-top.png");
        temp_crane->SetSpace(30);
        model_->AddContainerCrane(temp_crane);
        crane_x += crane_size_x + 150;
    }

    std::vector<Ship*> ships = sett->GetShips();
    for (auto ship : ships) {
        ship->SetSize(80, 100 + ship->get_weight() / 10);
        if (ship->get_type() == ShipType::CargoShip) ship->SetModel("assets/sprites/default_ship.png");
        else ship->SetModel("assets/sprites/default_tanker.png");
        if (ship->get_type() == ShipType::CargoShip) {
            model_->AddShip(ship);
        } else {
            model_->AddShip(ship);
        }
    }

    model_->RandomizeShipsData();
    model_->Update();

    chw_ = new CursorHoverWindow;
    chw_->SetSize(200, 150);
    chw_->SetFont("assets/fonts/roboto.ttf");
}

void Simulation::CheckEvents() {
    while (window_->pollEvent(*event_)) {
        int curr_hours, end_hours;
        switch (event_->type) {
        case sf::Event::Closed:
            curr_hours = model_->GetTime().first * 24 + model_->GetTime().second;
            end_hours = model_->GetTimeLimits().first * 24 + model_->GetTimeLimits().second;
            while (end_hours > curr_hours) {
                model_->UpdateShipsPos();
                model_->NextHour();
                model_->Update();
                ++curr_hours;
            }
            window_->close();
            break;

        case sf::Event::KeyPressed:
            if (event_->key.scancode == sf::Keyboard::Scan::Right) {
                int cycles = model_->GetStepSize();
                while (cycles--) {
                    model_->UpdateShipsPos();
                    model_->NextHour();
                    model_->Update();
                }
            } else if (event_->key.scancode == sf::Keyboard::Scan::Escape) {
                curr_hours = model_->GetTime().first * 24 + model_->GetTime().second;
                end_hours = model_->GetTimeLimits().first * 24 + model_->GetTimeLimits().second;
                while (end_hours > curr_hours) {
                    model_->UpdateShipsPos();
                    model_->NextHour();
                    model_->Update();
                    ++curr_hours;
                }
                window_->close();
            }
            break;

        case sf::Event::MouseButtonPressed:
            if (event_->mouseButton.button == 0) {
                moving = true;
                oldPos = window_->mapPixelToCoords(sf::Vector2i(event_->mouseButton.x, event_->mouseButton.y));
            }
            break;

        case  sf::Event::MouseButtonReleased:
            if (event_->mouseButton.button == 0) {
                moving = false;
            }
            break;

        case sf::Event::MouseMoved:
            if (!moving) break;
            const sf::Vector2f deltaPos = oldPos - window_->mapPixelToCoords(sf::Vector2i(event_->mouseMove.x, event_->mouseMove.y));
            view.setCenter(view.getCenter() + deltaPos);
            window_->setView(view);
            oldPos = window_->mapPixelToCoords(sf::Vector2i(event_->mouseMove.x, event_->mouseMove.y));
            break;
        }


    }
    if (model_->GetClock() >= model_->GetStepLength()) {
        int cycles = model_->GetStepSize();
        while (cycles--) {
            model_->UpdateShipsPos();
            model_->NextHour();
            model_->Update();
        }
    }

    /* check all objects if they are hovered */

    std::vector<std::string*> empty(0);
    chw_->SetInfo(empty);
    chw_->SetPos(-1000, -1000);
    sf::Vector2i cursor = sf::Mouse::getPosition(*window_);
    cursor.x += view.getCenter().x - default_center.x;
    cursor.y += view.getCenter().y - default_center.y;

    for (auto ship : model_->GetShips()) {
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
    sf::Sprite dock;
    sf::Texture texture;
    texture.loadFromFile("assets/sprites/dock.png");
    dock.setTexture(texture);

    for (auto ship : model_->GetShips()) {
        ship->Animate(model_->GetClock(), model_->GetFPS(), model_->GetStepLength());
        ship->Draw(window_);
    }

    for (auto crane : model_->GetBulkCranes()) {
        crane->Draw(window_);
        dock.setPosition(crane->GetPos().first - 600, 0);
        window_->draw(dock);
    }

    for (auto crane : model_->GetFluidCranes()) {
        crane->Draw(window_);
        dock.setPosition(crane->GetPos().first - 600, 0);
        window_->draw(dock);
    }

    for (auto crane : model_->GetContainerCranes()) {
        crane->Draw(window_);
        dock.setPosition(crane->GetPos().first - 600, 0);
        window_->draw(dock);
    }

    std::pair<int, int> tm = model_->GetTime();
    sf::Text time;
    sf::Font font;
    font.loadFromFile("assets/fonts/roboto.ttf");
    time.setFont(font);
    time.setCharacterSize(30);
    time.setFillColor(sf::Color::White);
    time.setString("day " + std::to_string(tm.first) + " time " + std::to_string(tm.second) + " : 00");
    time.setPosition(window_->getSize().x - time.getLocalBounds().width - 15 + view.getCenter().x - default_center.x, 10 + view.getCenter().y - default_center.y);
    window_->draw(time);

    chw_->Draw(window_);
    window_->display();
}

bool Simulation::isOpen() {
    return window_->isOpen();
}

Model* Simulation::GetModel() {
    return model_;
}

Simulation::~Simulation() {}
