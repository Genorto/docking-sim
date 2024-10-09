#pragma once
#include "SFML/Graphics.hpp"

enum class ShipType { CargoShip, Tanker };

class Ship {
public:
	Ship();
	Ship(int weight, std::pair<int, int> arrival_time, std::string ship_name);
	Ship(Ship&& other);
	Ship(const Ship& other);
	Ship& operator= (const Ship& other);
	~Ship() = default;
	virtual bool isHovered(sf::Vector2i cursor_pos) final;
	virtual std::vector<std::string*> GetInfo() = 0;
	void SetType(ShipType type);
	void set_weight(int);
	int get_weight();
	void set_arrival_rejection(int);
	int get_arrival_rejection();
	void set_arrival_time(std::pair<int, int>);
	std::pair<int, int> get_arrival_time();
	void set_ship_name(std::string);
	std::string get_ship_name();
	ShipType get_type();
	virtual void SetPos(double x, double y) final;
	virtual std::pair<double, double> GetPos() final;
	virtual void SetStartPos(double x, double y) final;
	virtual void SetEndPos(double x, double y) final;
	virtual void Animate(double time, int fps, double duration) final;
	virtual void SetSize(double size_x, double size_y) final;
	virtual std::pair<double, double> GetSize() final;
	virtual void SetModel(std::string path) final;
	virtual void Show() final;
	virtual void Hide() final;
	virtual void Draw(sf::RenderWindow*& window) final;

protected:
	// installed before the start
	int weight_;
	int fine_; // penalty for an hour of delay
	int arrival_rejection_; // delay
	std::pair<int, int> arrival_time_; // first - day, second - hour
	std::string ship_name_;
	ShipType type_;
	//  installed after the start
	int waiting_time_;
	int service_time_;
	// frontend variables
	double x_ = 0, y_ = 0;
	double start_x_ = 0, start_y_ = 0;
	double end_x_ = 0, end_y_ = 0;
	double size_x_ = 0, size_y_ = 0;
	sf::Texture model_;
	bool is_shown_ = false;
};