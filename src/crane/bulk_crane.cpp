#include "../../includes/crane/bulk_crane.h"

void BulkCrane::AddToQueue(Ship*& target) {
    if (!(target->get_type() == ShipType::CargoShip))
        throw std::runtime_error("Bulk crane is incompatible with received ship");
    queue_.push(target);
}

std::vector<std::string*> BulkCrane::GetInfo() {
    std::string* line1 = new std::string("I am bulk crane");
    std::vector<std::string*> info;
    info.push_back(line1);
    return info;
}

