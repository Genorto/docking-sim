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
     std::vector<Crane*> GetBulkCranes();
     std::vector<Crane*> GetFluidCranes();
     std::vector<Crane*> GetContainerCranes();
     std::vector<Ship*> GetCargoShips();
     std::vector<Ship*> GetTankers();
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
     int day_, hour_;
};