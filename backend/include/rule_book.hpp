#pragma once

#include "grid.hpp"

class RuleBook {

private:
  const int delay = 200; // Delay in milliseconds between steps

public:
  RuleBook(const int delay) : delay(delay) {};

  ~RuleBook() {};

  void applyRules(Grid &grid);

  void basicRule(BasicCell &currentCell, BasicCell &nextCell,
                 int aliveNeighbors);

  void hungerRule(HungerCell &currentCell, HungerCell &nextCell,
                  int aliveNeighbors);
};