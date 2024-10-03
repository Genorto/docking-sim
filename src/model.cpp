#include "../includes/model.h"

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
    if (step_ > 30) throw std::runtime_error("The month is over");
    ++step_;
}

void Model::PreviousStep() {
    if (step_ < 1) throw std::runtime_error("It is the beginning of the month");
    --step_;
}

int Model::GetStep() {
    return step_;
}
