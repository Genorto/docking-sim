#pragma once
#include "window.h"

class Gameplay : public Window {
 public:
     Gameplay();
     virtual void CheckEvents() override;
     virtual void Draw() override;
     virtual bool isOpen() override;
     virtual ~Gameplay();
};
