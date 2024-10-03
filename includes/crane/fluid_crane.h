#pragma once
#include "crane.h"

class FluidCrane : public Crane {
public:
    FluidCrane() : Crane() {}
    FluidCrane(const FluidCrane& other) : Crane(other) {}
    virtual void AddToQueue(Ship*& target) override;
    virtual std::vector<std::string*> GetInfo() override;
};
