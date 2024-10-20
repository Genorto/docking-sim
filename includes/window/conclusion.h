#pragma once
#include "simulation.h"


class Conclusion : public Window {
 public:
     Conclusion(Simulation* simulation);
     Conclusion();
     virtual void CheckEvents() override;
     virtual void Draw() override;
     virtual bool isOpen() override;
     virtual ~Conclusion();

     sf::Image background_image; 
     sf::Texture background_texture;
     sf::Sprite background_sprite;
     std::vector<sf::String> text;

     sf::RectangleShape background_text_;
     sf::Text text_, text_answer_;

     sf::Font font;

private:
    int res_ships_cnt_ = 0;
    double average_queue_length_ = 0;
    double average_waiting_time_ = 0;
    int get_max_unload_time_ = 0;
    double get_average_unload_time_ = 0;
    int total_fine_ = 0;

    
};
