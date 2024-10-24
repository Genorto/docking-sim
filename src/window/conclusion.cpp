#include "../../includes/window/conclusion.h"

Conclusion::Conclusion(Simulation* simulation) {
    window_ = new sf::RenderWindow(sf::VideoMode(960, 600), "Conclusion");
    event_ = new sf::Event;
    
    background_image_.loadFromFile("assets/sprites/background.png");
    background_texture_.loadFromImage(background_image_);
    background_sprite_.setTexture(background_texture_);
    background_sprite_.setPosition(0, 0);
    background_sprite_.setScale(0.5, 0.5);

    text_vector_ = { L"Статистика:",L"Число разгруженных судов", L"Средняя длина очереди", L"Среднее время ожидания", L"Максимальная и средняя задержка разгрузки", L"Общая сумма выплаченного штрафа" };
    
    res_ships_cnt_ = simulation->GetModel()->GetShipsCount();
    average_queue_length_ = simulation->GetModel()->GetAverageQueueLength();
    average_waiting_time_ = simulation->GetModel()->GetAverageWaitingTime();
    get_max_unload_time_ = simulation->GetModel()->GetMaxUnloadRejectionTime();
    get_average_unload_time_ = simulation->GetModel()->GetAverageUnloadRejectionTime();
    total_fine_ = simulation->GetModel()->GetTotalFine();

    font_.loadFromFile("assets/fonts/roboto.ttf");
    background_text_.setFillColor(sf::Color(256, 256, 256, 75));
    background_text_.setSize({ 470, 385 });
    background_text_.setPosition(450, 50);
    text_.setFont(font_);
    text_.setColor(sf::Color::White);
    text_.setCharacterSize(19);

}

Conclusion::Conclusion() {
    window_ = new sf::RenderWindow(sf::VideoMode(960, 600), "Conclusion");
    event_ = new sf::Event;

    background_image_.loadFromFile("assets/sprites/background.png");
    background_texture_.loadFromImage(background_image_);
    background_sprite_.setTexture(background_texture_);
    background_sprite_.setPosition(0, 0);
    background_sprite_.setScale(0.5, 0.5);

    text_vector_ = { L"Статистика:", L"Число разгруженных судов:", L"Средняя длина очереди:", L"Среднее время ожидания:", L"Максимальная и средняя задержка разгрузки:", L"Общая сумма выплаченного штрафа:"};

    font_.loadFromFile("assets/fonts/roboto.ttf");
    background_text_.setFillColor(sf::Color(256, 256, 256, 75));
    background_text_.setSize({ 470, 385 });
    background_text_.setPosition(450, 50);
    text_.setFont(font_);
    text_.setColor(sf::Color::White);
    text_.setCharacterSize(19);

}

void Conclusion::CheckEvents() {
    while (window_->pollEvent(*event_)) {
        switch (event_->type) {
        case sf::Event::Closed:
            window_->close();
            break;
        }
    }
}

void Conclusion::Draw() {
    window_->clear();
    window_->draw(background_sprite_);
    window_->draw(background_text_);
    int x = 455, y = 55;
    text_.setStyle(sf::Text::Bold | sf::Text::Underlined);
    for (int i = 0; i < text_vector_.size(); ++i) {
        text_.setString(text_vector_[i]);
        text_.setPosition(x, y);
        window_->draw(text_);
        y += (i == 0?35:70);
    }
    x = 455;
    y = 125;
    text_.setStyle(sf::Text::Regular);
    //res_ships_cnt_
    text_.setString(std::to_wstring(res_ships_cnt_));
    text_.setPosition(x, y);
    window_->draw(text_);
    y += 70;
    //average_queue_length_
    text_.setString((std::to_wstring(average_queue_length_).erase(std::to_wstring(average_queue_length_).find('.') + 2)));
    text_.setPosition(x, y);
    window_->draw(text_);
    y += 70;
    //average_waiting_time_
    text_.setString((std::to_wstring(average_waiting_time_).erase(std::to_wstring(average_waiting_time_).find('.') + 2)));
    text_.setPosition(x, y);
    window_->draw(text_);
    y += 70;
    //get_max_unload_time_ and get_average_unload_time_
    text_.setString(L"max: " + std::to_wstring(get_max_unload_time_) + L"/ average: " + ((std::to_wstring(get_average_unload_time_).erase(std::to_wstring(get_average_unload_time_).find('.') + 2))));
    text_.setPosition(x, y);
    window_->draw(text_);
    y += 70;
    //total_fine_ 
    text_.setString(std::to_wstring(total_fine_));
    text_.setPosition(x, y);
    window_->draw(text_);
    y += 70;

    window_->display();
}

bool Conclusion::isOpen() {
    return window_->isOpen();
}

Conclusion::~Conclusion() {}
