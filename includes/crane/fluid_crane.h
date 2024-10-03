#pragma once
#include "crane.h"

class FluidCrane : public Crane {
    virtual void AddToQueue(Ship*& target) override;
    virtual std::vector<std::string*> GetInfo() override;
};
