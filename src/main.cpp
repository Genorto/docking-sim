#include "../includes/window/settings.h"
#include "../includes/window/simulation.h"

int main() {
    Window* sett = new Settings;
    while (sett->isOpen()) {
        sett->Draw();
        sett->CheckEvents();
    }
    Window* window = new Simulation;
    delete sett;

    srand(time(0));
    while (window->isOpen()) {
        window->CheckEvents();
        window->Draw();
    }
    delete window;
}
