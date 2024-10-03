#include "../../includes/window/window.h"

Window::~Window() {
    delete window_;
    delete event_;
}