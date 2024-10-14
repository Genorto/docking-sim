#include "../../includes/crane/bulk_crane.h"

void BulkCrane::AddToQueue(Ship*& target) {
    if (!(target->get_type() == ShipType::CargoShip))
        throw std::runtime_error("Bulk crane is incompatible with received ship");
    queue_.push(target);
    target->SetStartPos(x_ + 45, last_ship_pos_ + 200);
    target->SetEndPos(x_ + 45, last_ship_pos_);
    target->FadeIn();
    last_ship_pos_ += target->GetSize().second + space_;
}

std::vector<std::string*> BulkCrane::GetInfo() {
    std::vector<std::string*> info;
    info.push_back(new std::string("Bulk crane"));
    info.push_back(new std::string(name_));
    info.push_back(new std::string("Currently unloading:"));
    if (isEmpty()) info.push_back(new std::string("None"));
    else info.push_back(new std::string(queue_.front()->get_ship_name()));
    return info;
}

