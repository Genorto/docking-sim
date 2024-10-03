#pragma once
#include "crane.h"

class ContainerCrane : public Crane {
    virtual void AddToQueue(Ship*& target) override;
    virtual std::vector<std::string*> GetInfo() override;
};