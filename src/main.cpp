#include "window/settings.h"
#include "window/simulation.h"
#include "window/conclusion.h"

int main() {
    Window* window = new Simulation;
    while (window->isOpen()) {
        window->CheckEvents();
        window->Draw();
    }
    delete window;
}
