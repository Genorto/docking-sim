#pragma once
#include "window.h"

class Simulation : public Window {
 public:
     Simulation();
     virtual void CheckEvents() override;
     virtual void Draw() override;
     virtual bool isOpen() override;
     virtual ~Simulation();
};
