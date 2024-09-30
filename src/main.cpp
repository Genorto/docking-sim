#include "settings.h"
#include "simulation.h"
#include "conclusion.h"

int main() {
    Window* window = new Simulation;
    while (window->isOpen()) {
        window->CheckEvents();
        window->Draw();
    }
    delete window;
}
