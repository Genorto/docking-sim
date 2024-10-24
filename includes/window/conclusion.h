#pragma once
#include "window.h"
#include "simulation.h"

class Conclusion : public Window {
 public:
     Conclusion();
     Conclusion(Simulation* simulation);
     virtual ~Conclusion();
     virtual void CheckEvents() override;
     virtual void Draw() override;
     virtual bool isOpen() override;

private:
    int res_ships_cnt_ = 0;
    double average_queue_length_ = 0;
    double average_waiting_time_ = 0;
    int get_max_unload_time_ = 0;
    double get_average_unload_time_ = 0;
    int total_fine_ = 0;
    sf::Image background_image_;
    sf::Texture background_texture_;
    sf::Sprite background_sprite_;
    std::vector<sf::String> text_vector_;
    sf::RectangleShape background_text_;
    sf::Text text_, text_answer_;
    sf::Font font_;
};
