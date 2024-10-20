#pragma once
#include "window.h"
#include "settings.h"

class Simulation : public Window {
 public:
     Simulation();
     Simulation(Settings*);
     virtual void CheckEvents() override;
     virtual void Draw() override;
     virtual bool isOpen() override;
     virtual ~Simulation();
     Model* GetModel();
 private:
     Model* model_;
     CursorHoverWindow* chw_;
};
