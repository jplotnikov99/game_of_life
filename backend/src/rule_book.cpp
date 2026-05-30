#include "rule_book.hpp"
#include "grid.hpp"
#include "utils.hpp"
#include <memory>

void RuleBook::applyRules(Grid &grid) {

  // Create a copy of the current grid
  newGrid.copyState(grid);

  for (x = 0; x < grid.getrows(); ++x) {
    for (y = 0; y < grid.getcols(); ++y) {
      // load all information about the current cell and its neighbors
      loadCellState();
      // Apply the Game of Life rules
      std::unique_ptr<BasicCell> &currentCell = newGrid.getCellPtr(x, y);
      std::unique_ptr<BasicCell> &nextCell = grid.getCellPtr(x, y);

      if (currentCell->alive)
        switch (currentCell->getType()) {
        case CellType::BASIC:
          basicRule(currentCell, nextCell);
          break;
        case CellType::HUNGER:
          hungerRule(currentCell, nextCell);
          break;
        default:
          break;
        }
      else {
        if (neighborCount[0] == 3) {
          if (dominantType == CellType::BASIC) {
            nextCell = std::make_unique<BasicCell>(true);
          }
        } else if (neighborCount[1] == 3) {
          if (dominantType == CellType::HUNGER) {
            nextCell = std::make_unique<HungerCell>(true);
          }
        }
      }
    }
  }
}

void RuleBook::basicRule(std::unique_ptr<BasicCell> &currentCell,
                         std::unique_ptr<BasicCell> &nextCell) {
  if (currentCell->killed) {
    nextCell->alive = false;  // Ensure the cell is dead in the next generation
    nextCell->killed = false; // reset the killed status for the next generation
    return;                   // Skip the rest of the rules for this cell
  }
  nextCell->alive = (neighborCount[0] == 1 || neighborCount[0] == 2 || neighborCount[0] == 3);
}

void RuleBook::hungerRule(std::unique_ptr<BasicCell> &currentCell,
                          std::unique_ptr<BasicCell> &nextCell) {
  HungerCell *current = dynamic_cast<HungerCell *>(currentCell.get());
  auto *next = dynamic_cast<HungerCell *>(nextCell.get());
  if (aliveNeighbors > neighborCount[1]) {
    for (auto &neighbor : neighbors) {
      if ((*neighbor)->alive && (*neighbor)->killed == false &&
          (*neighbor)->getType() != CellType::HUNGER) {
        (*neighbor)->killed = true; // Mark the neighbor as killed
        break;                      // Only kill one neighbor per turn
      }
    }
    current->hunger = -1;
  } else {
    nextCell->alive = (((aliveNeighbors == 2 || aliveNeighbors == 3) &&
                       current->hunger < current->hungerThreshold) || current->hunger < 0);
  }
  next->hunger = current->hunger + 1;
}

void RuleBook::loadNeighbors() {
  int n = 0;
  aliveNeighbors = 0;
  neighborCount = {0, 0}; // Reset counts for each type

  for (int dx = -1; dx <= 1; ++dx) {
    for (int dy = -1; dy <= 1; ++dy) {
      if (dx == 0 && dy == 0)
        continue; // Skip the current cell
      neighbors[n] = &newGrid.getCellPtr(x + dx, y + dy);
      if ((*neighbors[n])->alive) {
        neighborCount[(*neighbors[n])->getType()]++;
        aliveNeighbors++;
      }
      n++;
    }
  }
}

CellType RuleBook::getDominantCellType() const {
  if (neighborCount[0] > neighborCount[1]) {
    return CellType::BASIC;
  } else if (neighborCount[1] > neighborCount[0]) {
    return CellType::HUNGER;
  } else {
    if (rollDN(2) == 0) {
      return CellType::BASIC;
    } else {
      return CellType::HUNGER;
    }
  }
}

void RuleBook::loadCellState() {
  loadNeighbors();
  dominantType = getDominantCellType();
}