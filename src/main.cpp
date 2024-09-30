#include "settings.h"
#include "simulation.h"
#include "conclusion.h"

int main() {
    Window* window = new Settings;
    while (window->isOpen()) {
        window->CheckEvents();
        window->Draw();
    }
    delete window;
}
