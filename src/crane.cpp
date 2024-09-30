#include "crane.h"

void Crane::SetPos(double x, double y) {
    x_ = x;
    y_ = y;
}

void Crane::SetSize(double size_x, double size_y) {
    size_x_ = size_x;
    size_y_ = size_y;
}

void Crane::SetModel(std::string path) {
    if (!model_.loadFromFile(path)) model_.loadFromFile("src/assets/sprites/error.png");
}

void Crane::Draw(sf::RenderWindow*& window) {
    sf::Sprite crane(model_);
    crane.setPosition(sf::Vector2f(x_, y_));
    window->draw(crane);
}
