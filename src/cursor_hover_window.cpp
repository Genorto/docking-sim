#include "../includes/cursor_hover_window.h"

CursorHoverWindow::CursorHoverWindow() {

}

CursorHoverWindow::CursorHoverWindow(const CursorHoverWindow& other) {
    x_ = other.x_;
    y_ = other.y_;
    size_x_ = other.size_x_;
    size_y_ = other.size_y_;
}

CursorHoverWindow& CursorHoverWindow::operator=(const CursorHoverWindow& other) {
    x_ = other.x_;
    y_ = other.y_;
    size_x_ = other.size_x_;
    size_y_ = other.size_y_;
    return *this;
}

void CursorHoverWindow::SetPos(double x, double y) {
    x_ = x;
    y_ = y;
}

void CursorHoverWindow::SetSize(double size_x, double size_y) {
    size_x_ = size_x;
    size_y_ = size_y;
}

void CursorHoverWindow::Draw(sf::RenderWindow*& window) {
    sf::RectangleShape chw;
    chw.setPosition(sf::Vector2f(x_, y_));
    chw.setSize(sf::Vector2f(size_x_, size_y_));
}
