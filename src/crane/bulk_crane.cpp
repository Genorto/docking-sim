#include "bulk_crane.h"

void BulkCrane::AddToQueue(Ship*& target) {
    if (!(target->get_type() == ShipType::CargoShip))
        throw std::runtime_error("Bulk crane is incompatible with received ship");
    queue_.push(target);
}
