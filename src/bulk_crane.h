#pragma once
#include "crane.h"

class BulkCrane : public Crane {
    virtual void Unload(/* Ship*& target */) override;
};
