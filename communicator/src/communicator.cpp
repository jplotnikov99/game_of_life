#include "communicator.hpp"
#include "state_updater.hpp"

Communicator::Communicator(QObject *parent) : QObject(parent) {}

void Communicator::stateUpdate(Grid &grid) {
  StateUpdater updater(1);
  updater.update(grid);
  emit updated();
}