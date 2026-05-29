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
  Grid(int rows, int cols) : rows(rows), cols(cols) {
    cells.resize(rows);
    for (auto &row : cells) {
      row.resize(cols);
      for (auto &cell : row) {
        cell = std::make_unique<HungerCell>();
      }
    }
  }

  ~Grid() {};

  void printState();

  void copyState(const Grid &other);

  void boundaryConditions(int &x, int &y);

  void setCellState(int x, int y, bool alive);

  void toggleCellState(int x, int y);

  BasicCell &getCell(int x, int y);

  int getrows() const { return rows; }

  int getcols() const { return cols; }
};