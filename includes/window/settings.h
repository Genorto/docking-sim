#pragma once
#include "window.h"

class Settings : public Window {
 public:
     Settings();
     virtual void CheckEvents() override;
     virtual void Draw() override;
     virtual bool isOpen() override;
     virtual ~Settings();
};
