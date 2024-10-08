#include "../../includes/window/settings.h"
#include <iostream>
Settings::Settings() {
    window_ = new sf::RenderWindow(sf::VideoMode(700, 800), "Settings");
    event_ = new sf::Event;
    /* implement objects */
    font.loadFromFile("../../../../assets/fonts/roboto.ttf");
    background_.setFillColor(sf::Color::White);
    background_.setSize({ 640, 60 });
    text_.setCharacterSize(20);
    text_.setFillColor(sf::Color::Black);
    text_.setFont(font);
    text_answer_.setCharacterSize(20);
    text_answer_.setFillColor(sf::Color::Black);
    text_answer_.setFont(font);
    vector_text = { L"Укажите размер штрафа:", L"Укажите диапазон опозданий:", L"Укажите шаг моделирования:",
        L"Укажите кол-во кранов каждого вида:",  L"Введите расписание кораблей:      (+)          (+)" };
    answer_text = { L"", L"", L"", L"" };
    status = mouse_status::nothing;
    vector_ship = { new Tanker(), new CargoShip()};
}

void Settings::CheckEvents() {
    while (window_->pollEvent(*event_)) {
        int x = event_->mouseButton.x, y = event_->mouseButton.y;
        bool which_button;
        if (event_->type == sf::Event::MouseButtonPressed) {
            which_button = event_->mouseButton.button == sf::Mouse::Right;
        }
        switch (event_->type) {
        case sf::Event::Closed:
            window_->close();
            break;
        case sf::Event::MouseButtonPressed:
            if (x > 30 && x < 30 + 640 && y > 30 + 0 * 80 && y < 30 + 60 + 0 * 80) {
                status = mouse_status::graph1;
            }
            else {
                if (x > 30 && x < 30 + 640 && y > 30 + 1 * 80 && y < 30 + 60 + 1 * 80) {
                    status = mouse_status::graph2;
                }
                else {
                    if (x > 30 && x < 30 + 640 && y > 30 + 2 * 80 && y < 30 + 60 + 2 * 80) {
                        status = mouse_status::graph3;
                    }
                    else {
                        if (x > 30 && x < 30 + 640 && y > 30 + 3 * 80 && y < 30 + 60 + 3 * 80) {
                            status = mouse_status::graph4;
                        }
                        else {
                            if (x > 30 && x < 30 + 640 && y > 30 + 4 * 80 && y < 30 + 40 + 4 * 80) {
                                if (status == mouse_status::graph5) {
                                    if (x > 340 && x < 340 + 50) {
                                        vector_ship.push_back(new Tanker);
                                    }
                                    if (x > 420 && x < 420 + 50) {
                                        vector_ship.push_back(new CargoShip);
                                    }
                                }
                                else {
                                    status = mouse_status::graph5;
                                }
                            }
                            else {
                                bool in = false;
                                for (int i = 0; i < vector_ship.size(); ++i) {
                                    if (x > 260 && x < 260 + 60 && y > 40 * i + 390 && y < 40 * (i + 1) + 390) {
                                        vector_ship[i]->set_weight(std::min(std::max(0, vector_ship[i]->get_weight() + (which_button ? 1: -1) * 100), 900));
                                        in = true;
                                    }
                                    if (x > 460 && x < 460 + 40 && y > 40 * i + 390 && y < 40 * (i + 1) + 390) {
                                        std::pair<int, int> copy = vector_ship[i]->get_arrival_time();
                                        copy.first = (31 + copy.first + (which_button ? 1 : -1)) % 31;
                                        vector_ship[i]->SetArrivalTime(copy);
                                        in = true;
                                    }
                                    if (x > 540 && x < 540 + 60 && y > 40 * i + 390 && y < 40 * (i + 1) + 390) {
                                        std::pair<int, int> copy = vector_ship[i]->get_arrival_time();
                                        copy.second = (24 + copy.second + (which_button ? 1 : -1)) % 24;
                                        vector_ship[i]->SetArrivalTime(copy);
                                        in = true;
                                    }
                                }
                                if (!in) {
                                    status = mouse_status::nothing;
                                }
                            }
                        }
                    }
                }
            }
            break;
        case sf::Event::TextEntered:
            if (event_->text.unicode > 47 && event_->text.unicode < 58 || event_->text.unicode == 47) {
                switch (status) {
                case mouse_status::graph1:
                    answer_text[0] += (event_->text.unicode);
                    break;
                case mouse_status::graph2:
                    answer_text[1] += event_->text.unicode;                   
                    break;
                case mouse_status::graph3:
                    answer_text[2] += event_->text.unicode;                    
                    break;
                case mouse_status::graph4:
                    answer_text[3] += event_->text.unicode;                    
                    break;
                }
            }
            if (event_->text.unicode == 8) {
                switch (status) {
                case mouse_status::graph1:
                    answer_text[0].getSize() > 0 ? answer_text[0].erase(answer_text[0].getSize() - 1, 1):0;
                    break;
                case mouse_status::graph2:
                    answer_text[1].getSize() > 0 ? answer_text[1].erase(answer_text[1].getSize() - 1, 1) : 0;
                    break;
                case mouse_status::graph3:
                    answer_text[2].getSize() > 0 ? answer_text[2].erase(answer_text[2].getSize() - 1, 1) : 0;
                    break;
                case mouse_status::graph4:
                    answer_text[3].getSize() > 0 ? answer_text[3].erase(answer_text[3].getSize() - 1, 1) : 0;
                    break;
                }
            }
        }
    }
}

void Settings::Draw() {
    window_->clear();
    /* draw objects */
    int x = 30, y = 30;
    for (int i = 0; i < 5; ++i) {
        if (i == int(status) && i < 4) {
            background_.setFillColor(sf::Color{120, 120, 120});
        }
        else {
            background_.setFillColor(sf::Color::White);
        }
        background_.setPosition(x, y);
        text_.setString(vector_text[i]);
        text_.setPosition(x, y);
        window_->draw(background_);
        window_->draw(text_);
        if (i < 4) {
            text_answer_.setString(answer_text[i]);
            text_answer_.setPosition(x, y + 20);
            window_->draw(text_answer_);
        }
        else {
            y += 40;
            for (int j = 0; j < vector_ship.size(); ++j) {
                background_.setPosition(x, y);
                window_->draw(background_);
                sf::String type = L"Тип корабля: ";
                type += (vector_ship[j]->get_type() == ShipType::CargoShip) ? "CargoShip  " : "Tanker        ";
                type += L"Вес: ";
                type += std::to_wstring(vector_ship[j]->get_weight());
                if (vector_ship[j]->get_weight() / 100 > 0) {
                    type += L" ";
                }
                else {
                    type += L"     ";
                }
                type += L" Время: день ";
                if (vector_ship[j]->get_arrival_time().first / 10 < 1) {
                    type += L"  ";
                }
                type += std::to_wstring(vector_ship[j]->get_arrival_time().first);
                type += L" часы ";
                if (vector_ship[j]->get_arrival_time().second / 10 < 1) {
                    type+= L"0";
                }
                type += std::to_wstring(vector_ship[j]->get_arrival_time().second);
                type += L":00";
                text_answer_.setString(type);
                text_answer_.setPosition(x, y);
                window_->draw(text_answer_);
                y += 40;
            }
        }
        y += 80;
    }
    window_->display();
}

bool Settings::isOpen() {
    return window_->isOpen();
}

Settings::~Settings() {}
