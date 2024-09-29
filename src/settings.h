#pragma once
#include "window.h"

class Settings : public Window {
 public:
     Settings();
     virtual void Draw() override;
     virtual void CheckEvents() override;
     virtual bool isOpen() override;

 private:
     
};
