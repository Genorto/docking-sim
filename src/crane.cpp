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
    try {
        model_.loadFromFile("src/assets/sprites/default_crane.png");
    }
    catch (...) {
        model_.loadFromFile("src/assets/sprites/error.png");
    }
}

void Crane::Draw(sf::RenderWindow*& window) {
    sf::RectangleShape crane;
    crane.setPosition(sf::Vector2f(x_, y_));
    crane.setSize(sf::Vector2f(size_x_, size_y_));
    window->draw(crane);
}
