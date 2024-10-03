#pragma once
#include "SFML/Graphics.hpp"
#include "../ship/cargo_ship.h"
#include "../ship/tanker.h"
#include "exception"
#include "queue"

class Crane {
 public:
     Crane();
     Crane(const Crane& other);
     Crane& operator=(const Crane& other);
     virtual void AddToQueue(Ship*& target) = 0;
     bool isEmpty();
     void UnloadFirst();
     virtual void SetPos(double x, double y) final;
     virtual void SetSize(double size_x, double size_y) final;
     virtual void SetModel(std::string path) final;
     virtual void Draw(sf::RenderWindow*& window) final;

 protected:
     double x_ = 0, y_ = 0;
     double size_x_ = 0, size_y_ = 0;
     sf::Texture model_;
     std::queue<Ship*> queue_;
};
