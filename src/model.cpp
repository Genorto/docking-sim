#include "../includes/model.h"
#include "iostream"

void Model::CreateCranes(size_t bulk_cnt, size_t fluid_cnt, size_t container_cnt) {
    bulk_cranes_.assign(bulk_cnt, new BulkCrane);
    fluid_cranes_.assign(fluid_cnt, new FluidCrane);
    container_cranes_.assign(container_cnt, new ContainerCrane);
}

void Model::CreateShips(size_t cargo_cnt, size_t tanker_cnt) {
    cargo_ships_.assign(cargo_cnt, new CargoShip);
    tankers_.assign(tanker_cnt, new Tanker);
}

void Model::RandomizeShipsData() {
    for (auto ship : cargo_ships_) {
        ship->set_arrival_rejection(rand() % (rejection_limits_.second - 
            rejection_limits_.first + 1) + rejection_limits_.first);
    }
    for (auto ship : tankers_) {
        ship->set_arrival_rejection(rand() % (rejection_limits_.second -
            rejection_limits_.first + 1) + rejection_limits_.first);
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

void Model::AddCargoShip(Ship*& ship) {
    cargo_ships_.push_back(ship);
}

void Model::AddTanker(Ship*& ship) {
    tankers_.push_back(ship);
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

std::vector<Ship*> Model::GetCargoShips() {
    return cargo_ships_;
}

std::vector<Ship*> Model::GetTankers() {
    return tankers_;
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

void Model::SetFineLimits(std::pair<int, int> lim) {
    fine_limits_ = lim;
}

void Model::SetFineLimits(int lim_l, int lim_r) {
    fine_limits_ = { lim_l, lim_r };
}

void Model::SetSpeedLimits(std::pair<int, int> lim) {
    fine_limits_ = lim;
}

void Model::SetSpeedLimits(int lim_l, int lim_r) {
    fine_limits_ = { lim_l, lim_r };
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

void Model::PreviousStep() {
    int temp_day = day_, temp_hour = hour_;
    temp_hour -= step_size_;
    if (temp_hour < 0) {
        temp_day -= (abs(temp_hour) + 23) / 24;
        temp_hour = 24 + temp_hour % 24;
    }
    if (temp_day < 0) return;
    day_ = temp_day;
    hour_ = temp_hour;
}

std::pair<int, int> Model::GetTime() {
    return { day_, hour_ };
}

void Model::UpdateRejections() {
    std::string* message;
    std::pair<int, int> cur_tm = { day_, hour_ };
    for (auto ship : cargo_ships_) {
        if (ship->get_arrival_time() == cur_tm) {
            int day = ship->get_arrival_time().first;
            int hour = ship->get_arrival_time().second + ship->get_arrival_rejection();
            day += hour / 24;
            hour %= 24;
            message = new std::string;
            *message = ship->get_ship_name() + "'s arrival is postponed to " + std::to_string(day) + " : " + std::to_string(hour);
            log.push_back(message);
            std::cout << *message << "\n";
        }
    }
    for (auto ship : tankers_) {
        if (ship->get_arrival_time() == cur_tm) {
            int day = ship->get_arrival_time().first;
            int hour = ship->get_arrival_time().second + ship->get_arrival_rejection();
            day += hour / 24;
            hour %= 24;
            message = new std::string;
            *message = ship->get_ship_name() + "'s arrival is postponed to " + std::to_string(day) + " : " + std::to_string(hour);
            log.push_back(message);
            std::cout << *message << "\n";
        }
    }
 }

void Model::UpdateQueues() {
    std::pair<int, int> cur_tm = { day_, hour_ };
    /* cargo ships */
    for (auto ship : cargo_ships_) {
        std::pair<int, int> arr_tm = ship->get_arrival_time();
        int rej_tm = ship->get_arrival_rejection();
        ShipType type = ship->get_type();
        if (cur_tm == arr_tm) {
            size_t smallest_queue = INT_MAX, best_option = 0;
            switch (type) {
                case ShipType::CargoShip:
                    for (size_t it = 0; it < bulk_cranes_.size(); ++it) {
                        if (bulk_cranes_[it]->GetQueueSize() < smallest_queue) {
                            smallest_queue = bulk_cranes_[it]->GetQueueSize();
                            best_option = it;
                        }
                    }
                    bulk_cranes_[best_option]->AddToQueue(ship);
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
                    break;
            }
        }
    }
    /* tankers */
    for (auto ship : tankers_) {
        std::pair<int, int> arr_tm = ship->get_arrival_time();
        ShipType type = ship->get_type();
        if (cur_tm == arr_tm) {
            size_t smallest_queue = INT_MAX, best_option = 0;
            switch (type) {
            case ShipType::CargoShip:
                for (size_t it = 0; it < bulk_cranes_.size(); ++it) {
                    if (bulk_cranes_[it]->GetQueueSize() < smallest_queue) {
                        smallest_queue = bulk_cranes_[it]->GetQueueSize();
                        best_option = it;
                    }
                }
                bulk_cranes_[best_option]->AddToQueue(ship);
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
                break;
            }
        }
    }
}

void Model::DisplayTime(sf::RenderWindow*& window) {
    sf::Text time;
    time.setFont(font_);
    time.setCharacterSize(30);
    time.setFillColor(sf::Color::White);
    time.setString(std::to_string(day_) + " : " + std::to_string(hour_));
    time.setPosition(window->getSize().x - time.getLocalBounds().width - 15, 10);
    window->draw(time);
}

void Model::DisplayShips(sf::RenderWindow*& window) {

}

void Model::DisplayCranes(sf::RenderWindow*& window) {

}
