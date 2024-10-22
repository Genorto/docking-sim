#include "../../includes/crane/bulk_crane.h"

void BulkCrane::AddToQueue(Ship*& target) {
    if (!(target->get_type() == ShipType::CargoShip))
        throw std::runtime_error("Bulk crane is incompatible with received ship");
    // kaka
    if (isEmpty()) {
        target->Unload();
        target->SetStartPos(x_ + size_x_, last_ship_pos_ + 200);
        target->SetEndPos(x_ + size_x_ / 2 - target->GetSize().first / 2, last_ship_pos_);
    } else {
        target->FadeIn();
        target->SetStartPos(x_ + size_x_, last_ship_pos_ + 200);
        target->SetEndPos(x_ + size_x_, last_ship_pos_);
    }
    queue_.push(target);
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

