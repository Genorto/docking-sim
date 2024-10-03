#include "../includes/window/simulation.h"

int main() {
    Window* window = new Simulation;
    while (window->isOpen()) {
        window->CheckEvents();
        window->Draw();
    }
    delete window;
}
