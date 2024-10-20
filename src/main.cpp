#include "../includes/window/settings.h"
#include "../includes/window/simulation.h"
#include "../includes/window/conclusion.h"

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
    Window* conclusion = new Conclusion(static_cast<Simulation*>(window));
    delete window;
    while (conclusion->isOpen()) {
        conclusion->CheckEvents();
        conclusion->Draw();
    }
}
