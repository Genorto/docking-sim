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
    ++res_ships_cnt_;
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

int Model::GetStepSize() {
    return step_size_;
}

void Model::SetTimeLimits(std::pair<int, int> lim) {
    time_limits_ = lim;
}

void Model::SetTimeLimits(int lim_l, int lim_r) {
    time_limits_ = { lim_l, lim_r };
}

std::pair<int, int> Model::GetTimeLimits() {
    return time_limits_;
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

void Model::NextHour() {
    int temp_day = day_, temp_hour = hour_;
    ++temp_hour;
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
    for (auto crane : bulk_cranes_) {
        if (crane->GetQueueSize() > 0) {
            res_total_queues_length_ += crane->GetQueueSize();
            ++res_queues_cnt_;
        }
    }
    for (auto crane : fluid_cranes_) {
        if (crane->GetQueueSize() > 0) {
            res_total_queues_length_ += crane->GetQueueSize();
            ++res_queues_cnt_;
        }
    }
    for (auto crane : container_cranes_) {
        if (crane->GetQueueSize() > 0) {
            res_total_queues_length_ += crane->GetQueueSize();
            ++res_queues_cnt_;
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
            Ship* ship = crane->GetFirstShip();
            if (crane->GetUnloadTime() == -INT_MAX + 1) {
                crane->GetUnloadTime() = ((ship->get_weight() / (crane->GetSpeed() * 5)) + 59) / 60;
                if (rand() % 2) {
                    int postpone_number = rand() % ((unload_rejection_limits_.second -
                        unload_rejection_limits_.first + 1) + unload_rejection_limits_.first);

                    /* for results */
                    res_total_unload_rejection_time_ += postpone_number;
                    res_max_unload_rejection_time_ = std::max(res_max_unload_rejection_time_, postpone_number);
                    /* for results */

                    crane->GetUnloadTime() += postpone_number;
                    message = new std::string;
                    *message = crane->GetName() + " postpones the unloading by " + std::to_string(postpone_number);
                    log.push_back(message);
                    std::cout << *message << "\n";
                }
            }
            if (!crane->GetUnloadTime()) {
                crane->UnloadFirst();

                /* for results */
                std::pair<int, int> cur_tm = { day_, hour_ };
                std::pair<int, int> arr_tm = ship->get_arrival_time();
                int waiting_time = (cur_tm.first * 24 + cur_tm.second - arr_tm.first * 24 - arr_tm.second);
                res_total_fine_ = fine_ * waiting_time;
                res_total_waiting_time_ += waiting_time;
                /* for results */

                message = new std::string;
                *message = ship->get_ship_name() + " is unloaded";
                log.push_back(message);
                std::cout << *message << "\n";
                crane->GetUnloadTime() = -INT_MAX + 1;
            } else {
                --crane->GetUnloadTime();
            }
        }
    }
}

void Model::UpdateShipsPos() {
    for (auto ship : ships_) {
        ship->SetPos(ship->GetEndPos().first, ship->GetEndPos().second);
    }
}

int Model::GetShipsCount() {
    return ships_.size();
}

double Model::GetAverageQueueLength() {
    if (!res_queues_cnt_) return 0;
    return res_total_queues_length_ / res_queues_cnt_;
}

double Model::GetAverageWaitingTime() {
    if (!GetShipsCount()) return 0;
    return res_total_waiting_time_ / GetShipsCount();
}

int Model::GetMaxUnloadRejectionTime() {
    return res_max_unload_rejection_time_;
}

double Model::GetAverageUnloadRejectionTime() {
    if (!GetShipsCount()) return 0;
    return res_total_unload_rejection_time_ / GetShipsCount();
}

int Model::GetTotalFine() {
    return res_total_fine_;
}
