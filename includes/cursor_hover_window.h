#pragma once
#include"SFML/Graphics.hpp"

class CursorHoverWindow final {
 public:
     CursorHoverWindow();
     CursorHoverWindow(const CursorHoverWindow& other);
     CursorHoverWindow& operator=(const CursorHoverWindow& other);
     void SetPos(double x, double y);
     void SetSize(double size_x, double size_y);
     void Draw(sf::RenderWindow*& window);

 private:
     double x_, y_;
     double size_x_, size_y_;
};