#pragma once
#include "window.h"

class Simulation : public Window {
 public:
     Simulation();
     virtual void CheckEvents() override;
     virtual void Draw() override;
     virtual bool isOpen() override;
     virtual ~Simulation();

 private:
     std::vector<Crane*> cranes_;
     std::vector<Ship*> ships_;
     CursorHoverWindow* chw_;
};
