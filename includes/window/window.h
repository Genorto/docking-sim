#pragma once
#include <SFML/Graphics.hpp>
#include "../ship/cargo_ship.h"
#include "../ship/tanker.h"
#include "../crane/bulk_crane.h"
#include "../cursor_hover_window.h"

class Window {
 public:
     virtual void CheckEvents() = 0;
     virtual void Draw() = 0;
     virtual bool isOpen() = 0;
     virtual ~Window();

 protected:
     sf::RenderWindow* window_ = nullptr;
     sf::Event* event_ = nullptr;
};
