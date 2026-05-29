#pragma once

#include "cell.hpp"
#include <memory>
#include <vector>

class Grid {

private:
  const int rows;
  const int cols;
  std::vector<std::vector<std::unique_ptr<BasicCell>>> cells;

public:
  Grid(int rows, int cols); 
  ~Grid() {};

  void printState();

  void copyState(const Grid &other);

  void boundaryConditions(int &x, int &y);

  void setCell(int x, int y, std::unique_ptr<BasicCell> newCell);

  BasicCell &getCell(int x, int y);

  std::unique_ptr<BasicCell> &getCellPtr(int x, int y);

  void randomize();

  int getrows() const { return rows; }

  int getcols() const { return cols; }
};