#pragma once
#include "crane.h"

class FluidCrane : public Crane {
    virtual void Unload(/* Ship*& target */) override;
};
