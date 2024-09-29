#pragma once
#include <SFML/Graphics.hpp>

class Window {
 public:
     virtual void CheckEvents() = 0;
     virtual void Draw() = 0;
     virtual bool isOpen() = 0;
     virtual ~Window();

 protected:
     sf::RenderWindow* window_;
     sf::Event* event_;
};
