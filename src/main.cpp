#include "settings.h"

int main() {
    Window* window = new Settings;
    while (window->isOpen()) {
        window->CheckEvents();
        window->Draw();
    }
    return 0;
}
