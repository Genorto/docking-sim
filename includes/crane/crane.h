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
     bool isHovered(sf::Vector2i cursor_pos);
     bool isEmpty();
     void UnloadFirst();
     void Draw(sf::RenderWindow*& window);

     void SetPos(double x, double y);
     void SetSize(double size_x, double size_y);
     void SetModel(std::string path);
     void SetSpace(double space);
     void SetName(std::string name);

     size_t GetQueueSize();
     Ship* GetFirstShip();
     void SetSpeed(int);
     int GetSpeed();
     std::pair<double, double> GetPos();
     std::pair<double, double> GetSize();
     virtual std::vector<std::string*> GetInfo() = 0;
     std::string GetName();
     int& GetUnloadTime();

 protected:
     double x_ = 0, y_ = 0;
     double size_x_ = 0, size_y_ = 0;
     sf::Texture model_;
     std::queue<Ship*> queue_;
     std::string name_;
     int speed_; // in minutes per 5 kg
     double last_ship_pos_;
     double space_;
     int unload_time_ = -INT_MAX + 1;
};
