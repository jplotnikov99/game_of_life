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
        case CellType::VEGITATION:
          vegitationRule(currentCell, nextCell);
          break;
        default:
          break;
        }
      else {
        nextCell = deadCellRule(currentCell);
      }
    }
  }
  for (x = 0; x < grid.getrows(); ++x) {
    for (y = 0; y < grid.getcols(); ++y) {
      std::unique_ptr<BasicCell> &currentCell = newGrid.getCellPtr(x, y);
      std::unique_ptr<BasicCell> &nextCell = grid.getCellPtr(x, y);
      applyEatenRules(currentCell, nextCell);
    }
  }
}

void RuleBook::basicRule(std::unique_ptr<BasicCell> &currentCell,
                         std::unique_ptr<BasicCell> &nextCell) {
  if (neighborCount[2] > 0) {
    for (auto &neighbor : neighbors) {
      if ((*neighbor)->alive && (*neighbor)->eaten == false &&
          (*neighbor)->getType() != CellType::VEGITATION) {
        (*neighbor)->eaten = true; // Mark the neighbor as eaten
        break;                     // Only eat one neighbor per turn
      }
    }
  }
  nextCell->alive = (neighborCount[0] == 2 || neighborCount[0] == 3);
}

void RuleBook::hungerRule(std::unique_ptr<BasicCell> &currentCell,
                          std::unique_ptr<BasicCell> &nextCell) {
  HungerCell *current = dynamic_cast<HungerCell *>(currentCell.get());
  HungerCell *next = dynamic_cast<HungerCell *>(nextCell.get());
  if (aliveNeighbors > neighborCount[1]) {
    for (auto &neighbor : neighbors) {
      if ((*neighbor)->alive && (*neighbor)->eaten == false &&
          (*neighbor)->getType() != CellType::HUNGER) {
        (*neighbor)->eaten = true; // Mark the neighbor as eaten
        break;                     // Only eat one neighbor per turn
      }
    }
    current->hunger = -5;
  } else {
    nextCell->alive = ((aliveNeighbors == 2 || aliveNeighbors == 3) &&
                       current->hunger < current->hungerThreshold) ||
                      current->hunger < 0;
  }
  next->hunger = current->hunger + 1;
}

void RuleBook::vegitationRule(std::unique_ptr<BasicCell> &currentCell,
                              std::unique_ptr<BasicCell> &nextCell) {
  nextCell->alive = (neighborCount[2] < 5);
}

std::unique_ptr<BasicCell>
RuleBook::deadCellRule(std::unique_ptr<BasicCell> &currentCell) {
  if (neighborCount[0] == 3) {
    if (dominantType == CellType::BASIC) {
      return std::make_unique<BasicCell>(true);
    }
  } else if (neighborCount[1] == 3) {
    if (dominantType == CellType::HUNGER) {
      return std::make_unique<HungerCell>(true);
    }
  } else if (neighborCount[2] == 1) {
    if (currentCell->getType() == CellType::VEGITATION) {
      VegitationCell *current =
          dynamic_cast<VegitationCell *>(currentCell.get());
      if (current->growth > current->growthThreshold) {
        return std::make_unique<VegitationCell>(true, current->growth + 1);
      } else {
        return std::make_unique<VegitationCell>(false, current->growth + 1);
      }
    } else
      return std::make_unique<VegitationCell>(false, 0);
  }
  return std::make_unique<BasicCell>(false);
}

void RuleBook::loadNeighbors() {
  int n = 0;
  aliveNeighbors = 0;
  neighborCount = {0, 0, 0}; // Reset counts for each type

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

void RuleBook::applyEatenRules(std::unique_ptr<BasicCell> &currentCell,
                               std::unique_ptr<BasicCell> &nextCell) {
  if (currentCell->eaten) {
    nextCell->alive = false;
    nextCell->eaten = false;
  }
  else{
    return;
  }
  if (currentCell->getType() == CellType::VEGITATION) {
    VegitationCell *next = dynamic_cast<VegitationCell *>(nextCell.get());
    next->growth = 0;
  }
}