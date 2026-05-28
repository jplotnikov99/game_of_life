#pragma once

#include "grid.hpp"

class StateUpdater {

private:
  const int delay = 200; // Delay in milliseconds between steps

public:
  StateUpdater(const int delay) : delay(delay) {};

  ~StateUpdater() {};

  void steps(Grid &grid, int numSteps);

  void update(Grid &grid);

};