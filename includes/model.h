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
     void CreateCranes(size_t bulk_cnt, size_t fluid_cnt, size_t container_cnt);
     void CreateShips(size_t cargo_cnt, size_t tanker_cnt);
     void RandomizeShipsData();
     std::vector<Crane*> GetBulkCranes();
     std::vector<Crane*> GetFluidCranes();
     std::vector<Crane*> GetContainerCranes();
     std::vector<Ship*> GetCargoShips();
     std::vector<Ship*> GetTankers();
     void SetStepSize(int);
     void SetWeightLimits(std::pair<int, int>);
     void SetWeightLimits(int, int);
     void SetTimeLimits(std::pair<std::pair<int, int>, std::pair<int, int>>);
     void SetTimeLimits(std::pair<int, int>, std::pair<int, int>);
     void SetTimeLimits(int, int, int, int);
     void SetRejectionLimits(std::pair<int, int>);
     void SetRejectionLimits(int, int);
     void SetFineLimits(std::pair<int, int>);
     void SetFineLimits(int, int);
     void SetSpeedLimits(std::pair<int, int>);
     void SetSpeedLimits(int, int);
     void NextStep();
     void PreviousStep();
     std::pair<int, int> GetTime();
     void SortNewShips();

 private:
     std::vector<Crane*> bulk_cranes_;
     std::vector<Crane*> fluid_cranes_;
     std::vector<Crane*> container_cranes_;
     std::vector<Ship*> cargo_ships_;
     std::vector<Ship*> tankers_;
     std::pair<int, int> weight_limits_;
     std::pair<std::pair<int, int>, std::pair<int, int>> time_limits_; // day, hour && day, hour
     std::pair<int, int> rejection_limits_;
     std::pair<int, int> fine_limits_;
     std::pair<int, int> speed_limits_;
     int step_size_; // in hours
     int day_ = 0, hour_ = 0;
};