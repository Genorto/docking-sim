#include "../../includes/crane/crane.h"

Crane::Crane() {
    x_ = 0;
    y_ = 0;
    size_x_ = 0;
    size_y_ = 0;
    model_.loadFromFile("assets/sprites/error.png");
    name_ = "John Doe";
    speed_ = 1;
    last_ship_pos_ = 25;
    unload_time_ = -INT_MAX + 1;
}

Crane::Crane(const Crane& other) {
    x_ = other.x_;
    y_ = other.y_;
    size_x_ = other.size_x_;
    size_y_ = other.size_y_;
    model_ = other.model_;
    name_ = other.name_;
    speed_ = other.speed_;
    last_ship_pos_ = other.last_ship_pos_;
    unload_time_ = other.unload_time_;
}

Crane& Crane::operator=(const Crane& other) {
    x_ = other.x_;
    y_ = other.y_;
    size_x_ = other.size_x_;
    size_y_ = other.size_y_;
    model_ = other.model_;
    name_ = other.name_;
    speed_ = other.speed_;
    last_ship_pos_ = other.last_ship_pos_;
    other.unload_time_;
    return *this;
}

size_t Crane::GetQueueSize() {
    return queue_.size();
}

bool Crane::isHovered(sf::Vector2i cursor_pos) {
    return (cursor_pos.x >= x_ && cursor_pos.x <= x_ + size_x_) && (cursor_pos.y >= y_ && cursor_pos.y <= y_ + size_y_);
}

bool Crane::isEmpty() {
    return queue_.empty();
}

Ship* Crane::GetFirstShip() {
    if (isEmpty()) throw std::runtime_error("Ship* GetFirstShip();");
    return queue_.front();
}

void Crane::UnloadFirst() {
    if (isEmpty()) throw std::runtime_error("Queue is empty");
    Ship* ship = queue_.front();
    ship->set_weight(0);
    ship->SetStartPos(ship->GetPos().first, ship->GetPos().second);
    ship->SetEndPos(ship->GetPos().first, ship->GetPos().second - 200);
    double offset = ship->GetSize().second + space_;
    queue_.pop();
    last_ship_pos_ -= offset;
    std::queue<Ship*> all_ships = queue_;
    while (!all_ships.empty()) {
        ship = all_ships.front();
        ship->SetStartPos(ship->GetPos().first, ship->GetPos().second);
        ship->SetEndPos(ship->GetPos().first, ship->GetPos().second - offset);
        all_ships.pop();
    }
}

void Crane::SetSpeed(int speed) {
    speed_ = speed;
}

int Crane::GetSpeed() {
    return speed_;
}

void Crane::SetPos(double x, double y) {
    x_ = x;
    y_ = y;
}

void Crane::SetSize(double size_x, double size_y) {
    size_x_ = size_x;
    size_y_ = size_y;
}

void Crane::SetModel(std::string path) {
    if (!model_.loadFromFile(path)) model_.loadFromFile("assets/sprites/error.png");
}

void Crane::SetName(std::string name) {
    name_ = name;
}

std::string Crane::GetName() {
    return name_;
}

void Crane::SetSpace(double space) {
    space_ = space;
}

double& Crane::GetUnloadTime() {
    return unload_time_;
}

void Crane::Draw(sf::RenderWindow*& window) {
    sf::Sprite crane(model_);
    crane.setPosition(sf::Vector2f(x_, y_));
    crane.setScale(size_x_ / model_.getSize().x, size_y_ / model_.getSize().y);
    window->draw(crane);
}
