#pragma once
#include "SFML/Graphics.hpp"
#include "exception"

class Crane {
 public:
     virtual void Unload(/* Ship*& target */) = 0;
     virtual void SetPos(double x, double y) final;
     virtual void SetSize(double size_x, double size_y) final;
     virtual void SetModel(std::string path) final;
     virtual void Draw(sf::RenderWindow*& window) final;

 protected:
     double x_ = 0, y_ = 0;
     double size_x_ = 0, size_y_ = 0;
     sf::Texture model_;
};
