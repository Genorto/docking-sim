#pragma once
#include "window.h"
#include "settings.h"

class Simulation : public Window {
 public:
     Simulation();
     Simulation(Settings*);
     virtual ~Simulation();
     virtual void CheckEvents() override;
     virtual void Draw() override;
     virtual bool isOpen() override;
     Model* GetModel();

 private:
     Model* model_;
     CursorHoverWindow* chw_;
     sf::View view;
     sf::Vector2f oldPos;
     const sf::Vector2f default_center = sf::Vector2f(750, 400);
     bool moving = false, working = true;
     int news_l, news_r;
};
