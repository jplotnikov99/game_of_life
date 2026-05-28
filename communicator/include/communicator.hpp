#pragma once
#include "grid.hpp"
#include <QObject>

class Communicator : public QObject {
  Q_OBJECT
public:
  explicit Communicator(QObject *parent = nullptr);
  ~Communicator() = default;

  void stateUpdate(Grid &grid);
  void togglePlayPause();

signals:
  void updated();
};