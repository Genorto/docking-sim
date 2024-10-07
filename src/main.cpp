#include "../includes/window/simulation.h"

#include "../includes/window/settings.h"
int main() {
    Settings* sett = new Settings;
    while (sett->isOpen()) {
        sett->Draw();
        sett->CheckEvents();
    }
    delete sett;
    /*Window* window = new Simulation;
    while (window->isOpen()) {
        window->CheckEvents();
        window->Draw();
    }
    delete window;*/
}
