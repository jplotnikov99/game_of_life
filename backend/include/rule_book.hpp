#pragma once

#include "grid.hpp"
#include <memory>
#include <vector>

class RuleBook {

private:
  Grid newGrid;
  int x, y;
  std::vector<int> cellCount = {0, 0}; // Index 0 for BASIC, 1 for HUNGER

public:
  RuleBook(const Grid &grid) : newGrid(grid.getrows(), grid.getcols()) {};

  ~RuleBook() {};

  void applyRules(Grid &grid);

  void basicRule(BasicCell &currentCell, std::unique_ptr<BasicCell> &nextCell);

  void hungerRule(HungerCell &currentCell,
                  std::unique_ptr<BasicCell> &nextCell);

  int countNeighbors();

  CellType getDominantCellType() const;
};