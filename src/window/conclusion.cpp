#include "../../includes/window/conclusion.h"

Conclusion::Conclusion() {
    window_ = new sf::RenderWindow(sf::VideoMode(500, 800), "Conclusion");
    event_ = new sf::Event;
    /* implement objects */
}

void Conclusion::CheckEvents() {
    while (window_->pollEvent(*event_)) {
        switch (event_->type) {
        case sf::Event::Closed:
            window_->close();
            break;
        }
    }
}

void Conclusion::Draw() {
    window_->clear();
    /* draw objects */
    window_->display();
}

bool Conclusion::isOpen() {
    return window_->isOpen();
}

Conclusion::~Conclusion() {}
