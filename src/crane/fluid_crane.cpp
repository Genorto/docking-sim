#include "../../includes/crane/fluid_crane.h"

void FluidCrane::AddToQueue(Ship*& target) {
    if (!(target->get_type() == ShipType::Tanker))
        throw std::runtime_error("Fluid crane is incompatible with received ship");
    queue_.push(target);
}
