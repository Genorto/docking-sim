#pragma once
#include "window.h"

class Conclusion : public Window {
 public:
     Conclusion();
     virtual void CheckEvents() override;
     virtual void Draw() override;
     virtual bool isOpen() override;
     virtual ~Conclusion();
};
