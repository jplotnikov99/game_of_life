#include "rule_book.hpp"
#include "grid.hpp"
#include "utils.hpp"

void RuleBook::applyRules(Grid &grid) {

  // Create a copy of the current grid
  newGrid.copyState(grid);

  for (x = 0; x < grid.getrows(); ++x) {
    for (y = 0; y < grid.getcols(); ++y) {

      // Apply the Game of Life rules
      switch (newGrid.getCell(x, y).getType()) {
      case CellType::BASIC:
        basicRule(newGrid.getCell(x, y), grid.getCellPtr(x, y));
        break;
      case CellType::HUNGER:
        hungerRule(dynamic_cast<HungerCell &>(newGrid.getCell(x, y)),
                   grid.getCellPtr(x, y));
        break;
      default:
        break;
      }
    }
  }
}

void RuleBook::basicRule(BasicCell &currentCell,
                         std::unique_ptr<BasicCell> &nextCell) {
  int aliveNeighbors = countNeighbors();
  CellType dominantType = getDominantCellType();

  if (currentCell.alive)
    nextCell->alive = (aliveNeighbors == 2 || aliveNeighbors == 3);
  else if (aliveNeighbors == 3)
    nextCell = createCell(dominantType,
                          true); // Create next cell based on dominant type
}

void RuleBook::hungerRule(HungerCell &currentCell,
                          std::unique_ptr<BasicCell> &nextCell) {
  int aliveNeighbors = countNeighbors();
  CellType dominantType = getDominantCellType();

  if (currentCell.alive) {
    if (aliveNeighbors == 1 && cellCount[0] == 1) {
      if (auto *hunger = dynamic_cast<HungerCell *>(nextCell.get())) {
        hunger->hunger = 0;
      }
    } else {
      nextCell->alive = ((aliveNeighbors == 2 || aliveNeighbors == 3) &&
                         currentCell.hunger < currentCell.hungerThreshold);
    }
    if (auto *hunger = dynamic_cast<HungerCell *>(nextCell.get())) {
      hunger->hunger = currentCell.hunger + 1;
    }

  } else if (aliveNeighbors == 3) {
    nextCell = createCell(dominantType,
                          true); // Create next cell based on dominant type
    if (auto *hunger = dynamic_cast<HungerCell *>(nextCell.get())) {
      hunger->hunger = 0;
    }
  }
}

int RuleBook::countNeighbors() {
  int count = 0;
  cellCount = {0, 0}; // Reset counts for each type

  for (int dx = -1; dx <= 1; ++dx) {
    for (int dy = -1; dy <= 1; ++dy) {
      if (dx == 0 && dy == 0)
        continue; // Skip the current cell
      if (newGrid.getCell(x + dx, y + dy).alive) {
        cellCount[newGrid.getCell(x + dx, y + dy).getType()]++;
        count++;
      }
    }
  }
  return count;
}

CellType RuleBook::getDominantCellType() const {
  if (cellCount[0] > cellCount[1]) {
    return CellType::BASIC;
  } else if (cellCount[1] > cellCount[0]) {
    return CellType::HUNGER;
  } else {
    if (rollDN(2) == 0) {
      return CellType::BASIC;
    } else {
      return CellType::HUNGER;
    }
  }
}