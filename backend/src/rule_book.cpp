#include "rule_book.hpp"

void RuleBook::applyRules(Grid &grid) {
  Grid newGrid(grid.getrows(), grid.getcols()); // Create a copy of the current grid
  newGrid.copyState(grid);
  for (int x = 0; x < grid.getrows(); ++x) {
    for (int y = 0; y < grid.getcols(); ++y) {
      int aliveNeighbors = 0;
      // Check all 8 neighbors
      for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
          if (dx == 0 && dy == 0)
            continue; // Skip the current cell
          if (newGrid.getCell(x + dx, y + dy).alive) {
            aliveNeighbors++;
          }
        }
      }
      // Apply the Game of Life rules
      if (newGrid.getCell(x, y).alive) {
        grid.setCellState(x, y, aliveNeighbors == 2 || aliveNeighbors == 3);
      } else {
        grid.setCellState(x, y, aliveNeighbors == 3);
      }
    }
  }
}