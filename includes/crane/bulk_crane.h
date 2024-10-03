#pragma once
#include "crane.h"

class BulkCrane : public Crane {
public:
    BulkCrane() : Crane() {}
    BulkCrane(const BulkCrane& other) : Crane(other) {}
    virtual void AddToQueue(Ship*& target) override;
    virtual std::vector<std::string*> GetInfo() override;
};
