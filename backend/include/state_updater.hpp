#pragma once

#include "grid.hpp"
#include <QObject>
#include <qtmetamacros.h>

class StateUpdater : public QObject {
  Q_OBJECT
private:
  const int delay = 200; // Delay in milliseconds between steps

public:
  StateUpdater(const int delay) : delay(delay) {};

  ~StateUpdater() {};

  void steps(Grid &grid, int numSteps);

  void update(Grid &grid);

signals:

  void nextState();
};