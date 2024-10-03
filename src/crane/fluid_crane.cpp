#include "../../includes/crane/fluid_crane.h"

void FluidCrane::AddToQueue(Ship*& target) {
    if (!(target->get_type() == ShipType::Tanker))
        throw std::runtime_error("Fluid crane is incompatible with received ship");
    queue_.push(target);
}

std::vector<std::string*> FluidCrane::GetInfo() {
    std::string* line1 = new std::string("I am fluid crane");
    std::vector<std::string*> info;
    info.push_back(line1);
    return info;
}
