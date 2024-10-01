#include "container_crane.h"

void ContainerCrane::AddToQueue(Ship*& target) {
    if (!(target->get_type() == ShipType::Tanker))
        throw std::runtime_error("Container crane is incompatible with received ship");
    queue_.push(target);
}
