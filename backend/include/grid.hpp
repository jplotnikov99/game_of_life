#pragma once

#include "cell.hpp"
#include <vector>

class Grid {

private:
  const int rows;
  const int cols;
  std::vector<std::vector<BasicCell>> cells;

public:
  Grid(int rows, int cols) : rows(rows), cols(cols) {
    cells.resize(rows, std::vector<BasicCell>(cols));
  }

  ~Grid() {};

  void printState();

  void boundaryConditions(int &x, int &y);

  void setCellState(int x, int y, bool alive);

  BasicCell &getCell(int x, int y);

  int getrows() const { return rows; }

  int getcols() const { return cols; }
};