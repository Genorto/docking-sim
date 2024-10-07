﻿#pragma once
#include "window.h"
enum class mouse_status { graph1, graph2, graph3, graph4, graph5, nothing};
class Settings : public Window {
public:
    Settings();
    virtual void CheckEvents() override;
    virtual void Draw() override;
    virtual bool isOpen() override;
    virtual ~Settings();

    int penalty_waiting_; // штраф, который мы платим за час ожидания
    std::pair<int, int> shift_in_arrival_; //насколько поезд прибыл раньше/позже в днях
    int modeling_step_; // подается в часах
    int number_bulk_crane_, number_fluid_crane_, number_container_crane_; //кол-во кранов
    std::vector<Ship*> vector_ship; //расписание в виде вектора кораблей

    sf::RectangleShape background_;
    sf::Text text_, text_answer_;
    std::vector<sf::String> vector_text, answer_text;
    
    sf::Font font;
    mouse_status status;
};
