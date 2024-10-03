#include "../../includes/crane/container_crane.h"

void ContainerCrane::AddToQueue(Ship*& target) {
    if (!(target->get_type() == ShipType::Tanker))
        throw std::runtime_error("Container crane is incompatible with received ship");
    queue_.push(target);
}

std::vector<std::string*> ContainerCrane::GetInfo() {
    std::string* line1 = new std::string("I am container crane");
    std::vector<std::string*> info;
    info.push_back(line1);
    return info;
}
