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

void Model::SetTimeLimits(std::pair<std::pair<int, int>, std::pair<int, int>> lim) {
    time_limits_ = lim;
}

void Model::SetTimeLimits(std::pair<int, int> lim_l, std::pair<int, int> lim_r) {
    time_limits_ = { lim_l, lim_r };
}

void Model::SetTimeLimits(int lim_l_l, int lim_l_r, int lim_r_l, int lim_r_r) {
    time_limits_ = { { lim_l_l, lim_l_r }, { lim_r_l, lim_r_r } };
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

void Model::NextStep() {
    hour_ += step_size_;
    day_ += hour_ / 24;
    hour_ %= 24;
    if (day_ == time_limits_.second.first && hour_ > time_limits_.second.second
        || day_ > time_limits_.second.first) throw std::runtime_error("Time limit reached");
}

void Model::PreviousStep() {
    if (day_ < 1) throw std::runtime_error("It is the beginning of the month");
    --hour_;
}

std::pair<int, int> Model::GetTime() {
    return { day_, hour_ };
}

void Model::SortNewShips() {
    std::cout << day_ << " : " << hour_ << "\n";
    std::pair<int, int> cur_tm = { day_, hour_ };
    /* cargo ships */
    for (auto ship : cargo_ships_) {
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