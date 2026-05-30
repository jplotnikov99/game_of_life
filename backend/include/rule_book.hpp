#pragma once

#include "grid.hpp"
#include <memory>
#include <vector>

class RuleBook {

private:
  Grid newGrid;
  int x, y;              // Current cell coordinates
  int aliveNeighbors;    // Count of alive neighbors
  CellType dominantType; // Dominant cell type among neighbors
  std::vector<std::unique_ptr<BasicCell> *> neighbors; // Neighboring cells
  std::vector<int> neighborCount = {
      0, 0, 0}; // Index 0 for BASIC, 1 for HUNGER, 2 for VEGITATION

public:
  RuleBook(const Grid &grid)
      : newGrid(grid.getrows(), grid.getcols()), neighbors(8) {};

  ~RuleBook() {};

  void applyRules(Grid &grid);

  void basicRule(std::unique_ptr<BasicCell> &currentCell,
                 std::unique_ptr<BasicCell> &nextCell);

  void hungerRule(std::unique_ptr<BasicCell> &currentCell,
                  std::unique_ptr<BasicCell> &nextCell);

  void vegitationRule(std::unique_ptr<BasicCell> &currentCell,
                      std::unique_ptr<BasicCell> &nextCell);

  std::unique_ptr<BasicCell>
  deadCellRule(std::unique_ptr<BasicCell> &currentCell);

  void loadNeighbors();

  CellType getDominantCellType() const;

  void loadCellState();

  void applyEatenRules(std::unique_ptr<BasicCell> &currentCell,
                       std::unique_ptr<BasicCell> &nextCell);
};