#include "grid.hpp"
#include <iostream>

void Grid::printState() {
  std::cout << "--------------------" << std::endl;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      std::cout << (cells[i][j]->alive ? "#" : ".");
    }
    std::cout << std::endl;
  }
}

void Grid::copyState(const Grid &other) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      cells[i][j] = other.cells[i][j]->clone();
    }
  }
}

void Grid::boundaryConditions(int &x, int &y) {
  if (x < 0)
    x = (x % rows + rows); // Handle negative indices
  if (y < 0)
    y = (y % cols + cols);
  x = x % rows; // Wrap around for positive indices
  y = y % cols;
}

void Grid::setCellState(int x, int y, bool alive) {
  boundaryConditions(x, y);
  cells[x][y]->alive = alive;
}

void Grid::toggleCellState(int x, int y) {
  boundaryConditions(x, y);
  cells[x][y]->alive = !cells[x][y]->alive;
}

BasicCell &Grid::getCell(int x, int y) {
  boundaryConditions(x, y);
  return *cells[x][y];
}
