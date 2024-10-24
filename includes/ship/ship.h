#pragma once
#include "SFML/Graphics.hpp"

enum class ShipType { CargoShip, Tanker };
enum class Animation { FadeIn, Unload, FadeOut, Visible, Invisible };

class Ship {
public:
	Ship();
	Ship(int weight, std::pair<int, int> arrival_time, std::string ship_name);
	Ship(Ship&& other);
	Ship(const Ship& other);
	Ship& operator= (const Ship& other);
	~Ship() = default;
	virtual bool isHovered(sf::Vector2i cursor_pos) final;
	void Animate(double time, int fps, double duration);
	void Show();
	void Hide();
	void FadeIn();
	void FadeOut();
	void Unload();
	void Draw(sf::RenderWindow*& window);

	void SetType(ShipType type);
	void SetWeight(int);
	void SetArrivalRejection(int);
	void SetShipName(std::string);
	void SetPos(double x, double y);
	void SetArrivalTime(std::pair<int, int> data);
	void SetStartPos(double x, double y);
	void SetEndPos(double x, double y);
	void SetSize(double size_x, double size_y);
	void SetModel(std::string path);

	virtual std::vector<std::string*> GetInfo() = 0;
	int GetWeight();
	int GetArrivalRejection();
	std::pair<int, int> GetArrivalTime();
	std::string GetName();
	ShipType GetType();
	std::pair<double, double> GetPos();
	std::pair<double, double> GetStartPos();
	std::pair<double, double> GetEndPos();
	std::pair<double, double> GetSize();

protected:
	int weight_;
	int arrival_rejection_;
	std::pair<int, int> arrival_time_; // day, hour
	std::string ship_name_;
	ShipType type_;
	double x_ = 0, y_ = 0;
	double start_x_ = 0, start_y_ = 0;
	double end_x_ = 0, end_y_ = 0;
	double size_x_ = 0, size_y_ = 0;
	double rotation_;
	sf::Texture model_;
	Animation animation_ = Animation::Invisible;
	sf::Color color_ = sf::Color(255, 255, 255);
};