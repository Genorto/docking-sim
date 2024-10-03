#include "../../includes/crane/fluid_crane.h"

void FluidCrane::AddToQueue(Ship*& target) {
    if (!(target->get_type() == ShipType::Tanker))
        throw std::runtime_error("Fluid crane is incompatible with received ship");
    queue_.push(target);
}

std::vector<std::string*> FluidCrane::GetInfo() {
    std::vector<std::string*> info;
    info.push_back(new std::string("Fluid crane"));
    info.push_back(new std::string(name_));
    info.push_back(new std::string("Currently unloading:"));
    if (isEmpty()) info.push_back(new std::string("None"));
    else info.push_back(new std::string(queue_.front()->get_ship_name()));
    return info;
}
