#pragma once
#include "crane.h"

class ContainerCrane : public Crane {
    virtual void Unload(/* Ship*& target */) override;
};