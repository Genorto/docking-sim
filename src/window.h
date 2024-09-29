#pragma once
#include "SFML/Graphics.hpp"

class Window {
 public:
     virtual void Draw() = 0;
     virtual void CheckEvents() = 0;
     virtual bool isOpen() = 0;

 protected:
     sf::RenderWindow* window_;
     sf::Event* event_;
};
