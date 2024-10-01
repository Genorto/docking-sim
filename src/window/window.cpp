#include "window.h"

Window::~Window() {
    delete window_;
    delete event_;
}