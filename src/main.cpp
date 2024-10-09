#include "../includes/window/settings.h"
#include "../includes/window/simulation.h"

int main() {
    Settings* sett = new Settings;
    while (sett->isOpen()) {
        sett->Draw();
        sett->CheckEvents();
    }
    Window* window = new Simulation(sett);
    delete sett;
    srand(time(0));
    while (window->isOpen()) {
        window->CheckEvents();
        window->Draw();
    }
    delete window;
}
