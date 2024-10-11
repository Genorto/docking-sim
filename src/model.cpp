#include "../includes/model.h"
#include "iostream"

Model::Model() {
    clock_ = new sf::Clock;
}

void Model::RandomizeShipsData() {
    for (auto ship : ships_) {
        if (rand() % 2) {
            ship->set_arrival_rejection(rand() % (rejection_limits_.second -
                rejection_limits_.first + 1) + rejection_limits_.first);
        }
    }
}

void Model::AddBulkCrane(Crane*& crane) {
    bulk_cranes_.push_back(crane);
}

void Model::AddFluidCrane(Crane*& crane) {
    fluid_cranes_.push_back(crane);
}

void Model::AddContainerCrane(Crane*& crane) {
    container_cranes_.push_back(crane);
}

void Model::AddShip(Ship*& ship) {
    ships_.push_back(ship);
    ++ships_cnt;
}

std::vector<Crane*> Model::GetBulkCranes() {
    return bulk_cranes_;
}

std::vector<Crane*> Model::GetFluidCranes() {
    return fluid_cranes_;
}

std::vector<Crane*> Model::GetContainerCranes() {
    return container_cranes_;
}

std::vector<Ship*> Model::GetShips() {
    return ships_;
}

double Model::GetClock() {
    return clock_->getElapsedTime().asSeconds();
}

void Model::SetFPS(int fps) {
    fps_ = fps;
}

int Model::GetFPS() {
    return fps_;
}

void Model::SetStepLength(double step_length) {
    step_length_ = step_length;
}

double Model::GetStepLength() {
    return step_length_;
}

void Model::SetStepSize(int size) {
    step_size_ = size;
}

void Model::SetWeightLimits(std::pair<int, int> lim) {
    weight_limits_ = lim;
}

void Model::SetWeightLimits(int lim_l, int lim_r) {
    weight_limits_ = { lim_l, lim_r };
}

void Model::SetTimeLimits(std::pair<int, int> lim) {
    time_limits_ = lim;
}

void Model::SetTimeLimits(int lim_l, int lim_r) {
    time_limits_ = { lim_l, lim_r };
}

void Model::SetRejectionLimits(std::pair<int, int> lim) {
    rejection_limits_ = lim;
}

void Model::SetRejectionLimits(int lim_l, int lim_r) {
    rejection_limits_ = { lim_l, lim_r };
}

void Model::SetUnloadRejectionLimits(std::pair<int, int> lim) {
    unload_rejection_limits_ = lim;
}

void Model::SetUnloadRejectionLimits(int lim_l, int lim_r) {
    unload_rejection_limits_ = { lim_l, lim_r };
}

void Model::SetFine(int fine) {
    fine_ = fine;
}

void Model::SetSpeedLimits(std::pair<int, int> lim) {
    speed_limits_ = lim;
}

void Model::SetSpeedLimits(int lim_l, int lim_r) {
    speed_limits_ = { lim_l, lim_r };
}

void Model::SetFont(std::string font_dir) {
    font_.loadFromFile(font_dir);
}

void Model::NextStep() {
    int temp_day = day_, temp_hour = hour_;
    temp_hour += step_size_;
    temp_day += temp_hour / 24;
    temp_hour %= 24;
    if (temp_day == time_limits_.first && temp_hour > time_limits_.second ||
        temp_day > time_limits_.first) return;
    day_ = temp_day;
    hour_ = temp_hour;
}

std::pair<int, int> Model::GetTime() {
    return { day_, hour_ };
}

void Model::Update() {
    UpdateUnloads();
    UpdateQueues();
    UpdateRejections();
    clock_->restart();
}

void Model::UpdateRejections() {
    std::string* message;
    std::pair<int, int> cur_tm = { day_, hour_ };
    for (auto ship : ships_) {
        if (ship->get_arrival_time() == cur_tm) {
            int day = ship->get_arrival_time().first;
            int hour = ship->get_arrival_time().second + ship->get_arrival_rejection();
            day += hour / 24;
            hour %= 24;
            message = new std::string;
            *message = ship->get_ship_name() + "'s arrival is postponed to day " + std::to_string(day) + " time " + std::to_string(hour) + " : 00";
            log.push_back(message);
            std::cout << *message << "\n";
        }
    }
 }

void Model::UpdateQueues() {
    std::pair<int, int> cur_tm = { day_, hour_ };
    for (auto ship : ships_) {
        std::pair<int, int> arr_tm = ship->get_arrival_time();
        arr_tm.second += ship->get_arrival_rejection();
        arr_tm.first += arr_tm.second / 24;
        arr_tm.second %= 24;
        size_t smallest_queue = INT_MAX, best_option = 0;
        if (cur_tm == arr_tm) {
            switch (ship->get_type()) {
            case ShipType::CargoShip:
                for (size_t it = 0; it < bulk_cranes_.size(); ++it) {
                    if (bulk_cranes_[it]->GetQueueSize() < smallest_queue) {
                        smallest_queue = bulk_cranes_[it]->GetQueueSize();
                        best_option = it;
                    }
                }
                bulk_cranes_[best_option]->AddToQueue(ship);
                ship->Show();
                break;


            case ShipType::Tanker:
                bool fluid = true;
                for (size_t it = 0; it < fluid_cranes_.size(); ++it) {
                    if (fluid_cranes_[it]->GetQueueSize() < smallest_queue) {
                        smallest_queue = fluid_cranes_[it]->GetQueueSize();
                        best_option = it;
                    }
                }
                for (size_t it = 0; it < container_cranes_.size(); ++it) {
                    if (container_cranes_[it]->GetQueueSize() < smallest_queue) {
                        smallest_queue = container_cranes_[it]->GetQueueSize();
                        best_option = it;
                        fluid = false;
                    }
                }
                if (fluid) {
                    fluid_cranes_[best_option]->AddToQueue(ship);
                } else {
                    container_cranes_[best_option]->AddToQueue(ship);
                }
                ship->Show();
                break;
            }
        }
    }
}

void Model::UpdateUnloads() {
    std::string* message;
    std::vector<Crane*> cranes(0);
    for (auto crane : bulk_cranes_) cranes.push_back(crane);
    for (auto crane : fluid_cranes_) cranes.push_back(crane);
    for (auto crane : container_cranes_) cranes.push_back(crane);

    for (auto crane : cranes) {
        if (!crane->isEmpty()) {
            int hours_of_work = step_size_;
            Ship* ship = crane->GetFirstShip();
            while (hours_of_work > 0) {
                if (crane->isEmpty()) break;
                if (crane->GetUnloadTime() == -INT_MAX + 1) {
                    ship = crane->GetFirstShip();
                    crane->GetUnloadTime() = ((ship->get_weight() / (crane->GetSpeed() * 5)) + 59) / 60;
                    if (rand() % 2) {
                        int postpone_number = rand() % (unload_rejection_limits_.second -
                            unload_rejection_limits_.first + 1) + unload_rejection_limits_.first;
                        crane->GetUnloadTime() += postpone_number;
                        message = new std::string;
                        *message = crane->GetName() + " postpones the unloading by " + std::to_string(postpone_number);
                        log.push_back(message);
                        std::cout << *message << "\n";
                    }
                    if (hours_of_work > crane->GetUnloadTime()) UpdateShipsPos();
                }
                if (crane->GetUnloadTime() <= 0) {
                    crane->UnloadFirst();
                    message = new std::string;
                    *message = ship->get_ship_name() + " is unloaded";
                    log.push_back(message);
                    std::cout << *message << "\n";
                    crane->GetUnloadTime() = -INT_MAX + 1;
                } else {
                    int curr_min = std::min(crane->GetUnloadTime(), (double)hours_of_work);
                    crane->GetUnloadTime() -= curr_min;
                    hours_of_work -= curr_min;
                }
            }
            if (!crane->isEmpty() && crane->GetUnloadTime() <= 0) {
                crane->UnloadFirst();
                message = new std::string;
                *message = ship->get_ship_name() + " is unloaded";
                log.push_back(message);
                std::cout << *message << "\n";
                crane->GetUnloadTime() = -INT_MAX + 1;
            }
        }
    }
}

void Model::UpdateShipsPos() {
    for (auto ship : ships_) {
        ship->SetPos(ship->GetEndPos().first, ship->GetEndPos().second);
    }
}

void Model::DisplayTime(sf::RenderWindow*& window) {
    sf::Text time;
    time.setFont(font_);
    time.setCharacterSize(30);
    time.setFillColor(sf::Color::White);
    time.setString("day " + std::to_string(day_) + " time " + std::to_string(hour_) + " : 00");
    time.setPosition(window->getSize().x - time.getLocalBounds().width - 15, 10);
    window->draw(time);
}

void Model::DisplayShips(sf::RenderWindow*& window) {

}

void Model::DisplayCranes(sf::RenderWindow*& window) {

}
