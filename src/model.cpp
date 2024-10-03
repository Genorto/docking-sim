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

void Model::NextStep() {
    if (day_ > 30) throw std::runtime_error("The month is over");
    ++day_;
    SortNewShips();
}

void Model::PreviousStep() {
    if (day_ < 1) throw std::runtime_error("It is the beginning of the month");
    --day_;
}

std::pair<int, int> Model::GetTime() {
    return { day_, hour_ };
}

void Model::SortNewShips() {
    std::cout << day_ << " : " << hour_ << "\n";
    for (auto crane : bulk_cranes_) {
        if (crane->GetQueueSize()) crane->UnloadFirst();
    }
    for (auto crane : fluid_cranes_) {
        if (crane->GetQueueSize()) crane->UnloadFirst();
    }
    for (auto crane : container_cranes_) {
        if (crane->GetQueueSize()) crane->UnloadFirst();
    }
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