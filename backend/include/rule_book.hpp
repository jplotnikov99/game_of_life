#pragma once

#include "grid.hpp"

class RuleBook {

private:
  const int delay = 200; // Delay in milliseconds between steps

public:
  RuleBook(const int delay) : delay(delay) {};

  ~RuleBook() {};

  void applyRules(Grid &grid);

};