#include "state_updater.hpp"
#include <chrono>
#include <iostream>
#include <thread>

void StateUpdater::update(Grid &grid) {
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

void StateUpdater::steps(Grid &grid, int numSteps) {
  std::cout << "\033[2J\033[H"; // Clear screen and move cursor to top-left
  grid.printState();
  for (int i = 0; i < numSteps; ++i) {
    std::this_thread::sleep_for(
        std::chrono::milliseconds(delay)); // Sleep for 200ms between steps
    std::cout << "\033[2J\033[H"; // Clear screen and move cursor to top-left
    update(grid);
    // grid.printState();
  }
}