#include "rule_book.hpp"

void RuleBook::applyRules(Grid &grid) {
  Grid newGrid(grid.getrows(),
               grid.getcols()); // Create a copy of the current grid
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
      switch (newGrid.getCell(x, y).getType()) {
      case CellType::BASIC:
        basicRule(newGrid.getCell(x, y), grid.getCell(x, y), aliveNeighbors);
        break;
      case CellType::HUNGER:
        hungerRule(dynamic_cast<HungerCell &>(newGrid.getCell(x, y)),
                   dynamic_cast<HungerCell &>(grid.getCell(x, y)),
                   aliveNeighbors);
        break;
      default:
        break;
      }
    }
  }
}

void RuleBook::basicRule(BasicCell &currentCell, BasicCell &nextCell,
                         int aliveNeighbors) {
  if (currentCell.alive) {
    nextCell.alive = (aliveNeighbors == 2 || aliveNeighbors == 3);
  } else {
    nextCell.alive = (aliveNeighbors == 3);
  }
}

void RuleBook::hungerRule(HungerCell &currentCell, HungerCell &nextCell,
                          int aliveNeighbors) {
  if (currentCell.alive) {
    nextCell.alive = ((aliveNeighbors == 2 || aliveNeighbors == 3) && currentCell.hunger < 3);
    nextCell.hunger = currentCell.hunger + 1; // Increase hunger
  } else {
    nextCell.alive = (aliveNeighbors == 3);
    nextCell.hunger = 0; // Reset hunger when a cell becomes alive
  }
}