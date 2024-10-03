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
    x_ = x + 20;
    y_ = y + 20;
}

void CursorHoverWindow::SetSize(double size_x, double size_y) {
    size_x_ = size_x;
    size_y_ = size_y;
}

void CursorHoverWindow::SetFont(std::string font_dir) {
    font_.loadFromFile(font_dir);
}

void CursorHoverWindow::SetInfo(std::vector<std::string*> info) {
    for (auto it_ : info_) {
        delete it_;
    }
    info_.assign(info.size(), nullptr);
    for (size_t it = 0; it < info.size(); ++it) {
        info_[it] = new std::string(*info[it]);
    }
}

void CursorHoverWindow::Draw(sf::RenderWindow*& window) {
    sf::RectangleShape chw;
    chw.setPosition(sf::Vector2f(x_, y_));
    chw.setFillColor(sf::Color(0, 0, 0, 155));
    sf::Text line;
    line.setFont(font_);
    line.setFillColor(sf::Color::White);
    line.setCharacterSize(size_y_ / info_.size());
    size_t max_size = 0;
    for (size_t it = 0; it < info_.size(); ++it) {
        if (info_[it]->size() > max_size) {
            max_size = info_[it]->size();
            line.setString(*info_[it]);
            size_x_ = line.getLocalBounds().width + 10;
        }
    }
    chw.setSize(sf::Vector2f(size_x_, size_y_));
    window->draw(chw);
    for (size_t it = 0; it < info_.size(); ++it) {
        line.setString(*info_[it]);    
        line.setPosition(sf::Vector2f(x_, y_ + size_y_ / info_.size() * it - 10));
        window->draw(line);
    }
}
