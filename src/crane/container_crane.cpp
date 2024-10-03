#include "../../includes/crane/container_crane.h"

void ContainerCrane::AddToQueue(Ship*& target) {
    if (!(target->get_type() == ShipType::Tanker))
        throw std::runtime_error("Container crane is incompatible with received ship");
    queue_.push(target);
}

std::vector<std::string*> ContainerCrane::GetInfo() {
    std::vector<std::string*> info;
    info.push_back(new std::string("Container crane"));
    info.push_back(new std::string(name_));
    info.push_back(new std::string("Currently unloading:"));
    if (isEmpty()) info.push_back(new std::string("None"));
    else info.push_back(new std::string(queue_.front()->get_ship_name()));
    return info;
}
