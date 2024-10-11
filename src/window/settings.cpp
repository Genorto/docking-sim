#include "../../includes/window/settings.h"
#include <iostream>

Settings::Settings() {
    window_ = new sf::RenderWindow(sf::VideoMode(700, 800), "Settings", sf::Style::Close);
    event_ = new sf::Event;
    /* implement objects */
    font.loadFromFile("assets/fonts/roboto.ttf");
    background_.setFillColor(sf::Color::White);
    background_.setSize({ 640, 45 });
    background_button_.setFillColor(sf::Color::White);
    background_button_.setSize({ 200, 30 });
    text_.setCharacterSize(20);
    text_.setFillColor(sf::Color::Black);
    text_.setFont(font);
    text_answer_.setCharacterSize(20);
    text_answer_.setFillColor(sf::Color::Black);
    text_answer_.setFont(font);
    text_button_.setCharacterSize(20);
    text_button_.setFillColor(sf::Color::Black);
    text_button_.setFont(font);
    text_button_.setString("Start simulation");
    background_button_.setPosition(240, 760);
    text_button_.setPosition(270, 760);
    vector_text = { L"Укажите размер штрафа:", L"Укажите диапазон опозданий:", L"Укажите шаг моделирования:",
        L"Укажите кол-во кранов каждого вида:",  L"Введите расписание кораблей:      (+)          (+)" };
    answer_text = { L"", L"", L"", L"" };
    status = mouse_status::nothing;
    count_ship_ = 0;
}

int Settings::GetStepSize() {
    return modeling_step_;
}

std::pair<int, int> Settings::GetRejectionLimits() {
    return shift_in_arrival_;
}

int Settings::GetFine() {
    return penalty_waiting_;
}

int Settings::GetBulkCranesNumber() {
    return number_bulk_crane_;
}

int Settings::GetFluidCranesNumber() {
    return number_fluid_crane_;
}

int Settings::GetContainerCranesNumber() {
    return number_container_crane_;
}

std::vector<Ship*> Settings::GetShips() {
    return vector_ship_;
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
            FillingFields();
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
                                        vector_ship_.push_back(new Tanker);
                                        vector_ship_[count_ship_]->set_ship_name("#" + std::to_string(count_ship_ + 1));
                                        count_ship_++;
                                        up_border_ = std::max(0, (int)vector_ship_.size() - 9);
                                        bottom_border_ = (int)vector_ship_.size() - 1;
                                    }
                                    if (x > 420 && x < 420 + 50) {
                                        vector_ship_.push_back(new CargoShip);
                                        vector_ship_[count_ship_]->set_ship_name("#" + std::to_string(count_ship_ + 1));
                                        count_ship_++;
                                        up_border_ = std::max(0, (int)vector_ship_.size() - 9);
                                        bottom_border_ = (int)vector_ship_.size() - 1;
                                    }
                                }
                                else {
                                    status = mouse_status::graph5;
                                }
                            }
                            else {
                                bool in = false;
                                for (int i = 0, j = up_border_; j <= bottom_border_; ++i, ++j) {
                                    if (x > 260 && x < 260 + 60 && y > 40 * i + 390 && y < 40 * (i + 1) + 390) {
                                        vector_ship_[j]->set_weight(std::min(std::max(0, vector_ship_[j]->get_weight() + (which_button ? 1: -1) * 100), 900));
                                        in = true;
                                    }
                                    if (x > 460 && x < 460 + 40 && y > 40 * i + 390 && y < 40 * (i + 1) + 390) {
                                        std::pair<int, int> copy = vector_ship_[j]->get_arrival_time();
                                        copy.first = (31 + copy.first + (which_button ? 1 : -1)) % 31;
                                        vector_ship_[j]->SetArrivalTime(copy);
                                        in = true;
                                    }
                                    if (x > 540 && x < 540 + 60 && y > 40 * i + 390 && y < 40 * (i + 1) + 390) {
                                        std::pair<int, int> copy = vector_ship_[j]->get_arrival_time();
                                        copy.second = (24 + copy.second + (which_button ? 1 : -1)) % 24;
                                        vector_ship_[j]->SetArrivalTime(copy);
                                        in = true;
                                    }
                                }
                                if (!in) {
                                    if (x > background_button_.getPosition().x && x < background_button_.getPosition().x + background_button_.getSize().x &&
                                        y > background_button_.getPosition().y && y < background_button_.getPosition().y + background_button_.getSize().y) {
                                        FillingFields();
                                        window_->close();
                                    }
                                    else {
                                        status = mouse_status::nothing;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;

        case sf::Event::TextEntered:
            if (event_->text.unicode > 47 && event_->text.unicode < 58 || event_->text.unicode == 47 || event_->text.unicode == 45) {
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
            break;

        case sf::Event::MouseWheelScrolled:
            if (event_->mouseWheelScroll.delta > 0) {
                up_border_ = std::max(0, up_border_ - (int)event_->mouseWheelScroll.delta);
                bottom_border_ = std::min((int)vector_ship_.size() - 1, up_border_ + 8);
            } else {
                bottom_border_ = std::min((int)vector_ship_.size() - 1, bottom_border_ - (int)event_->mouseWheelScroll.delta);
                up_border_ = std::max(0, bottom_border_ - 8);
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
        window_->draw(background_button_);
        window_->draw(text_button_);

        if (i < 4) {
            text_answer_.setString(answer_text[i]);
            text_answer_.setPosition(x, y + 20);
            window_->draw(text_answer_);
        }
        else {
            y += 40;
            for (int j = up_border_; j <= bottom_border_; ++j) {
                background_.setPosition(x, y);
                window_->draw(background_);
                sf::String type = L"Тип корабля:";
                type += (vector_ship_[j]->get_type() == ShipType::CargoShip) ? ("CargoShip " + vector_ship_[j]->get_ship_name() + "  ") : ("Tanker       " + vector_ship_[j]->get_ship_name() + "  ");
                type += L"Вес: ";
                type += std::to_wstring(vector_ship_[j]->get_weight());
                if (vector_ship_[j]->get_weight() / 100 > 0) {
                    type += L" ";
                }
                else {
                    type += L"     ";
                }
                type += L" Время: день ";
                if (vector_ship_[j]->get_arrival_time().first / 10 < 1) {
                    type += L"  ";
                }
                type += std::to_wstring(vector_ship_[j]->get_arrival_time().first);
                type += L" часы ";
                if (vector_ship_[j]->get_arrival_time().second / 10 < 1) {
                    type+= L"0";
                }
                type += std::to_wstring(vector_ship_[j]->get_arrival_time().second);
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

int TranslatorFromStringToNumber(sf::String str) {
    if (str.getSize() == 0) {
        return 0;
    }
    int i = 0, sign = 1;;
    if (str[0] == L'+') {
        sign = 1;
        i++;
    }
    if (str[0] == L'-') {
        sign = -1;
        i++;
    }
    int answer = 0;
    for (; i < str.getSize(); ++i) {
        answer = answer * 10 + (str[i] - L'0');
    }
    return sign * answer;
}

std::pair<int, int> OneSeparator(sf::String str) {
    sf::String first = L"", second = L"";
    bool flag = true;
    for (int i = 0; i < str.getSize(); ++i) {
        if (str[i] == L'/') {
            flag = !flag;
            continue;
        }
        if (flag) {
            first += str[i];
        }
        else {
            second += str[i];
        }
    }
    return { TranslatorFromStringToNumber(first), TranslatorFromStringToNumber(second) };
}

std::pair<std::pair<int, int>, int> TwoSeparator(sf::String str) {
    sf::String first = L"", second = L"", third = L"";
    int flag = 1;
    for (int i = 0; i < str.getSize(); ++i) {
        if (str[i] == L'/') {
            flag++;
            continue;
        }
        switch (flag) {
        case 1:
            first += str[i];
            break;
        case 2:
            second += str[i];
            break;
        case 3:
            third += str[i];
            break;
        }
    }
    return { {TranslatorFromStringToNumber(first), TranslatorFromStringToNumber(second) }, TranslatorFromStringToNumber(third) };
}

void Settings::FillingFields() {
    penalty_waiting_ = TranslatorFromStringToNumber(answer_text[0]); // штраф, который мы платим за час ожидания
    shift_in_arrival_ = OneSeparator(answer_text[1]); //насколько поезд прибыл раньше/позже в днях
    modeling_step_ = TranslatorFromStringToNumber(answer_text[2]); // подается в часах
    std::pair<std::pair<int, int>, int> crane_ = TwoSeparator(answer_text[3]);
    number_bulk_crane_ = crane_.first.first; //кол-во кранов
    number_fluid_crane_ = crane_.first.second; //кол-во кранов
    number_container_crane_ = crane_.second; //кол-во кранов
}

Settings::~Settings() {}
