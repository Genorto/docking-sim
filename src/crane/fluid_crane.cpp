#include "../../includes/crane/fluid_crane.h"

void FluidCrane::AddToQueue(Ship*& target) {
    if (!(target->GetType() == ShipType::Tanker))
        throw std::runtime_error("Fluid crane is incompatible with received ship");
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

std::vector<std::string*> FluidCrane::GetInfo() {
    std::vector<std::string*> info;
    info.push_back(new std::string("Fluid crane"));
    info.push_back(new std::string(name_));
    info.push_back(new std::string("Speed: "));
    info.push_back(new std::string(std::to_string(speed_) + " min per 5 kg"));
    info.push_back(new std::string("Currently unloading:"));
    if (isEmpty()) info.push_back(new std::string("None"));
    else info.push_back(new std::string(queue_.front()->GetName()));
    return info;
}
