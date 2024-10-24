#pragma once
#include <SFML/Graphics.hpp>
#include "ship/cargo_ship.h"
#include "ship/tanker.h"
#include "crane/bulk_crane.h"
#include "crane/fluid_crane.h"
#include "crane/container_crane.h"
#include "cursor_hover_window.h"

class Model final {
 public:
     Model();
     virtual ~Model();
     void RandomizeShipsData();
     void AddBulkCrane(Crane*&);
     void AddFluidCrane(Crane*&);
     void AddContainerCrane(Crane*&);
     void AddShip(Ship*&);
     std::vector<Crane*> GetBulkCranes();
     std::vector<Crane*> GetFluidCranes();
     std::vector<Crane*> GetContainerCranes();
     std::vector<Ship*> GetShips();
     
     void SetFPS(int);
     void SetStepLength(double);
     void SetStepSize(int);
     void SetTimeLimits(std::pair<int, int>);
     void SetTimeLimits(int, int);
     void SetRejectionLimits(std::pair<int, int>);
     void SetRejectionLimits(int, int);
     void SetUnloadRejectionLimits(std::pair<int, int>);
     void SetUnloadRejectionLimits(int, int);
     void SetFine(int);
     void SetSpeedLimits(std::pair<int, int>);
     void SetSpeedLimits(int, int);
     void SetFont(std::string font_dir);

     int GetFPS();
     double GetClock();
     double GetStepLength();
     int GetStepSize();
     std::pair<int, int> GetTimeLimits();
     std::pair<int, int> GetTime();
     int GetShipsCount();
     double GetAverageQueueLength();
     double GetAverageWaitingTime();

     void NextHour();
     void UpdateSimulation();
     void SkipShipsAnimations(); // only when switches by key
     int GetMaxUnloadRejectionTime();
     double GetAverageUnloadRejectionTime();
     int GetTotalFine();
     std::vector<std::string*> GetLog();

 private:
     void UpdateRejections();
     void UpdateQueues();
     void UpdateUnloads();
     std::vector<Crane*> bulk_cranes_;
     std::vector<Crane*> fluid_cranes_;
     std::vector<Crane*> container_cranes_;
     std::vector<Ship*> ships_;
     std::pair<int, int> weight_limits_;
     std::pair<int, int> time_limits_; // day, hour
     std::pair<int, int> rejection_limits_;
     std::pair<int, int> unload_rejection_limits_;
     int fine_;
     std::pair<int, int> speed_limits_;
     int step_size_; // in hours
     double step_length_;
     int unload_time_ = -1; // in hours
     int day_ = 0, hour_ = 0;
     int fps_ = 60;
     sf::Font font_;
     std::vector<std::string*> log;
     sf::Clock* clock_;
     /* results are sent to conclusion */
     int res_ships_cnt_ = 0;
     int res_total_queues_length_ = 0;
     int res_queues_cnt_ = 0;
     int res_total_waiting_time_ = 0;
     int res_total_unload_rejection_time_ = 0;
     int res_max_unload_rejection_time_ = 0;
     int res_total_fine_ = 0;
};