#pragma once
#include "crane.h"

class ContainerCrane : public Crane {
public:
    ContainerCrane() : Crane() {}
    ContainerCrane(const ContainerCrane& other) : Crane(other) {}
    virtual void AddToQueue(Ship*& target) override;
    virtual std::vector<std::string*> GetInfo() override;
};