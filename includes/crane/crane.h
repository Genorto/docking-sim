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
     size_t GetQueueSize();
     virtual bool isHovered(sf::Vector2i cursor_pos) final;
     virtual std::vector<std::string*> GetInfo() = 0;
     bool isEmpty();
     Ship* GetFirstShip();
     void UnloadFirst();
     void SetSpeed(int);
     int GetSpeed();
     std::pair<double, double> GetPos();
     std::pair<double, double> GetSize();
     virtual void SetPos(double x, double y) final;
     virtual void SetSize(double size_x, double size_y) final;
     virtual void SetModel(std::string path) final;
     virtual void SetName(std::string name) final;
     virtual std::string GetName() final;
     virtual void SetSpace(double space) final;
     virtual int& GetUnloadTime() final;
     virtual void Draw(sf::RenderWindow*& window) final;

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
