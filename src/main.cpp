#include "settings.h"
#include "gameplay.h"
#include "conclusion.h"

int main() {
    Window* window = new Settings;
    while (window->isOpen()) {
        window->CheckEvents();
        window->Draw();
    }
    delete window;
    return 0;
}
