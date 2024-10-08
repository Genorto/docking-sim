#include "../includes/window/simulation.h"

int main() {
    srand(time(0));
    Window* window = new Simulation;
    while (window->isOpen()) {
        window->CheckEvents();
        window->Draw();
    }
    delete window;
}
