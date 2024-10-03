#include "../../includes/crane/crane.h"

Crane::Crane() {
    x_ = 0;
    y_ = 0;
    size_x_ = 0;
    size_y_ = 0;
    model_.loadFromFile("assets/sprites/error.png");
    name_ = "John Doe";
}

Crane::Crane(const Crane& other) {
    x_ = other.x_;
    y_ = other.y_;
    size_x_ = other.size_x_;
    size_y_ = other.size_y_;
    model_ = other.model_;
    queue_ = other.queue_;
    name_ = other.name_;
}

Crane& Crane::operator=(const Crane& other) {
    x_ = other.x_;
    y_ = other.y_;
    size_x_ = other.size_x_;
    size_y_ = other.size_y_;
    model_ = other.model_;
    queue_ = other.queue_;
    name_ = other.name_;
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

void Crane::UnloadFirst() {
    if (isEmpty()) throw std::runtime_error("Queue is empty");
    queue_.front()->set_weight(0);
    queue_.pop();
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

void Crane::Draw(sf::RenderWindow*& window) {
    sf::Sprite crane(model_);
    crane.setPosition(sf::Vector2f(x_, y_));
    crane.setScale(size_x_ / model_.getSize().x, size_y_ / model_.getSize().y);
    window->draw(crane);
}
